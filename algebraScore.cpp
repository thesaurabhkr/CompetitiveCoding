#include <bits/stdc++.h>
using namespace std;
long long int arr[500];
char op[500];
int main() {
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;
        int j = 1, k=1;
        for(int i=1; i<=n+(n-1); i++)
        {
            if(i%2)
            {
                cin >> arr[j++];	
            }
            else
            {
                cin >> op[k++];
            }
        }
        long long int minVal[210][210], maxVal[210][210];
        memset(minVal, 0, sizeof minVal);
        memset(maxVal, 0, sizeof maxVal);
        
        for(int i=1; i<=n; i++)
        {
            minVal[i][i] = arr[i];
            maxVal[i][i] = arr[i];
        }
        
        for(int s=2; s<=n; s++)
        {
            for(int i = 1, j = s; j<= n; i++, j++)
            {
                long long int minn = 1e13;
                long long int maxx = -10000000000000;
                
                for(int k = i; k<= j-1; k++)
                {
                    if(op[k] == '+')
                    {
                        long long int a = minVal[i][k] + minVal[k+1][j];
                        long long int b = minVal[i][k] + maxVal[k+1][j];
                        long long int c = maxVal[i][k] + minVal[k+1][j];
                        long long int d = maxVal[i][k] + maxVal[k+1][j];
                        minn = min(minn, min(a, min(b, min(c, d))));
                        maxx = max(maxx, max(a, max(b, max(c, d))));
                    }
                    else
                    {
                        long long int a = minVal[i][k] - minVal[k+1][j];
                        long long int b = minVal[i][k] - maxVal[k+1][j];
                        long long int c = maxVal[i][k] - minVal[k+1][j];
                        long long int d = maxVal[i][k] - maxVal[k+1][j];
                        minn = min(minn, min(a, min(b, min(c, d))));
                        maxx = max(maxx, max(a, max(b, max(c, d))));
                    }
                }
                minVal[i][j] = minn;
                maxVal[i][j] = maxx;
            }
        }
        cout << maxVal[1][n] << endl;
    }
    return 0;
} 