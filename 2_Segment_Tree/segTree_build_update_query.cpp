#include <bits/stdc++.h>
using namespace std;
void build(int node,int start,int end, vector<int> &tree, vector<int> &a)
{
    if(start==end)
        tree[node]=a[start];
    else
    {
        int mid=(start+end)/2;
        build(2*node,start,mid,tree,a);
        build(2*node+1,mid+1,end,tree,a);

        tree[node] = min(tree[2*node], tree[2*node+1]);
    }
}
void update(int node,int start,int end,int idx,int val,vector<int> &tree)
{
    if(start==end)
        tree[node]=val;
    else
    {
        int mid=(start+end)/2;
        if(idx>=start&&idx<=mid)
            update(2*node,start,mid,idx,val,tree);
        else
            update(2*node+1,mid+1,end,idx,val,tree);

        tree[node] = min(tree[2*node], tree[2*node+1]);
    }
}
int query(int node,int start,int end,int l,int r, vector<int> &tree)
{
    if(l>end||start>r)
        return 100005;
    if(l<=start&&r>=end)
        return tree[node];

    int p1,p2;
    int mid=(start+end)/2;
    p1=query(2*node,start,mid,l,r,tree);
    p2=query(2*node+1,mid+1,end,l,r,tree);
    return min(p1, p2);
}
int main()
{
    int n,q;
    vector<int>a(n+1);
    vector<int>tree(4*n+4);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    build(1,1,n,tree,a);

    // Queries are of two types:
    // 1. qlr: print the min in subarray A[l:r]
    // 2. uxy: update A[x] = y;
    while(q--)
    {
        char b;
        int x,y;
        cin >> b >> x >> y;
        if(b=='q')
            cout << query(1,1,n,x,y,tree) << endl;
        else
        update(1,1,n,x,y,tree);
    }
    return 0;
}