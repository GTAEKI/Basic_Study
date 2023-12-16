#include<bits/stdc++.h>
using namespace std;

int H,W;
int arr[104][104];
char c;

int main()
{
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            cin >> c;
            if(c=='c')
            {
                arr[i][j] = 0;
                cout << arr[i][j] << " ";
            }
            else
            {
                if(j == 0 || arr[i][j-1] == -1)
                {
                    arr[i][j] = -1;
                    cout << arr[i][j] << " ";
                }
                else
                {
                    arr[i][j] = arr[i][j-1]+1;
                    cout << arr[i][j] << " ";
                }
            }
        }
        cout << "\n";
    }  
}