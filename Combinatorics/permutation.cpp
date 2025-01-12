#include <bits/stdc++.h>

// 백준 : 2309번

using namespace std;

int arr[9];

void permutation(int n, int r, int depth)
{
    if (r == depth)
    {
        if (100 == accumulate(arr, arr + 7, 0))
        {
            sort(arr, arr + 7);

            for (int i = 0; i < 7; i++)
            {
                cout << arr[i] << '\n';
            }

            exit(0);
        }

        return;
    }

    for (int i = depth; i < n; i++)
    {
        swap(arr[i], arr[depth]);

        permutation(n, r, depth + 1);

        swap(arr[i], arr[depth]);
    }
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        cin >> arr[i];
    }

    permutation(9, 7, 0);

    return 0;
}