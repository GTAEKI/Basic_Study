#include<bits/stdc++.h>
using namespace std;

int k;
long long retMax = -987654321,retMin = 987654321;
string sRetMax, sRetMin;
char mapp[10];
int visited[10];
string ans;

bool cal(int a, int b, char bracket)
{
    switch(bracket)
    {
        case '<':
            if(a < b) return true;
            else return false;
        case '>':
            if(a > b) return true;
            else return false;
    }
}

void dfs(int i,int cnt)
{
    if(ans.size() == k+1)
    {
        long long temp = stol(ans);
        retMax = max(retMax, temp);  
        retMin = min(retMin, temp);
        return;
    }
    
    for(int j = 0; j < 10; j++)
    {
        if(visited[j] || !cal(i,j,mapp[cnt])) continue;
        visited[j] = 1;
        ans += j+'0';
        dfs(j,cnt+1);
        int ansSize = ans.size();
        ans.erase(ans.begin()+(ansSize-1));
        visited[j] = 0;
    }
    return;
}

int main()
{
    cin >> k;
    for(int i = 0; i < k; i++)
    {
        cin >> mapp[i];
    }
    
    for(int i = 0; i < 10; i++)
    {
        visited[i] = 1;
        ans += i+'0';
        dfs(i,0);
        int ansSize = ans.size();
        ans.erase(ans.begin()+(ansSize-1));
        visited[i] = 0;
    }
    
    sRetMax = to_string(retMax);
    sRetMin = to_string(retMin);
    
    if(sRetMax.size() != k+1)
    {
        sRetMax = '0'+sRetMax;
    }
    if(sRetMin.size() != k+1)
    {
        sRetMin = '0' + sRetMin;
    }
    
    cout << sRetMax << "\n";
    cout << sRetMin << "\n";
    return 0;
}