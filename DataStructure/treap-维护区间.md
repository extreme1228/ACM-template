## Treap维护区间信息
### 简介
treap 维护区间信息时，本质上treap树此时不再属于一个严格的二叉搜索树，更像是一种类似于线段树的数据结构，但所使用的节点一共只有n个。

### 区间重新组合
这里的treap支持区间翻转，重新组合，重新组合的顺序由merge的先后顺序规定，如果将区间分为x,y,z三部分，需要重新组合为y,z,x;那么代码应该为:
```cpp
root = merge(merge(y,z),x);
```
这样最后中序遍历最后的结构也就是按顺序的yzx

### 区间翻转
如果要进行区间翻转操作，那么可以类似线段树定义懒标记，同时定义下传函数，该例题也被称为文艺平衡树，示例代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(233);
const int maxn = 1e5+10;
typedef long long ll;

struct NODE{
    int ls,rs;//lchild and rchild
    int val,pri,siz;//val = 节点值，pri = 节点优先级，siz = 节点子树大小
    bool rev;
}trp[maxn];
int cnt,root;
int newnode(int val)
{
    cnt++;
    trp[cnt].ls = trp[cnt].rs = 0;
    trp[cnt].val = val;
    trp[cnt].pri = rnd();
    trp[cnt].siz = 1;
    trp[cnt].rev = false;
    return cnt;
}
void update(int rt)
{
    int lc = trp[rt].ls;
    int rc = trp[rt].rs;
    trp[rt].siz = trp[lc].siz + trp[rc].siz + 1;
    return;
}
void push_down(int rt)
{
    if(trp[rt].rev){
        swap(trp[rt].ls,trp[rt].rs);
        trp[trp[rt].ls].rev^=1;
        trp[trp[rt].rs].rev^=1;
        trp[rt].rev = false;
    }
    return;
}

//按大小分裂，分裂出前k个节点组成的treap树为x，其余的节点组成的treap树为y
void split(int rt,int k,int&x,int&y)
{
    if(!rt){
        x = y = 0;
        return;
    }
    push_down(rt);
    if(trp[trp[rt].ls].siz<k){
        x = rt;
        split(trp[rt].rs,k - trp[trp[rt].ls].siz - 1,trp[rt].rs,y);
        update(rt);
    }
    else{
        y = rt;
        split(trp[rt].ls,k,x,trp[rt].ls);
        update(rt);
    }
    return;
}

//这里merge时的先后顺序决定了最后中序遍历的最终结果
int merge(int a,int b)
{
    if(!a||!b)return a|b;
    if(trp[a].pri<trp[b].pri){
        push_down(a);
        trp[a].rs = merge(trp[a].rs,b);
        update(a);
        return a;
    }
    else{
        push_down(b);
        trp[b].ls = merge(a,trp[b].ls);
        update(b);
        return b;
    }
}
void reverse(int l,int r)
{
    int x,y,z;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    trp[y].rev^=1;
    root = merge(merge(x,y),z);
    return;
}
void dfs(int rt)
{
    if(!rt)return;
    push_down(rt);
    dfs(trp[rt].ls);
    cout<<trp[rt].val<<" ";
    dfs(trp[rt].rs);
    return;
}
void solve()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        root = merge(root,newnode(i));
    }
    for(int i =1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        reverse(l,r);
    }
    dfs(root);
    return;
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
### treap树上二分（维护区间信息）
同时treap还可以定义区间信息(区间最大值)，利用维护的区间信息在treap树上二分
(例如：维护区间max，可以二分寻找到区间中第一个>k的位置)示例如下：
```cpp
struct NODE{
    int ls,rs,val,pri,max_val,siz;
    vector<int>ans;
}trp[maxn];
int cnt,root;
void update(int rt)
{
    int lchild = trp[rt].ls;
    int rchild = trp[rt].rs;
    trp[rt].max_val = max(trp[rt].val,max(trp[lchild].max_val,trp[rchild].max_val));
    trp[rt].siz = trp[lchild].siz + trp[rchild].siz + 1;
    return;
}
//split为核心函数，在树上二分找到第一个大于k的节点，通过b传出，之前的treap树以a为根，之后的treap树以c为根。
void split(int rt,int k,int &a,int &b,int &c)
{
    int lchild = trp[rt].ls;
    int rchild = trp[rt].rs;
    if(trp[lchild].max_val<=k){
        if(trp[rt].val>k){
            a = lchild;
            b = rt;
            trp[b].ls = trp[b].rs = 0;
            update(b);
            c = rchild;
        }
        else{
            a = rt;
            split(rchild,k,trp[a].rs,b,c);
            update(a);
        }
    }
    else{
        c = rt;
        split(lchild,k,a,b,trp[c].ls);
        update(c);
    }
    return;
}
```
