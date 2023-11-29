/*
用法：DominatorTree dTree(n)初始化,dTree.add_edge(u,v)加边，dTree.solve(rt)求支配点,dTree.idom[i]表示i的直接支配点
*/

class DominatorTree{
public:
    std::vector <std::vector <int>> e, _e, tmp;
    std::vector <int> dfn, inv;
    int dfncnt;
    std::vector <int> sdom, idom;
    std::vector <int> fa, father, value;

    explicit DominatorTree(int n):dfncnt(0){
        int sz = n + 10;
        e.resize(sz);
        _e.resize(sz);
        tmp.resize(sz);
        dfn.resize(sz);
        inv.resize(sz);
        sdom.resize(sz);
        idom.resize(sz);
        fa.resize(sz);
        father.resize(sz);
        value.resize(sz);
    }

    void add_edge(int u, int v){
        e[u].emplace_back(v);
        _e[v].emplace_back(u);
    }

    int min(int u, int v){
        return dfn[u] < dfn[v] ? u : v;
    }

    int find(int u){
        if (fa[u] == u) return u;
        int f = fa[u];
        fa[u] = find(fa[u]);
        if (dfn[sdom[value[f]]] < dfn[sdom[value[u]]]) value[u] = value[f];
        return fa[u];
    }

    void dfs(int u){
        dfn[u] = ++ dfncnt;
        inv[dfncnt] = u;
        for (auto v : e[u]){
            if (dfn[v]){
                continue;
            }
            father[v] = u;
            dfs(v);
        }
    }

    void solve(int rt){
        dfs(rt);
        for (int i = 1; i <= dfncnt; ++ i){
            fa[inv[i]] = value[inv[i]] = sdom[inv[i]] = inv[i];
        }
        for (int i = dfncnt; i >= 2; -- i){
            int u = inv[i];
            for (auto v : _e[u]){
                if (!dfn[v]) continue;
                if (dfn[v] < i){
                    sdom[u] = min(sdom[u], v);
                }
                else{
                    find(v);
                    sdom[u] = min(sdom[u], sdom[value[v]]);
                }
            }
            fa[u] = father[u];
            tmp[sdom[u]].emplace_back(u);
            int pa = fa[u];
            for (auto v : tmp[pa]){
                find(v);
                idom[v] = value[v];
            }
            tmp[pa].clear();
        }
        for (int i = 2; i <= dfncnt; ++ i){
            int u = inv[i];
            idom[u] = sdom[u] == sdom[idom[u]] ? sdom[u] : idom[idom[u]];
        }
    }
};