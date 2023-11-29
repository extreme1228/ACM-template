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
struct DIST{
    int id;
    int d;
    friend bool operator <(const DIST& a,const DIST&b)
    {
        return a.d>b.d;
    }
};
struct EDGE{
    int to;
    int cost;
};
int d[maxn];
int vis[maxn];
vector<EDGE>G[maxn];

void Dijkstra(int s)
{
    priority_queue<DIST>pq;
    memset(d,INF,sizeof(d));//d[]是距离数组，存储某个点到指定源点的当前最短距离
    memset(vis,0,sizeof(vis));//vis[]是标记数组，记录某个节点是否更新过
    d[s]=0;
    pq.push({s,d[s]});//pq为优先队列，小根堆，按照距离大小依次弹出
    while(!pq.empty())
    {
        DIST u=pq.top();
        pq.pop();
        if(vis[u.id])
            continue;
        vis[u.id]=1;
        int id=u.id;
        for(int i=0;i<G[id].size();i++){
            EDGE e=G[id][i];
            if(d[e.to]>d[id]+e.cost)
            {
                d[e.to]=d[id]+e.cost;
                pq.push({e.to,d[e.to]});
            }
        }
    }
}
