#include <bits/stdc++.h>
using namespace std;
long long int n, p, k, intSum;


int main()
{
    int tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> p;
        intSum = (n*(n+1))/2;
        long long int ans = p/intSum;
        p = p%intSum;

        if(p == 0)
        {
            cout << ans << endl;
            continue;
        }
        long double l = 0, r = 1, mid, e = 1e-6;
        while(l < r)
        {
            mid = (long double)(l+r)/(long double)2;
            long long int sum = 0;
            for(int i=1; i<=n; i++)
            {
                sum += (long long int)((long double)(i) * (long double)(mid));
            }
            if(sum == p)
            {
                break;
            }
            else if(sum < p)
            {
                l = mid + e;
            }
            else
            {
                r = mid - e;
            }
        }
        if(l < r)
        {
            cout << ans << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}