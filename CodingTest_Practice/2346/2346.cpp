#include<bits/stdc++.h>
using namespace std;

int N;
bool isFront = true;
deque<int> dq;

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        dq.push_back(i);
    }
    
    cout << dq.front() << " "; // 1번 풍선 터뜨림
    dq.pop_front();
    
    while(dq.size() != 0)
    {
        int temp;
        cin >> temp;
        
        if(temp > 0)
        {
            for(int i = 0; i < temp; i++)
            {
                dq.push_back(dq.front());
                dq.pop_front();
            }
            cout << dq.back() << " ";
            dq.pop_back();
        }
        else 
        {
            temp = abs(temp);
            for(int i = 0; i < temp; i++)
            {
                dq.push_front(dq.back());
                dq.pop_back();
            }
            cout << dq.front() << " ";
            dq.pop_front();
        }
    }
    return 0;
}