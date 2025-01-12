#include <bits/stdc++.h>

using namespace std;

// Time Complexity : O(N^2)
//
// 최장 길이만 구함

int n;

int arr[1004];
int dp[1004];

int res;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // dp에 담기는 것은 해당 인덱스가 최장 증가 부분 수열이 될 때의 길이
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;

        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1); // 이전 길이를 이어서 표현 가능
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        res = max(res, dp[i]);
    }

    cout << res;

    return 0;
}
