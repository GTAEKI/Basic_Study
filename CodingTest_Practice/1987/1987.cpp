#include<bits/stdc++.h>
using namespace std;

int R,C,turn,check;
const int MAX = 20;
int ret = -987654321;
char gameMap[MAX+1][MAX+1];
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};
vector<char> arr;

void dfs(int y,int x)
{
    if(check == 1)
    {
        ret = max(ret, turn);
    }
    
    check = 0;
    turn ++;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(ny < 0 || nx < 0 || ny > MAX || nx > MAX)
        {
            turn--;
            arr.pop_back();
            continue;
        } 
        auto it = find(arr.begin(),arr.end(),gameMap[ny][nx]);
        if(it != arr.end())
        {
            turn --;
            arr.pop_back();
            continue;  
        } 
        arr.push_back(gameMap[ny][nx]);
        check = 1;
        dfs(ny,nx);
    }
}

int main()
{
    cin >> R >> C;
    for(int j = 0; j < R; j++)
    {
        for(int i = 0; i < C; i++)
        {
            cin >> gameMap[j][i];
        }
    }
    
    arr.push_back(gameMap[0][0]);
    dfs(0,0);
    
    cout << ret;
    return 0;
}