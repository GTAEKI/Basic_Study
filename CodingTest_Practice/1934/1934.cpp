#include<bits/stdc++.h>
using namespace std;

int T;
int A,B;
vector<int> ans;

void Check(int a, int b, int num)
{
    if(a > b)
    {
        for(int i = b; i > 0; i--)
        {
            if(a%i == 0 && b % i == 0 && num % i == 0)
            {
                num /= i;
            }
        }
    }
    else 
    {
        for(int i = a; i > 0; i--)
        {
            if(a%i == 0 && b % i == 0 && num % i == 0)
            {
                num /= i;
            }
        }
    }
    
    ans.push_back(num);
}

int main()
{
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        cin >> A >> B;
        
        Check(A,B,A*B);
    }
    
    for(int i : ans)
    {
        cout << i << "\n";
    }
    return 0;
}