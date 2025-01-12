#include <bits/stdc++.h>

using namespace std;

int CountDigits(int num)
{
    return int(log10(num) + 1);
}

int GetPlaceValue(int num)
{
    return int(pow(10, int(log10(num))));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << "9 : " << CountDigits(9) << '\n';
    cout << "10 : " << CountDigits(10) << '\n';
    cout << "11 : " << CountDigits(11) << '\n';

    cout << "99 : " << CountDigits(99) << '\n';
    cout << "100 : " << CountDigits(100) << '\n';
    cout << "101 : " << CountDigits(101) << '\n';

    cout << "999 : " << CountDigits(999) << '\n';
    cout << "1000 : " << CountDigits(1000) << '\n';
    cout << "1001 : " << CountDigits(1001) << '\n';

    cout << '\n';

    cout << "9 : " << GetPlaceValue(9) << '\n';
    cout << "10 : " << GetPlaceValue(10) << '\n';
    cout << "11 : " << GetPlaceValue(11) << '\n';

    cout << "99 : " << GetPlaceValue(99) << '\n';
    cout << "100 : " << GetPlaceValue(100) << '\n';
    cout << "101 : " << GetPlaceValue(101) << '\n';

    cout << "999 : " << GetPlaceValue(999) << '\n';
    cout << "1000 : " << GetPlaceValue(1000) << '\n';
    cout << "1001 : " << GetPlaceValue(1001) << '\n';

    return 0;
}
