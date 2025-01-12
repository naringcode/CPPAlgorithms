#include <bits/stdc++.h>

using namespace std;

vector<int> mySet = { 11, 22, 33, 44 };

vector<vector<vector<int>>> res;

void MakeAllSubsets(int idx, vector<int> subset)
{
    if (mySet.size() == idx)
    {
        res[subset.size()].push_back(subset);

        return;
    }

    // 원소 추가 X
    MakeAllSubsets(idx + 1, subset);

    // 원소 추가 O
    subset.push_back(mySet[idx]);

    MakeAllSubsets(idx + 1, subset);
}

int main()
{
    res.resize(5);

    MakeAllSubsets(0, {});

    for (auto& vecList : res)
    {
        for (auto& vec : vecList)
        {
            cout << " { ";

            for (int elem : vec)
            {
                cout << elem << ' ';
            }

            cout << "}\n";
        }
    }
    
    return 0;
}
