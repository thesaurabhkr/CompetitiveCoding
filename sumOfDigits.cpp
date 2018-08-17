#include<bits/stdc++.h>
using namespace std;


long long int dp[16][140][2];
long long int a, b, s;
int sz1 = 0, sz2 = 0;
int arr1[16], arr2[16];
int arr[16];
int sz = 0;
long long int ans1, ans2;
long long int solve(int numDig, int sum, int constraint, int szz, int arrt[])
{
    if(numDig == szz)
    {
        if(sum == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if(dp[numDig][sum][constraint] != -1)
    {
        return dp[numDig][sum][constraint];
    }
    long long int ans = 0;
    if(constraint == 1)
    {
        for(int i=0; i<arrt[numDig]; i++)
        {
            ans += solve(numDig+1, sum-i, 0, szz, arrt);
        }
        ans += solve(numDig+1, sum-arrt[numDig], 1, szz, arrt);
    }
    else
    {
        for(int i=0; i<=9; i++)
        {
            ans += solve(numDig + 1, sum-i, 0, szz, arrt);
        }
    }
    dp[numDig][sum][constraint] = ans;
    return ans;
}

void reverseOrder(int ind)
{
    if(ind == 1)
    {
        for(int i=0; i<sz1/2; i++)
        {
            int tmp = arr1[i];
            arr1[i] = arr1[sz1-i-1];
            arr1[sz1-i-1] = tmp;
        }
    }
    else if(ind == 2)
    {
        for(int i=0; i<sz2/2; i++)
        {
            int tmp = arr2[i];
            arr2[i] = arr2[sz2-i-1];
            arr2[sz2-i-1] = tmp;
        }
    }
    else
    {
        for(int i=0; i<sz/2; i++)
        {
            int tmp = arr[i];
            arr[i] = arr[sz-i-1];
            arr[sz-i-1] = tmp;
        }
    }
}

int preprocess(long long int tmp, int arrtmp[])
{
    int szz = 0;
    while(tmp > 0)
    {
        arrtmp[szz++] = tmp%10;
        tmp = tmp/10;
    }
    return szz;
}

void binarySearch()
{
    long long int low = a, high = b, mid;

    while(high > low)
    {
        mid = (low + high)/2;
        memset(dp, -1, sizeof dp);
        sz = preprocess(mid, arr);
        reverseOrder(3);
        long long int ans = solve(0, s, 1, sz, arr);
        ans = ans - ans1;
        if(ans >= 1)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    sz = preprocess(low, arr);
    int tmp = 0;
    for(int i=0; i<sz; i++)
    {
        tmp += arr[i];
    }
    if(tmp == s)
    {
        cout << low << endl;
    }
    else
    {
        cout << high << endl;
    }
}



int main()
{
    cin >> a >> b >> s;
    if(b < a)
        swap(a, b);
    long long int tmp = a;
    sz1 = preprocess(a, arr1);
    sz2 = preprocess(b, arr2);
    int offset = 0, sumtmp = 0;
    for(int i=0; i<sz1; i++)
    {
        sumtmp += arr1[i];
    }
    if(sumtmp == s)
    {
        offset = 1;
    }
    reverseOrder(1);
    reverseOrder(2);

    long long int diff = 0;
    memset(dp, -1, sizeof dp);
    ans1 = solve(0, s, 1, sz1, arr1);
    memset(dp, -1, sizeof dp);
    ans2 = solve(0, s, 1, sz2, arr2);
    diff = ans2 - ans1 + offset;
    if(offset == 1)
    {
        cout << diff << endl;
        cout << a << endl;
    }
    else
    {
        cout << diff << endl;
        if(diff > 0)
        {
            binarySearch();
        }
    }
    return 0;
}