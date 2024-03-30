#include<bits/stdc++.h>
using namespace std;
const int max_n = 500000;
int visited[2][max_n+4], a, b, ok, turn = 1;
int main()
{
    cin >> a >> b;
    if(a == b){cout << 0; return 0;}
    queue<int> que;
    visited[0][a]  = 1;
    que.push(a);
    while(que.size())
    {
        b += turn;
        if(b > max_n) break;
        if(visited[turn % 2][b])
        {
            ok = true;
            break;
        }
        int qSize = que.size();
        for(int i = 0; i < qSize; i++)
        {
            int x = que.front(); que.pop();
            for(int nx : {x+1, x-1, x*2})
            {
                if(nx < 0 || nx > max_n || visited[turn %2][nx]) continue;
                visited[turn % 2][nx] = visited[(turn +1) % 2][x] +1;
                if(nx == b)
                {
                    ok = 1;break;
                }
                que.push(nx);
            }
            if(ok) break;
        }
        if(ok) break;
        turn++;
    }
    if(ok) cout << turn << "\n";
    else cout << -1 << "\n";
    return 0;
}