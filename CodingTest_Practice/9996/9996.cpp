#include<bits/stdc++.h>
using namespace std;

int N;
string pattern;
vector<string> files;

int main()
{
    cin >> N;
    cin >> pattern;
    
    string front = pattern.substr(0,pattern.find('*'));
    string back = pattern.substr(pattern.find('*')+1);
    
    for(int i = 0; i < N; ++i)
    {
        string temp;
        cin >> temp;
        if(temp.size() >= back.size() && temp.find(front) == 0 && temp.substr(temp.size() - back.size()) == back)
        {
            cout << "DA" << "\n";   
        }
        else 
        {
            cout << "NE" << "\n";
        }
    }
    return 0;
}