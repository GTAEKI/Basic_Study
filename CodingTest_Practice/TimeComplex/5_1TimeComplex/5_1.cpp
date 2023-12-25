#include<bits/stdc++.h>
using namespace std;

int n, a[1004], cnt;
int go(int l, int r)
{
    cnt++;
    if(l == r) return a[l];
    int mid = (l + r) / 2;
    int sum = go(l, mid) + go(mid + 1, r);
    return sum;
}

int main()
{
    int cnt2 = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cnt2++;
        a[i-1] = i;
    }
    int sum = go(0,n-1);
    cout << sum << "\n";
    cout << "시간복잡도" << cnt+cnt2 << "\n";
}