#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll dp[94];

void fibo(ll n)
{
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
}

int main()
{
    memset(dp, -1, sizeof(dp));

    fibo(90);

    ll n;

    while (true)
    {
        cin >> n;

        cout << dp[n] << '\n';
    }
    
    return 0;
}
