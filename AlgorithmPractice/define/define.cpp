#include <bits/stdc++.h>

using namespace std;

#define APPLE 10
#define macro(x,n) for(int x = 0; x < n; x++)

int main()
{
    cout << APPLE << '\n';
    int j = 1;
    macro(i,5)
    {
        j += i;
    }
    cout << j << '\n';
    return 0;
}