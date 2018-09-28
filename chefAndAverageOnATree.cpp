//https://www.codechef.com/problems/L56AVG
//shauryakr
#include<bits/stdc++.h>
using namespace std;
int arr[100010];
vector<int> v[100010];
long double dp[100010][2];
long double b[100010];

void solve(int node, int parent= -1)
{
    vector<int> c;

    for(int child : v[node])
    {
        if(child != parent)
        {
            solve(child, node);
        }
    }

    dp[node][0] = dp[node][1] = -1*1e12+5;

    for(int child:v[node])
    {
        if(child != parent)
        {
            if(max(dp[child][0], dp[child][1]) < 0)
            {
                c.push_back(child);
            }
        }
    }

    if(c.size() > 2)
    {
        return;
    }

    

    if(c.size() == 0)
    {
        dp[node][0] = b[node];
        for(int child: v[node])
        {
            if(child != parent)
            {
                if(dp[node][0] < dp[child][0] + b[node])
                {
                    dp[node][0] = dp[child][0] + b[node];
                }
            }
        }

        pair<long double, long double> twomax = make_pair(-1*1e12+5, -1*1e12+5);
        for(int child: v[node])
        {
            if(child != parent)
            {
                if(dp[child][0] > twomax.first)
                {
                    twomax.second = twomax.first;
                    twomax.first = dp[child][0];
                }
                else
                {
                    if(twomax.second < dp[child][0])
                    {
                        twomax.second = dp[child][0];
                    }
                }
            }
        }
        if(dp[node][1] < twomax.first + twomax.second + b[node])
        {
            dp[node][1] = twomax.first + twomax.second + b[node];
        }
    }

    if(c.size() == 1)
    {
        dp[node][0] = dp[c[0]][0] + b[node];
        for(int child:v[node])
        {
            if(child != parent && child != c[0])
            {
                if(dp[node][1] < dp[child][0] + b[node] + dp[c[0]][0])
                {
                    dp[node][1] = dp[child][0] + b[node] + dp[c[0]][0];
                }
            }
        }
    }

    if(c.size() == 2)
    {
        dp[node][0] = -1*1e12+5;
        dp[node][1] = dp[c[0]][0] + b[node] + dp[c[1]][0];
        if(dp[node][1]<0)
        {
            dp[node][1] = -1*1e12+5;
        }
    }

    if(dp[node][1] < dp[node][0])
    {
        dp[node][1] = dp[node][0];
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;
        for(int i=1; i<=n; i++)
        {
            cin >> arr[i];
            v[i].clear();
            dp[i][0] = 0;
            dp[i][1] = 0;
        }
        for(int i=1; i<n; i++)
        {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        long double left = 0, right = 1e5+10;
        int t = 42;
        while(t--)
        {
            long double mid = (left + right)/2;
            for(int i=1; i<=n; i++)
            {
                b[i] = arr[i] - mid;
            }
            solve(1);
            if(dp[1][1]>=0)
                left = mid;
            else
                right = mid;
        }
        cout.precision(7);
        cout << fixed << right << endl;
    }
    return 0;
}