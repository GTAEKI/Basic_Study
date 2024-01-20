#include<bits/stdc++.h>
using namespace std;

const int V = 10;
int arr[V][V];
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};
int visited[V][V];

void dfs(int y,int x)
{
    for(int i = 0; i < 4; i++)
    {
       for( int j = 0; j<4; j++)
       {
            int ay = dy[i] + y;
            int ax = dx[j] + x;

            if(ay < 0||)
            {
                dfs(ay,ax);
            }
       }
    }   
}

int main()
{
    arr[1][2] = 1;
    arr[2][1] = 1;
    arr[1][3] =1;
    arr[3][1] = 1;
    arr[3][4] = 1;
    arr[4][3] = 1;

    for(int i = 0; i< V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            if(arr[i][j])
            {
                dfs(i,j);
            }
        }
    }
}