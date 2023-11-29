/*
本质上就是利用树链剖分的性质使得我们可以把树上的任意两点间最短距离或者以某个节点为根的全部子树看作一个区间，用线段树
去维护这段区间信息。
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int a[maxn];
int P;
int n,m,root;
vector<int>tree[maxn];
int fa[maxn],siz[maxn],dep[maxn],hson[maxn],dfn[maxn],rnk[maxn],top[maxn];
int w[maxn];
struct SegTree{
    int sum[4*maxn],tag[4*maxn];
    void push_up(int rt)
    {
        //push_up函数的具体实现取决于我们想要维护的区间信息(区间和，最大值最小值)
        sum[rt]=(sum[2*rt]+sum[2*rt+1])%P;//这里注意可能有某些问题数值很大需要再这里取模
    }
    void build(int rt,int l,int r)
    {
        if(l>r)return ;
        if(l==r){
            sum[rt]=w[rnk[l]];//这里的a数组是我们想维护的区间数组
            return;
        }
        int mid=(l+r)/2;
        build(2*rt,l,mid);
        build(2*rt+1,mid+1,r);
        push_up(rt);
    }
    void push_down(int rt,int len_l,int len_r)
    {
        if(tag[rt]){
            sum[2*rt]+=tag[rt]*len_l;
            sum[2*rt]%=P;
            sum[2*rt+1]+=tag[rt]*len_r;
            sum[2*rt+1]%=P;
            tag[2*rt]+=tag[rt];
            tag[2*rt]%=P;
            tag[2*rt+1]+=tag[rt];
            tag[2*rt+1]%=P;
            tag[rt]=0;
        }
    }
    void update(int rt,int L,int R,int l,int r,int k)
    {
        //目标区间[L,R]+=k
        if(L<=l&&r<=R){
            //如果当前rt所代表区间被目标区间完全包括，直接更改rt节点处的值更新tag数组
            sum[rt]+=k*(r-l+1);
            sum[rt]%=P;
            tag[rt]+=k;
            tag[rt]%=P;
            return;
        }
        int mid=(l+r)/2;
        push_down(rt,mid-l+1,r-mid);//先下移tag影响
        if(mid>=L)update(2*rt,L,R,l,mid,k);
        if(mid+1<=R)update(2*rt+1,L,R,mid+1,r,k);
        push_up(rt);
    }
    int query(int rt,int L,int R,int l,int r)
    {
        if(L<=l&&r<=R){
            return sum[rt]%P;
        }
        int mid=(l+r)/2;
        push_down(rt,mid-l+1,r-mid);
        int ans=0;
        if(mid>=L)ans+=query(2*rt,L,R,l,mid);
        ans%=P;
        if(mid+1<=R)ans+=query(2*rt+1,L,R,mid+1,r);
        return ans%P;
    }
}st;


void dfs1(int node,int p,int depth)
{
    fa[node]=p;
    dep[node]=depth;
    siz[node]=1;
    int hson_num=0;
    for(auto v:tree[node]){
        if(v!=p){
            dfs1(v,node,depth+1);
            siz[node]+=siz[v];
            if(siz[v]>hson_num){
                hson_num=siz[v];
                hson[node]=v;
            }
        }
    }
}
int cnt=0;
void dfs2(int node,int p,int anc)
{
    dfn[node]=++cnt;
    top[node]=anc;
    rnk[cnt]=node;
    if(hson[node]){
        dfs2(hson[node],node,anc);
        for(auto v:tree[node]){
            if(v!=hson[node]&&v!=p)dfs2(v,node,v);
        }
    }
}
void modify1(int x,int y,int k)
{
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        st.update(1,dfn[top[x]],dfn[x],1,n,k);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    st.update(1,dfn[y],dfn[x],1,n,k);
}
int query1(int x,int y)
{
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans=(ans+st.query(1,dfn[top[x]],dfn[x],1,n))%P;
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    ans=(ans+st.query(1,dfn[y],dfn[x],1,n))%P;
    return ans;
}
void modify2(int x,int k)
{
    st.update(1,dfn[x],dfn[x]+siz[x]-1,1,n,k);
}
int query2(int x)
{
    return st.query(1,dfn[x],dfn[x]+siz[x]-1,1,n);
}
int main()
{
    cin>>n>>m>>root>>P;
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    dfs1(root,root,0);
    dfs2(root,root,root);
    st.build(1,1,n);
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,y,z;
            cin>>x>>y>>z;
            modify1(x,y,z);
        }
        else if(opt==2){
            int x,y;
            cin>>x>>y;
            cout<<query1(x,y)<<"\n";
        }
        else if(opt==3){
            int x,z;
            cin>>x>>z;
            modify2(x,z);
        }
        else if(opt==4){
            int x;
            cin>>x;
            cout<<query2(x)<<"\n";
        }
    }
}