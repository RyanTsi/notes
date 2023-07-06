```cpp
namespace Dinic {
    using ll = long long;
    const int MAX_V = 500;
    const ll INF = 1e12;
    struct Edge {
        int from, to;
        ll  cup, flow;
        Edge(int u, int v, ll c, ll f) : from(u), to(v), cup(c), flow(f) {}
    };
    struct Graph {

        int s, t, n, m;
        vector<Edge> es;
        vector<int> G[MAX_V];
        int level[MAX_V], iter[MAX_V];
        bool vis[MAX_V];

        Graph(int s, int t, int n = MAX_V) : n(n), s(s), t(t) {
            es.clear();
            for(int i = 0; i < n; i ++) {
                G[i].clear();
            }
        };

        void addEdge(int u, int v, ll c) {
            es.push_back({u, v, c, 0}), es.push_back({v, u, 0, 0});
            m = es.size();
            G[u].push_back(m - 2), G[v].push_back(m - 1);
        }

        ll dfs(int v, ll f) {
            if(v == t || f == 0) return f;
            ll flow = 0, d;
            for(int &i = iter[v]; i < G[v].size(); i ++) {
                auto &e = es[G[v][i]], &reve = es[G[v][i] ^ 1];
                if(level[v] + 1 == level[e.to] && (d = dfs(e.to, min(f, e.cup - e.flow))) > 0) {
                    e.flow += d, reve.flow -= d;
                    flow += d;
                    f -= d;
                    if(! f) break;
                }
            }
            return flow;
        }

        bool bfs() {
            memset(vis, false, sizeof vis);
            queue<int> q;
            q.push(s);
            level[s] = 0;
            vis[s] = true;
            while(q.size()) {
                int v = q.front();
                q.pop();
                for(int i = 0; i < G[v].size(); i ++) {
                    auto &e = es[G[v][i]], &reve = es[G[v][i] ^ 1];
                    if(!vis[e.to] && e.cup > e.flow) {
                        vis[e.to] = true;
                        level[e.to] = level[v] + 1;
                        q.push(e.to);
                    }
                }
            }
            return vis[t];
        }

        ll maxflow() {
            ll flow = 0;
            while(bfs()) {
                memset(iter, 0, sizeof iter);
                flow += dfs(s, INF);
            }
            return flow;
        }

    };
};
using namespace Dinic;
```