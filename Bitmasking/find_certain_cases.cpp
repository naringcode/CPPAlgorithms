#include <bits/stdc++.h>

using namespace std;

const int n = 4;

string arr[4] = { "A", "B", "C", "D" };

void go(int num)
{
    string res = "";

    for (int i = 0; i < n; i++)
    {
        if (num & (1 << i))
        {
            res += arr[i] + " ";
        }
    }

    cout << res << '\n';
}

int main()
{
    for (int i = 1; i < n; i++)
    {
        go(1 | (1 << i)); // with A
    }

    return 0;
}
