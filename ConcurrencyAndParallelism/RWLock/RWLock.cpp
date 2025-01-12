#include "RWLock.h"

#include <iostream>
#include <thread>
#include <chrono>

// https://en.cppreference.com/w/cpp/numeric/ratio/ratio

thread_local uint32_t tls_threadID = 0;

using my_clock_t       = std::chrono::high_resolution_clock;
using my_millisecond_t = std::chrono::duration<uint64_t, std::milli>;

void RWLock::WriteLock()
{
    // 상위 32비트를 추출하여 스레드 ID를 구하는 코드
    const uint32_t lockOwnerID = (_lockState.load() & kWriteOwnerThreadMask) >> 32;

    // 동일 ID에 대한 재귀적 접근 허용
    if (tls_threadID == lockOwnerID)
    {
        // W -> W : 동일한 스레드가 Lock을 걸고 있는 것이니 멀티스레드 문제는 발생하지 않는다.
        // 동일한 스레드가 락을 소유하고 있다면 무조건 성공해야 한다.
        _writeCnt++; // 재귀적 접근이기 때문에 unlock을 위한 카운팅

        return;
    }

    // 시간 측정 시작(경합에서 이기지 못 하는 이상 현상을 탐지하기 위한 용도)
    const auto startTP = my_clock_t::now();

    // 락의 소유자를 바꾸기 위한 값
    const uint64_t desired = (uint64_t(tls_threadID) << 32) & kWriteOwnerThreadMask;

    while (true)
    {
        for (uint64_t spinCnt = 0; spinCnt < kMaxSpinCount; spinCnt++)
        {
            // C++의 CAS 작업은 실패하면 expected의 값을 원본의 값으로 갱신하기에 매번 새로 받아서 처리해야 한다.
            uint64_t expected = kEmptyState;

            // 소유권 획득 시도(아무도 소유 및 공유하고 있지 않을 때, 경합해서 소유권을 얻음)
            if (true == _lockState.compare_exchange_strong(expected, desired))
            {
                // 경합에서 이긴 상태
                _writeCnt++; // 재귀적인 호출을 파악하기 위한 용도

                return;
            }
        }

        const auto     duration = my_clock_t::now() - startTP;
        const uint64_t interval = std::chrono::duration_cast<my_millisecond_t>(duration).count();

        // 예상한 시간 내 소유권을 얻지 못하면 비정상적인 상황(프로그램을 종료시킴)
        if (interval >= kMaxTimeWait)
        {
            // TIMEOUT
            std::cout << "TimeOut\n";
            exit(-1);
        }

        // 제한된 횟수 내 소유권 획득에 실패하면 타임 슬라이스 포기(컨텍스트 스위칭 유도)
        std::this_thread::yield();
    }
}

void RWLock::WriteUnlock()
{
    // 동일 스레드에서 WriteLock을 잡고 ReadLock을 잡았다면 먼저 ReadLock을 전부 풀어야 WriteUnlock을 진행할 수 있다.
    if (0 != (_lockState.load() & kReadSharedCountMask)) // ReadCount가 0이 아니라는 의미는 누군가가 쓰고 있다는 뜻임.
    {
        // UNLOCK_ORDER_MISMATCH
        std::cout << "Unlock Order Mismatch\n";
        exit(-1);
    }

    _writeCnt--;

    if (0 == _writeCnt)
    {
        _lockState.store(kEmptyState);
    }

    // 이 코드에는 _writeCnt가 0 아래로 떨어졌을 때 이를 막는 예외처리가 없으니 주의할 것(필요하다면 추가)!
}

void RWLock::ReadLock()
{
    // 1) WriteLock을 잡고 있는 동일한 스레드 쪽에서 ReadLock을 호출하면 허용한다(어차피 다른 스레드는 접근하지 못하는 상황).
    const uint32_t lockOwnerID = (_lockState.load() & kWriteOwnerThreadMask) >> 32;

    if (tls_threadID == lockOwnerID)
    {
        // 다른 스레드에서는 여기에 접근할 수 없기 때문에 멀티스레딩 문제는 발생하지 않는다.
        _lockState.fetch_add(1);

        return;
    }
    
    // 2) 어떠한 스레드도 배타적으로 소유하고 있지 않은 상태라면 경합해서 공유 카운트(읽기 카운트)를 올려야 한다.
    const auto startTP = my_clock_t::now();

    while (true)
    {
        for (uint64_t spinCnt = 0; spinCnt < kMaxSpinCount; spinCnt++)
        {
            // WriteFlag는 의도적으로 0으로 밀어야 한다(예상되는 값에는 WriteThread가 없어야 함 -> 락을 소유하는 스레드가 없어야 한다는 뜻).
            // WriteLock을 잡고 있는 스레드가 아니라면 모든 스레드는 ReadLock을 대상으로만 경합해야 한다.
            uint64_t expected = _lockState.load() & kReadSharedCountMask;
            uint64_t desired  = expected + 1;

            // ReadLock만 잡고 있는 상태라면 허용
            if (true == _lockState.compare_exchange_strong(expected, desired))
                return; // 경합에서 이긴 상황(다른 스레드는 다시 경합하러 감)

            // 경합이 실패하는 상황은?
            // - 누군가 WriteLock을 잡고 있는 경우(WriteLock을 소유한 쪽이 아닌 경우).
            // - 누군가가 경합에서 이기고 _lockState의 값을 원자적으로 바꿔 expected와 매칭되지 않는 경우
        }

        const auto     duration = my_clock_t::now() - startTP;
        const uint64_t interval = std::chrono::duration_cast<my_millisecond_t>(duration).count();

        // 예상한 시간 내 소유권을 얻지 못하면 비정상적인 상황(프로그램을 종료시킴)
        if (interval >= kMaxTimeWait)
        {
            // TIMEOUT
            std::cout << "TimeOut\n";
            exit(-1);
        }

        // 제한된 횟수 내 소유권 획득에 실패하면 타임 슬라이스 포기(컨텍스트 스위칭 유도)
        std::this_thread::yield();
    }
}

void RWLock::ReadUnlock()
{
    if (0 == (_lockState.fetch_sub(1) & kReadSharedCountMask))
    {
        // ReadLock을 잡지 않은 상태에서 ReadUnlock을 호출한 상황
        std::cout << "ReadUnlock Under Zero\n";
        exit(-1);
    }
}
