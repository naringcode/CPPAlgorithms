#include <bits/stdc++.h>

// 백준 : 2309번

using namespace std;

int arr[9];
int sum;

vector<int> vec;
vector<int> res;

void combination(int n, int r, int depth)
{
    if (r == depth)
    {
        if (100 == sum - arr[vec[0]] - arr[vec[1]])
        {
            throw 'o';
        } 

        return;
    }

    for (int i = depth; i < n; i++)
    {
        vec.push_back(i);

        combination(n, r, depth + 1);

        vec.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 9; i++)
    {
        cin >> arr[i];

        sum += arr[i];
    }

    try
    {
        combination(9, 2, 0);
    } 
    catch (char ch)
    {
        for (int i = 0; i < 9; i++)
        {
            if (i == vec[0] || i == vec[1])
                continue;

            res.push_back(arr[i]);
        }
    }

    sort(res.begin(), res.end());

    for (int i : res)
    {
        cout << i << '\n';
    }

    return 0;
}