
// 스플릿 함수 구현 연습
#include<bits/stdc++.h>
using namespace std;

vector<string> Split(string sentence, string delimeter)
{
    int pos = 0;
    vector<string> ret;
    while((pos = sentence.find(delimeter)) != string::npos)
    {
        ret.push_back(sentence.substr(0,pos));
        sentence.erase(0,pos+delimeter.length());
    }
    ret.push_back(sentence);
    return ret;
}

int main()
{
    string ans = "안녕 나는 지금 split함수를 만드는 연습을 하는중이야.";
    for (auto a : Split(ans, " "))
    {
        cout << a << "\n";
    }
    return 0;
}
