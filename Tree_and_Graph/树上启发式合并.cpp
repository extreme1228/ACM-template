//颜色平衡树，本质上是树上启发式合并
//题目链接：https://www.dotcpp.com/oj/problem3144.html
/*
本题可以作为一道树上启发式合并的例题模板，树上启发式合并主要是用于求解树上问题，且树上每个节点都要求一次答案，并且这个答案
与其子树的信息有关，如果暴力递归枚举是O(n^2)的做法，我们通过引入重子节点的概念，贪心的每次最后遍历重子节点的内容并保留下来
这样就可以使得整个复杂度变为O(nlogn),大部分有关树上启发式合并的问题模板都类似，不同问题背景下，add函数和del函数的编写可能
会有不同。

*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=2e5+10;
vector<int>tree[maxn];
int hson[maxn],siz[maxn],color[maxn],fa[maxn];
int n;
int ans=0;
int cnt[maxn];//cnt[i]表示颜色i出现次数
int num[maxn];//num[i]表示出现次数为i的颜色个数
int m_max=0,m_min=1e9;//分别代表该子树中的出现颜色的最多与最少次数


void pre_dfs(int node,int p)
{
    siz[node]=1;
    int hson_num=0;
    for(auto v:tree[node]){
        if(v==p)continue;
        pre_dfs(v,node);
        siz[node]+=siz[v];
        if(siz[v]>hson_num){
            hson_num=siz[v];
            hson[node]=v;
        }
    }
}
void add(int node)
{
    num[cnt[color[node]]]--;
    if(num[cnt[color[node]]]==0&&m_min==cnt[color[node]]){
        m_min=cnt[color[node]]+1;
    }
    else{
        m_min=min(m_min,cnt[color[node]]+1);
    }
    cnt[color[node]]++;
    num[cnt[color[node]]]++;
    m_max=max(m_max,cnt[color[node]]);
}
void add_subtree(int node,int p)
{
    add(node);
    for(auto v:tree[node]){
        if(v!=p)add_subtree(v,node);
    }
}
void del(int node)
{
    m_max=0,m_min=1e9;
    // num[cnt[color[node]]]=0;
    // cnt[color[node]]=0;
    num[cnt[color[node]]]--;
    cnt[color[node]]--;
    if(cnt[color[node]]>0)num[cnt[color[node]]]++;
}
void del_subtree(int node,int p)
{
    del(node);
    for(auto v:tree[node]){
        if(v!=p)del_subtree(v,node);
    }
}
void dfs(int node,int p,bool keep)
{
    for(auto v:tree[node]){
        if(v!=hson[node]&&v!=p)dfs(v,node,0);
    }
    if(hson[node])dfs(hson[node],node,1);
    add(node);
    for(auto v:tree[node]){
        if(v!=hson[node]&&v!=p){
            add_subtree(v,node);
        }
    }
    if(m_min==m_max)ans++;
    if(!keep){
        del_subtree(node,p);
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>color[i]>>fa[i];
        if(fa[i]==0)continue;
        tree[i].push_back(fa[i]);
        tree[fa[i]].push_back(i);
    }
    //预处理出hson
    pre_dfs(1,-1);
    //树上启发式合并
    dfs(1,-1,0);
    cout<<ans;
}