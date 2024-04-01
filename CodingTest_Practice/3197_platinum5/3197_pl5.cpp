#include<bits/stdc++.h>
using namespace std;

int R,C,lX,lY,turn,check;
const int MAX = 1500;
char gameMap[MAX+1][MAX+1];
int visited[MAX+1][MAX+1];
int lvisited[MAX+1][MAX+1];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
queue<pair<int,int>> que;

void dfs(int y, int x)
{
    visited[y][x] = 1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx > MAX || ny > MAX || visited[ny][nx]) continue;
        if(gameMap[ny][nx] == 'X')
        {
            que.push({ny,nx});
            gameMap[ny][nx] = '.';
            visited[ny][nx] = 1;
        }
        else if(gameMap[ny][nx] == '.')
        {
            dfs(ny,nx);
        }
    }
}

void findOtherL(int y, int x)
{
    if(check) return;
    
    visited[y][x] = 1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx > MAX || ny > MAX || visited[ny][nx]) continue;
        if(gameMap[ny][nx] == '.')
        {
            dfs(ny,nx);
        }
        else if(gameMap[ny][nx] == 'L')
        {
            check = 1;
            return;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> R >> C;
    for(int j = 0; j < R; j++)
    {
        for(int i = 0; i < C; i++)
        {
            cin >> gameMap[j][i];
            if(gameMap[j][i] == 'L')
            {
                lX = i;
                lY = j;
            }
        }
    }
    
    findOtherL(lY,lX);
    if(check)
    {
        cout << 0;
        return 0;
    }
    
    
    for(int j = 0; j < R; j++)
    {
        for(int i = 0; i < C; i++)
        {
            if(visited[j][i] == 0 && gameMap[j][i] == '.')
            {
                dfs(j,i);
            }
        }
    }
    
    memset(lvisited,0,sizeof(lvisited));
    findOtherL(lY,lX);
    if(check)
    {
        cout << 1;
        return 0;
    }
    
    while(que.size())
    {
        int qSize = que.size();
        int tX = que.front().second;
        int tY = que.front().first;
        que.pop();
        
        for(int i = 0; i < qSize; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                int ny = tY + dy[j];
                int nx = tX + dx[j];
                if(nx < 0 || ny < 0 || nx > MAX || ny > MAX || visited[ny][nx]) continue;
                if(gameMap[ny][nx] == 'X')
                {
                    que.push({ny,nx});
                    gameMap[ny][nx] = '.';
                    visited[ny][nx] = 1;
                }
            }
        }
        turn++;
        memset(lvisited,0,sizeof(lvisited));
        findOtherL(lY,lX);
        if(check) break;
    }
    
    cout << turn;
    return 0;
    
}