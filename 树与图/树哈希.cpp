#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
vector<int>tree[maxn];
struct TreeHash{
    typedef unsigned long long ull;
    const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();
    ull hs[maxn];
    ull shift(ull x){
        x ^= mask;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        x ^= mask;
        return x;
    }
    void dfs(int u,int f)
    {
        hs[u] = 1;
        for(auto v:tree[u]){
            if(v == f)continue;
            dfs(v,u);
            hs[u]+=shift(hs[v]);
        }
    }
    ull get_hash(int x)
    {
        return hs[x];
    }
    void clear(int n)
    {
        for(int i=0;i<=n;i++)hs[i] = 0;
    }
}th;
void solve()
{
    
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