#include <bits/stdc++.h>

using namespace std;

// Time Complexity : O(NlogN)
//
// 길이와 수열을 모두 구함

constexpr int INIT_ELEM = -1'999'999'999;

int n;

int arr[1'000'004];
int lis[1'000'004];
int maxLen[1'000'004]; // 최장 증가 부분 수열에서의 길이(길이인데 인덱스가 맞는 듯)

int len;

vector<int> vec;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(lis, lis + 1'000'004, INIT_ELEM);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        int* lower = lower_bound(lis, lis + len, arr[i]);

        if (INIT_ELEM == *lower)
        {
            len++;
        }

        *lower = arr[i];

        maxLen[i] = lower - lis; // 포인터의 거리 연산임
    }

    // 가장 큰 것부터 찾고 -> 그 다음 큰 것을 찾고...
    len--;

    for (int i = n - 1; i >= 0; i--)
    {
        if (len == maxLen[i])
        {
            vec.push_back(arr[i]);

            len--;
        }
    }

    reverse(vec.begin(), vec.end());

    cout << vec.size() << '\n';

    for (int elem : vec)
    {
        cout << elem << ' ';
    }

    return 0;
}
