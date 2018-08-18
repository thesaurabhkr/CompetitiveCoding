#include <bits/stdc++.h>
using namespace std;
long long int l, r;
long long int dp[18][9*18 + 5][2];
int sz, arr[20];
long long int ans[9*18+5];
long long int mod = 1e9+7;

long long int solve(int ind, int sum, int constraint)
{
    if(ind == sz)
    {
        if(sum == 0)
        {
            return 1;
        }
        return 0;
    }
    if(dp[ind][sum][constraint] != -1)
        return dp[ind][sum][constraint];
    long long int summ = 0;
    if(constraint == 1)
    {
        for(int i=0; i<arr[ind]; i++)
        {
            summ += solve(ind+1, sum - i, 0);
        }
        summ += solve(ind+1, sum-arr[ind], 1);
    }
    else
    {
        for(int i=0; i<=9; i++)
        {
            summ += solve(ind+1, sum - i, 0);
        }
    }
    dp[ind][sum][constraint] = summ;
    return summ;
}

void processAndSolve(long long int a, long long int b)
{
    memset(ans, 0, sizeof ans);
    sz = 0;
    while(a>0)
    {
        arr[sz++] = a%10;
        a = a/10;
    }
    for(int i=0; i<sz/2; i++)
    {
        int tmp = arr[i];
        arr[i] = arr[sz-i-1];
        arr[sz-i-1] = tmp;
    }
    for(int i=1; i<=9*18; i++)
    {
        memset(dp, -1, sizeof dp);
        ans[i] = solve(0, i, 1);
    }
    sz = 0;
    b--;
    while(b>0)
    {
        arr[sz++] = b%10;
        b = b/10;
    }
    for(int i=0; i<sz/2; i++)
    {
        int tmp = arr[i];
        arr[i] = arr[sz-i-1];
        arr[sz-i-1] = tmp;
    }
    for(int i=1; i<=9*18; i++)
    {
        memset(dp, -1, sizeof dp);
        ans[i] = ans[i] - solve(0, i, 1);
    }
}

int main()
{
    int tc;
    cin >> tc;
    while(tc--)
    {
        cin >> l >> r;
        if(l > r)
        {
            swap(l, r);
        }
        processAndSolve(r, l);
        long long int sum = 0;
        for(int i=1; i<=9*18; i++)
        {
            for(int j=i+1; j<=9*18; j++)
            {
                if(__gcd(i, j) == 1)
                {
                    sum = (sum + (ans[i]%mod*ans[j]%mod)%mod)%mod;
                }
            }
        }
        cout << sum << endl;
    }
    return 0;
}