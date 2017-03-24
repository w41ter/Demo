#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 110000;
struct Node
{
    int l,r;
    int val;
};
Node tree[10*N];
void build(int o,int l,int r)
{
    tree[o].l = l,tree[o].r = r;
    tree[o].val = 0;
    if(l==r)
        return ;
    int mid = (l+r)/2;
    build(o+o,l,mid);
    build(o+o+1,mid+1,r);
}
void update(int o,int l,int r,int val)
{
    if(tree[o].l==l && tree[o].r==r)
    {
        tree[o].val|=val;
        return ;
    }
    int mid = (tree[o].l + tree[o].r)/2;
    if(mid>=r)
        update(o+o,l,r,val);
    else if(l>mid)
        update(o+o+1,l,r,val);
    else
    {
        update(o+o,l,mid,val);
        update(o+o+1,mid+1,r,val);
    }
}
int query(int o,int l,int r)
{
    if(tree[o].l==l && tree[o].r==r)
        return tree[o].val;
    int mid = (tree[o].l + tree[o].r)/2;
    if(mid>=r)
        return query(o+o,l,r);
    else if(l>mid)
        return query(o+o+1,l,r);
    else
    {
        return query(o+o,l,mid)&query(o+o+1,mid+1,r);
    }
}
vector<int> ans;
void solve(int o)
{
    if(o!=1)
        tree[o].val |= tree[o/2].val;
    //printf("%d %d %d %d\n",o,tree[o].l,tree[o].r,tree[o].val);
    if(tree[o].l==tree[o].r){
        ans.push_back(tree[o].val);
        return ;
    }
    solve(o+o);
    solve(o+o+1);
}
Node a[N];
int main()
{
    //freopen("Input.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].val);
        update(1,a[i].l,a[i].r,a[i].val);
    }
    int ok=1;
    for(int i=0;i<m;i++)
    {
        if(query(1,a[i].l,a[i].r)!=a[i].val)
        {
            ok=0;
            break;
        }
    }
    solve(1);
    if(ok){
        puts("YES");
        for(int i=0;i<ans.size();i++)
            printf("%d%c",ans[i],i==n?'\n':' ');
        ans.clear();
    }
    else
        puts("NO");
    return 0;
}
