#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll dp[94];

ll fibo(ll n)
{
    if (n < 2)
        return n;

    if (~dp[n])
        return dp[n];

    ll& ret = dp[n];
    
    ret = fibo(n - 1) + fibo(n - 2);

    return ret;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    ll n;

    while (true)
    {
        cin >> n;

        cout << fibo(n) << '\n';
    }
    
    return 0;
}
