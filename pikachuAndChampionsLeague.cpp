//Distance Query
#include <bits/stdc++.h>

using namespace std;
vector<pair<int, int> > v[500010];
int visited[500010], parent[500010], level[500010], root, dist[500010];
int p[500010][20], aa, bb;
int arr[200010];

//This function is used to calculate the level of all the nodes taking 1 as the root
//and also the distance of the nodes which are given.
void calcLevel(int node, int lev, int distance)
{
    level[node] = lev;
    visited[node] = 1;
    for(int i=0; i<v[node].size(); i++)
    {
        if(visited[v[node][i].first]!=1)
        {
            parent[v[node][i].first] = node;
            calcLevel(v[node][i].first, lev+1, v[node][i].second);
        }
    }
}

//This function finds the Lowest common Ancestor in Log(n) after the precomputations.
int LCA(int P, int Q)
{

    if(level[P]<level[Q])
    {
        int tmp = P;
        P = Q;
        Q = tmp;
    }

    //Finding the height of the tree.
    int log;
    for(log = 1; 1<<log <= level[P]; log++);
    log--;

    //Finding the ancestor of P in the level of Q
    for(int i=log; i>=0; i--)
    {
        if(level[P] - (1<<i) >= level[Q])
        {
            P=p[P][i];
        }
    }


    if(P==Q)
        return P;

    //If one is not the ancestor of the other.
    for(int i=log; i>=0; i--)
    {
        if(p[P][i]!=-1 && p[P][i] != p[Q][i])
        {
            P = p[P][i];
            Q = p[Q][i];
        }
    }
    return parent[P];
}


int main()
{
    int n, q;
    cin >> n >> q;
    for(int i=1; i<n; i++)
    {
        int a , b, c = 1;
        cin >> a >> b ;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }
    root = 1;
    parent[1] = -1;
    calcLevel(1, 0, -1);

    memset(p, -1, sizeof p);
    //The first  ancestor of every node is parent[node].
    for(int i=1; i<=n; i++)
    {
        p[i][0]= parent[i];
    }

    //Precomputations in nlog(n).
    for(int j=1; 1<<j <= n; j++)
    {
        for(int i=1; i<=n; i++)
        {
            if(p[i][j-1] != -1)
            {
                p[i][j] = p[p[i][j-1]][j-1];
            }
        }
    }
    while(q--)
    {
        int k;
        cin >> k;
        for(int i=0; i<k; i++)
        {
        	cin >> arr[i];
        }
        int mx = 0, farthestVertex = 0;
        for(int i=1; i<k; i++)
        {
            int l = LCA(arr[i], arr[0]);
            int dis = level[arr[i]] + level[arr[0]] - 2*level[l];
            if(dis > mx)
            {
                mx = dis;
                farthestVertex = i;
            }
        }
        mx = 0;
        for(int i = 0; i<k; i++)
        {
            int l = LCA(arr[i], arr[farthestVertex]);
            int dis = level[arr[i]] + level[arr[farthestVertex]] - 2*level[l];
            mx = max(mx, dis);
        }
        cout << mx << endl;
    }
    return 0;
}
