#include <bits/stdc++.h>

using namespace std;

struct Median
{
    // 그냥 큐가 아니라 우선순위 큐
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    void insert(int data)
    {
        if (0 == maxHeap.size())
        {
            maxHeap.push(data);

            return;
        }

        if (maxHeap.size() == minHeap.size())
        {
            if (data < get())
            {
                maxHeap.push(data);
            }
            else
            {
                minHeap.push(data);
            }

            return;
        }

        if (maxHeap.size() < minHeap.size())
        {
            if (data > get())
            {
                maxHeap.push(minHeap.top());

                minHeap.pop();
                minHeap.push(data);
            }
            else
            {
                maxHeap.push(data);
            }
        }
        else
        {
            if (data < get())
            {
                minHeap.push(maxHeap.top());

                maxHeap.pop();
                maxHeap.push(data);
            }
            else
            {
                minHeap.push(data);
            }
        }
    }

    double get()
    {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;

        if (maxHeap.size() < minHeap.size())
        {
            return minHeap.top();
        }
        else
        {
            return maxHeap.top();
        }        
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Median med;

    med.insert(1);
    cout << med.get() << '\n';
    
    med.insert(5);
    cout << med.get() << '\n';
    
    med.insert(2);
    cout << med.get() << '\n';
    
    med.insert(10);
    cout << med.get() << '\n';
    
    med.insert(40);
    cout << med.get() << '\n';

    return 0;
}
