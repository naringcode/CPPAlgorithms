#include <bits/stdc++.h>

using namespace std;

// Time Complexity : O(N^2)
//
// 길이와 수열을 모두 구함

int n;

int arr[1'004];
int dp[1'004];

int prevIdx[1'004];
int nowIdx;

vector<int> vec;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(prevIdx, prevIdx + 1004, -1); // 0을 인덱싱할 수도 있으니까 초기화

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;

        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                if (dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;

                    prevIdx[i] = j; // 이전 요소로 나올 수 있는 것 계속 갱신
                }
            }
        }

        // 마지막으로 가장 긴 요소일 경우
        if (dp[nowIdx] < dp[i])
        {
            nowIdx = i;
        }
    }

    // 트레이싱
    while (nowIdx != -1)
    {
        vec.push_back(arr[nowIdx]);

        nowIdx = prevIdx[nowIdx];
    }

    reverse(vec.begin(), vec.end());

    cout << vec.size() << '\n';

    for (int elem : vec)
    {
        cout << elem << ' ';
    }

    return 0;
}
