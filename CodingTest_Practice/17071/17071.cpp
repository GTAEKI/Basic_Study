#include<bits/stdc++.h>
using namespace std;

int N,K,turn,check;
const int MAX = 500000;
int visited[2][MAX+1];

int main()
{
    cin >> N >> K;
    if(N==K){cout << 0; return 0;}
    queue<int> que;
    que.push(N);
    visited[0][N] = 1;
    while(que.size())
    {
        K += turn;
        if(K > MAX) break;
        else if(visited[turn%2][K])
        {
            check = 1;
            break;
        }
        
        int qSize = que.size();
        for(int i = 0; i < qSize; i++)
        {
            int now = que.front();
            que.pop();
            for(int next : {now-1,now+1,now*2})
            {
                if(next < 0 || next > MAX) continue;
                else if(visited[turn%2][next]) continue;
                visited[turn%2][next] = visited[(turn+1)%2][now] + 1;
                if(next == K)
                {
                    check = 1;
                    break;
                }
                que.push(next);
            }
            if(check) break;
        }
        if(check) break;
        turn++;
    }
    
    if(check) cout << turn;
    else cout << -1;
    return 0;
}