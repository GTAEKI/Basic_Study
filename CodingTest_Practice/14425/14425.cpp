#include<bits/stdc++.h>
using namespace std;

int N,M;
set<string> st;
string temp;
int cnt;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        cin >> temp;
        st.insert(temp);
    }
    
    for(int i = 0; i < M; i++)
    {
        cin >> temp;
        if(st.find(temp)!= st.end())
        {
            cnt++;
        }
        
    }
    
    cout << cnt;
    
    return 0;
}