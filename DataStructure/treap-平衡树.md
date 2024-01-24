### Treap实现平衡树
这里的treap实现的是一般的平衡树，本质上treap树借用节点优先级的方法使得构建出的二叉搜索树的平均高度达到了log(n)。
```cpp
/*
treap实现的普通平衡树模版，支持
(1)插入一个数 
(2)删除一个数 （若有多个相同的数，应只删除一个）。
(3)定义排名为比当前数小的数的个数 + 1 查询 x 的排名。
(4)查询数据结构中排名为 x 的数。
(5)求 x 的前驱（前驱定义为小于 x，且最大的数）。
(6)求 x 的后继（后继定义为大于 x，且最小的数）。
题目数据保证5,6中一定存在x的前驱或者后继，不保证3,5,6操作中的x一定在出现过
注意treap实现的平衡树中同一个值可能对应多个树上的节点
*/

#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(233);
const int maxn = 1e5+10;
typedef long long ll;

struct NODE{
    int ls,rs;//lchild and rchild
    int val,pri,siz;//val = 节点值，pri = 节点优先级，siz = 节点子树大小
}trp[maxn];
int cnt,root;
int newnode(int val)
{
    cnt++;
    trp[cnt].ls = trp[cnt].rs = 0;
    trp[cnt].val = val;
    trp[cnt].pri = rnd();
    trp[cnt].siz = 1;
    return cnt;
}
void update(int rt)
{
    int lc = trp[rt].ls;
    int rc = trp[rt].rs;
    trp[rt].siz = trp[lc].siz + trp[rc].siz + 1;
    return;
}

//按值分裂，分裂成x,y两棵treap树，满足x上的所有节点值<=k,y上的所有节点值>k
void split(int rt,int k,int&x,int&y)
{
    if(!rt){
        x = y = 0;
        return;
    }
    if(trp[rt].val<=k){
        x = rt;
        split(trp[x].rs,k,trp[x].rs,y);
        update(x);
    }
    else{
        y = rt;
        split(trp[y].ls,k,x,trp[y].ls);
        update(y);
    }
    return;
}

//这里merge时一定要保证a子树上的所有权值<=b子树上的所有权值
int merge(int a,int b)
{
    if(!a||!b)return a|b;
    if(trp[a].pri<trp[b].pri){
        trp[a].rs = merge(trp[a].rs,b);
        update(a);
        return a;
    }
    else{
        trp[b].ls = merge(a,trp[b].ls);
        update(b);
        return b;
    }
}
void insert(int val)
{
    int x,y;
    split(root,val,x,y);
    root = merge(merge(x,newnode(val)),y);
}
void del(int val)
{
    int x,y,z;
    split(root,val,x,z);
    split(x,val-1,x,y);
    y = merge(trp[y].ls,trp[y].rs);
    root = merge(merge(x,y),z);
}

int get_rank(int val)
{
    int x,y,z;
    split(root,val-1,x,y);
    int ans = trp[x].siz + 1;
    root = merge(x,y);
    return ans;
}

int get_val(int rank)
{
    int rt = root;
    while(rt){
        if(trp[trp[rt].ls].siz + 1 == rank){
            break;
        }
        else if(trp[trp[rt].ls].siz>=rank){
            rt = trp[rt].ls;
        }
        else{
            rank -= trp[trp[rt].ls].siz + 1;
            rt = trp[rt].rs;
        }
    }
    return trp[rt].val;
}
int pre(int val)
{
    int x,y;
    split(root,val - 1,x,y);
    int rt = x;
    while(trp[rt].rs)rt = trp[rt].rs;
    int ans = trp[rt].val;
    root = merge(x,y);
    return ans;
}
int nxt(int val)
{
    int x,y;
    split(root,val,x,y);
    int rt = y;
    while(trp[rt].ls)rt = trp[rt].ls;
    int ans = trp[rt].val;
    root = merge(x,y);
    return ans;
}
void solve()
{
    int n;
    cin>>n;
    trp[0].ls = trp[0].rs = 0;
    for(int i=1;i<=n;i++){
        int opt,x;
        cin>>opt>>x;
        if(opt == 1){
            insert(x);
        }
        else if(opt == 2){
            del(x);
        }
        else if(opt == 3){
            cout<<get_rank(x)<<"\n";
        }
        else if(opt == 4){
            cout<<get_val(x)<<"\n";
        }
        else if(opt == 5){
            cout<<pre(x)<<"\n";
        }
        else{
            cout<<nxt(x)<<"\n";
        }
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