//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/pikachu-vs-team-rocket-56b518ee/
#include<bits/stdc++.h>
using namespace std;
const int N = 600005;
int arr[600010];
int tree[4*N];
int BIT[N];

//These variables store the index of the first and the last element in the arr.
int startIndex, endIndex;

void buildTree(int node, int start, int ends)
{
    if(start == ends)
    {
        tree[node] = arr[start];
        return;
    }
    buildTree(node*2, start, (start+ends)/2);
    buildTree(node*2+1, (start+ends)/2+1, ends);
    tree[node] = max(tree[node*2], tree[node*2+1]);
}

void updateTree(int node, int start, int ends, int l, int r, int val)
{
    if(start > r || ends < l)
        return;
    if(start >= l && ends <= r)
    {
        tree[node] = val;
        return;
    }
    int mid = (start + ends)/2;
    updateTree(node*2, start, mid, l, r, val);
    updateTree(node*2+1, mid+1, ends, l, r, val);
    tree[node] = max(tree[node*2], tree[node*2+1]);
}

int queryTree(int node, int start, int ends, int l, int r)
{
    if(start > r || ends < l)
        return 0;
    if(start >= l && ends <= r)
    {
        return tree[node];
    }
    int mid = (start + ends)/2;
    return max(queryTree(node*2, start, mid, l, r), queryTree(node*2+1, mid+1, ends, l, r));
}

void updateBit(int ind, int val)
{
    while(ind < N)
    {
        BIT[ind] += val;
        ind += ind&-ind;
    }
}

int getBit(int ind)
{
    int ans = 0;
    while(ind > 0)
    {
        ans += BIT[ind];
        ind -= ind&-ind;
    }
    return ans;
}

//Using Binary Search on BIT we find the index of the pos element in the arr.
//e.g. We can find the index of the 1st or 2nd element in the arr.
int binarySearchOnBit(int pos)
{
    int low = startIndex, high = endIndex, mid;
    while(high - low > 1)
    {
        mid = (low + high)/2;
        int tmp = getBit(mid);
        if(tmp >= pos)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    int newPos;
    if(getBit(low) == pos)
    {
        newPos = low;
    }
    else
    {
        newPos = high;
    }
    return newPos;
}

int main()
{
    int n, q;
    cin >> n >> q;
    int treeSize = 2*q + n;
    for(int i=1; i<=n; i++)
    {
        cin >> arr[i+q];
        updateBit(i+q, 1);
    }
    startIndex = q+1, endIndex = q+n;
    buildTree(1, 1, treeSize);
    while(q--)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int l, r;
            cin >> l >> r;
            int ll = binarySearchOnBit(l);
            int rr = binarySearchOnBit(r);
            cout << queryTree(1, 1, treeSize, ll, rr) << endl;
        }
        else
        {
            int typeAgain, k;
            cin >> typeAgain >> k;
            int ind = binarySearchOnBit(k);
            updateBit(ind, -1);
            updateTree(1, 1, treeSize, ind, ind, 0);
            if(typeAgain == 1)
            {
                endIndex++;
                arr[endIndex] = arr[ind];
                arr[ind] = 0;
                updateBit(endIndex, 1);
                updateTree(1, 1, treeSize, endIndex, endIndex, arr[endIndex]);
            }
            else
            {
                startIndex--;
                arr[startIndex] = arr[ind];
                arr[ind] = 0;
                updateBit(startIndex, 1);
                updateTree(1, 1, treeSize, startIndex, startIndex, arr[startIndex]);
            }
        }
    }
    return 0;
}