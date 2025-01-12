#include <bits/stdc++.h>

using namespace std;

int main()
{
    const int n = 4;

    string arr[n] = { "A", "B", "C", "D" };

    for (int i = 0; i < (1 << n); i++)
    {
        string res = "";

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                res += (arr[j] + " ");
            }
        }

        cout << i << " : " << res << '\n';
    }

    return 0;
}
