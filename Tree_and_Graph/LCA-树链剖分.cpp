/*
利用树链剖分来解决LCA问题，我们再对整棵树做出剖分后，寻找两个节点的最近公共祖先只需要不断的进行跳链操作，
由于重链剖分的性质可以决定我们最多进行logn次跳边
*/


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=5e5+10;
vector<int>tree[maxn];
int fa[maxn],top[maxn],siz[maxn],hson[maxn],dep[maxn];
//top[x]表示x节点所在重链的第一个节点，hson[x]表示x节点的重子节点，为0表示没有重子节点


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
            if(siz[node]>hson_num){
                hson_num=siz[node];
                hson[node]=v;
            }
        }
    }
    return ;
}
void dfs2(int node,int p,int fa)
{
    top[node]=fa;//top[node]表示node节点所在重链上的第一个祖先节点
    if(hson[node]){
        //如果有重子节点
        //优先遍历重子节点
        dfs2(hson[node],node,fa);
        for(auto v:tree[node]){
            if(v!=p&&v!=hson[node]){
                dfs2(v,node,v);
            }
        }
    }
    return;
}

int lca(int x,int y)
{
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]){
            x=fa[top[x]];
        }
        else y=fa[top[y]];
    }
    return dep[x]>=dep[y]?y:x;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,root;
    cin>>n>>m>>root;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    dfs1(root,root,0);
    dfs2(root,-1,root);
    while(m--){
        int a,b;
        cin>>a>>b;
        cout<<lca(a,b)<<"\n";
    }
}