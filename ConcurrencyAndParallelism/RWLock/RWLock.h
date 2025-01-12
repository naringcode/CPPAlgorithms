#pragma once

#include <atomic>

extern thread_local uint32_t tls_threadID;

// 64비트 자료형을 상위 32비트와 하위 32비트로 나눠서 다음과 같이 표현한다.
// !! 32비트 자료형을 상위 16비트와 하위 16비트로 나눠서 표현해도 됨. !!
// 
// [WWWWWWWW][WWWWWWWW][WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR][RRRRRRRR][RRRRRRRR]
// W : WriteFlag(Exclusive Lock Owner ThreadId) // 락을 현재 획득하고 있는 스레드의 ID
// R : ReadFlag(Shared Lock Count) // 락을 공유해서 사용하고 있는 카운트

// 동일 스레드의 Lock 정책
// W -> W (O)
// W -> R (O)
// R -> W (X)

// 멀티 스레드의 Lock 정책
// R -> R (O)
// W -> W (X)
// R -> W (X)
// W -> R (X)
class RWLock
{
public:
    enum : uint64_t
    {
        kMaxTimeWait  = 10'000,
        kMaxSpinCount = 5000,

        // 상위 32비트는 소유자 ID
        kWriteOwnerThreadMask = 0xFF'FF'FF'FF'00'00'00'00,

        // 하위 32비트는 Read의 공유 상태
        kReadSharedCountMask = 0x00'00'00'00'FF'FF'FF'FF,

        kEmptyState = 0x0000'0000'0000'0000
    };

public:
    RWLock() = default;
    ~RWLock() = default;

public:
    RWLock(const RWLock&) = delete;
    RWLock& operator=(const RWLock&) = delete;

    RWLock(RWLock&&) = delete;
    RWLock& operator=(RWLock&&) = delete;

public:
    void WriteLock();
    void WriteUnlock();

    void ReadLock();
    void ReadUnlock();

private:
    std::atomic<uint64_t> _lockState = kEmptyState;
    uint32_t              _writeCnt  = 0;
};

class ReadLockGuard
{
public:
    ReadLockGuard(RWLock& lock) : _lock(lock) { _lock.ReadLock(); }
    ~ReadLockGuard() { _lock.ReadUnlock(); }

private:
    RWLock&  _lock;
};

class WriteLockGuard
{
public:
    WriteLockGuard(RWLock& lock) : _lock(lock) { _lock.WriteLock(); }
    ~WriteLockGuard() { _lock.WriteUnlock(); }

private:
    RWLock& _lock;
};
