//https://www.codechef.com/COOK98A/problems/UPDOTR
//shauryakr

#include<bits/stdc++.h>
using namespace std;
int arr[1000010];
vector<int> v[1000010];
int parent[1000010][30];

void dfs(int node, int prev)
{
    parent[node][0] = prev;
    for(int i=1; i<=20; i++)
    {
        parent[node][i] = parent[parent[node][i-1]][i-1];
    }
    if(arr[node] > arr[prev])
    {
        prev = node;
    }
    for(auto child : v[node])
    {
        dfs(child, prev);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n,q;
        cin >> n;
        for(int i = 1; i<=n; i++)
        {
            v[i].clear();
            cin >> arr[i];
        }
        for(int i=2; i<=n; i++)
        {
            int a, b;
            cin >> a;
            v[a].push_back(i);
        }
        dfs(1, 0);
        int pr = 0;
        cin >> q;
        while(q--)
        {
            int a, b;
            cin >> a >> b;
            int v = a ^ pr;
            int w = b ^ pr;

            int ans = 0;
            int tmpv = v;
            if(w > max(arr[v], arr[parent[v][0]]))
            {
                pr = 0;
                cout << 0 << endl;
                continue;

            }
            for(int i=20; i>=0; i--)
            {
                if(parent[v][i] != 0)
                {
                    if(arr[parent[v][i]] > w)
                    {
                        v = parent[v][i];
                        ans += (1<<i);
                    }
                }
            }

            if(arr[tmpv] > max(w, arr[parent[tmpv][0]]))
            {
                ans++;
            }
            cout << ans << endl;
            pr = ans;
        }
    }
    return 0;
}