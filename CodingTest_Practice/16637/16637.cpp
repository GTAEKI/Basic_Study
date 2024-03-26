#include<bits/stdc++.h>
using namespace std;

int oper(char a, int b, int c);

int N, ret = -987654321;
string S;
vector<int> num;
vector<char> oper_str;

void go(int here, int _num)
{
    cout << here << ":" << _num << "\n";
    if(here == num.size() -1)
    {
        ret = max(ret, _num);
        return;
    }
    go(here + 1, oper(oper_str[here], _num, num[here+1]));
    if(here + 2 <= num.size() -1)
    {
        int temp = oper(oper_str[here+1], num[here + 1], num[here+2]);
        go(here + 2, oper(oper_str[here], _num, temp));
    }
    return;
}

int main()
{
    cin >> N;
    cin >> S;
    for(int i = 0; i < N; ++i)
    {
        if(i%2 == 0) num.push_back(S[i] - '0');
        else oper_str.push_back(S[i]);
    }
    go(0,num[0]);
    cout << ret << "\n";
    return 0;
}


int oper(char a, int b, int c)
{
    if(a == '+') {return b+c;}
    if(a == '-') {return b-c;}
    if(a == '*') {return b*c;}
    return 0;
}