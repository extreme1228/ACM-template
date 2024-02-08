/*1.Dijstra()//用于计算单源最短路，适合于正权图，无法处理负权图，基于贪心思想和优先队列实现

注意：在本算法中一个节点可能会被多次加入队列，但由于小根堆的性质，他只会进行一次更新
可能会多次更新，但出队列时一定是最短距离
注：Dijstra算法的优先队列要重定义<,
friend bool operator <(const NODE& a,const NODE&b)
    {
        return a.d>b.d;
    }
且这次更新时该节点到原点已经是最短距离（PS：这也时Dijstra算法不能处理负权图的原因，由于负权边的存在
使得贪心思想不再正确）*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9+7;
const int maxn = 1e5+10;
struct dist{
    ll id;
    ll d;
    friend bool operator <(const dist& a,const dist&b)
    {
        return a.d>b.d;
    }
};//pq为优先队列，小根堆，按照距离大小依次弹出
struct edge{
    ll to;
    ll cost;
};
ll dis[maxn];//d[]是距离数组，存储某个点到指定源点的当前最短距离
int vis[maxn];//vis[]是标记数组，记录某个节点是否更新过
vector<edge>g[maxn];

//O(mlogm)
void Dijkstra1(int s,int n)
{
    priority_queue<dist>pq;
    for(int i=0;i<=n;i++){
        dis[i] = INF;
        vis[i] = 0;
    }
    dis[s]=0;
    pq.push({s,dis[s]});
    while(!pq.empty())
    {
        dist u=pq.top();
        pq.pop();
        if(vis[u.id])
            continue;
        vis[u.id]=1;
        for(auto e:g[u.id]){
            if(dis[e.to]>dis[u.id] + e.cost){
                dis[e.to]=dis[u.id]+e.cost;
                pq.push({e.to,dis[e.to]});
            }
        }
    }
    return;
}

//O(n^2)
void Dijstra2(int s,int n)
{
    for(int i=0;i<=n;i++)dis[i] = INF,vis[i] = 0;
    dis[s] = 0;
    for(int i=1;i<=n;i++){
        int u = -1;
        ll minv = INF;
        //这里依据具体情况枚举所有图中节点
        for(int j=0;j<n;j++){
            if(vis[j] == 0&&dis[j]<minv){
                u = j;
                minv = dis[j];
            }
        }
        if(u == -1)return;
        vis[u] = 1;
        for(auto e:g[u]){
            if(dis[e.to]>dis[u] + e.cost){
                dis[e.to] = dis[u] + e.cost;
            }
        }
    }
    return;
}