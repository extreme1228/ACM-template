/*
LCA即树上最近公共祖先问题(可能还有变式：如问树上两点间最短距离等)，可以通过倍增来求解，
预处理fa[x][i]代表节点x的第2^i个祖先节点，求最近公共祖先时，首先把x,y节点提高到相同高度，之后
从大到小循环找第一个不是他们公共祖先的节点fa_x,fa_y，最终的结果fa=fa[fa_x][0];

*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=40000+10;
vector<int>tree[maxn];
int fa[maxn][32];
int dep[maxn];


//dfs遍历树的同时预处理出fa数组
void dfs(int node,int p)
{
    fa[node][0]=p;
    dep[node]=dep[p]+1;
    for(int i=1;i<=30;i++){
        fa[node][i]=fa[fa[node][i-1]][i-1];
    }
    for(auto v:tree[node]){
        if(v!=p){
            dfs(v,node);
        }
    }
}

//lca求最近公共祖先。
int lca(int x,int y)
{
    int ans=0;
    if(dep[x]<dep[y])swap(x,y);
    int tmp=dep[x]-dep[y];
    for(int i=0;tmp!=0;i++,tmp>>=1){
        if(tmp&1){
            x=fa[x][i];
        }
    }
    if(x==y)return x;
    for(int i=30;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
void solve()
{
    int n,m;
    cin>>n>>m;
    memset(fa,0,sizeof(fa));
    memset(dep,0,sizeof(dep));
    for(int s=1;s<n;s++){
        int i,j;
        cin>>i>>j;
        tree[i].push_back(j);
        tree[j].push_back(i);
    }
    dfs(1,0);
    while(m--){
        int i,j;
        cin>>i>>j;
        cout<<lca(i,j)<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}