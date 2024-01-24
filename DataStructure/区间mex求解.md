## 区间mex求解
### 简介
mex(l,r)表示区间(l,r)中最小的未出现过的自然数的值，可以通过权值线段树求解。

我们利用权值线段树维护每个数字最后出现的位置，得到root[n],即n颗权值线段树，对于(l,r)的询问，我们搜索root[r],树上二分找到满足最后出现位置< l的最小值，也就是mex(l,r)的值。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
const int maxn = 2e5+10;
int a[maxn];
struct NODE{
    int ls;
    int rs;
    int pos;
}tree[maxn*40];
int cnt = 0;
int root[maxn];
void push_up(int rt)
{
    int ls = tree[rt].ls;
    int rs = tree[rt].rs;
    tree[rt].pos = min(tree[ls].pos,tree[rs].pos);
    return;
}
void build(int l,int r)
{
    int rt = ++cnt;
    tree[rt].ls = l;
    tree[rt].rs = r;
    if(l == r){
        tree[rt].pos = 0;
        return;
    }
    int mid = (l+r)/2;
    build(l,mid);
    build(mid+1,r);
    push_up(rt);
}

void update(int pre,int&now,int l,int r,int v,int p)
{
    now = ++cnt;
    tree[now] = tree[pre];
    if(l == r){
        tree[now].pos = p;
        return;
    }
    int mid = (l+r)/2;
    if(v<=mid)update(tree[pre].ls,tree[now].ls,l,mid,v,p);
    else update(tree[pre].rs,tree[now].rs,mid+1,r,v,p);
    push_up(now);
    return;
}

int query(int rt,int l,int r,int L)
{
    if(l == r)return l;
    int mid = (l+r)/2;
    if(tree[tree[rt].ls].pos<L)return query(tree[rt].ls,l,mid,L);
    else return query(tree[rt].rs,mid+1,r,L);
}

void solve()
{
    cin>>n>>m;
    build(0,n);
    root[0] = 1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        update(root[i-1],root[i],0,n,a[i],i);
    }
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(root[r],0,n,l)<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while(t--){
        solve();
    }
    return 0;
}
```