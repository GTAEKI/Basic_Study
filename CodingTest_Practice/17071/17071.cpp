#include<bits/stdc++.h>
using namespace std;

int N,K,cnt;
const int MAX = 500001;
int ret = 987654321;
int visited[MAX];

int calMoveDist(int time)
{
    int temp = 0;
    while(time--)
    {
        temp += time;
    }
    return temp;
}

int main()
{
    bool check = false;
    cin >> N >> K;
    
    queue<int> que;
    que.push(N);
    visited[N] = 1;
    while(que.size())
    {
        int now = que.front();
        que.pop();
        int nowK = K + calMoveDist(visited[now]);
        if (nowK > 500000) break;
        else if(now == nowK)
        {
            check = true;
            ret = visited[now] - 1;
            break;
        }
        
        for(int next: {now -1, now +1, now*2 })
        {
            if(next < 0 || next >= MAX || visited[next]) continue;
            visited[next] = visited[now] + 1;
            que.push(next);
        }
    }
    
    if(!check)
    {
        cout << -1;
    }
    else 
    {
        cout << ret;
    }
    return 0;
}