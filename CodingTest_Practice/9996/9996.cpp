#include <bits/stdc++.h>
using namespace std;

int a;
string rule;
string input;

bool check(string _input)
{
    if(rule[0] != _input[0] || 
       rule[rule.size()] != _input[_input.size()])
    {
        return false;
    }
    
    return true;
}


int main()
{
    cin >> a;
    cin >> rule;
    for(int i = 0; i < a; i++)
    {
        cin >> input;
        if(check(input))
        {
            cout << "DA" << "\n";
        }
        else
        {
            cout << "NE" << "\n";
        }
    }
}