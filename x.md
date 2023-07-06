##### Dinic

```cpp
namespace Dinic {
    using ll = long long;
    const int MAX_V = 500;
    const ll INF = 1e12;
    struct Edge {
        int from, to;
        ll  cup, flow;
        Edge(int u, int v, int c, int f) : from(u), to(v), cup(c), flow(f) {}
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
        void addEdge(int u, int v, int c) {
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
                    flow += d, f -= d;
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
```

##### tarjan

```cpp
const int MAXN = 1e4 + 10;
int n, m;
struct Edge {
    int v;
    bool is_bri; //是否为桥（割边：删去这条边后导致整张图的联通分量增大）
};
vector<Edge> e[MAXN];
// tarjan 需要定义的
int dfn[MAXN], low[MAXN];
bool vis[MAXN];
int tim = 0;
stack<int> stk;
// 缩点需要定义的
int tag;                                        // 强连通分量个数
vector<int> tar[MAXN];                          // 每个强连通分量的点集
int scc[MAXN];                                  // 每个点属于哪个强连通分量
int deg[MAXN];                                  // 缩点后新图每个点的出度
vector<int> che[MAXN];                          // 缩点后的图
void init() {
    for(int i = 0; i < tag; i ++) {
        tar[i].clear();
    }
    for(int i = 0; i < n; i ++) {
        che[i].clear();
        e[i].clear();
        dfn[i] = 0, low[i] = 0, scc[i] = 0, vis[i] = 0;
    }
    tim = 0;
    tag = 0;
}
void tarjan(int u, int f) {
    dfn[u] = low[u] = ++ tim;
    vis[u] = 1;
    stk.push(u);
    for(auto &[v, yes] : e[u]) {
        if(!dfn[v]) {                           // 父子边
            tarjan(v, u);
            low[u] = min(low[u], low[v]);       // 更新low
            if(dfn[u] < low[v]) {               // v不能通过u到达更早的祖宗
                yes = 1;
            }
        } else if(vis[v]) {
			low[u] = min(low[u], low[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int now;
        do {
            now = stk.top();
            stk.pop();
            vis[now] = 0;
            tar[tag].push_back(now);
            scc[now] = tag;
        } while(now != u);
        tag ++;
    }
}
void tarjan_all() {
    for(int i = 0; i < n; i ++) {
        if(!dfn[i]) tarjan(i, i);
    }
}
// 缩点
void regra() {
    for(int i = 0; i < n; i ++) {
        int u = i;
        for(auto [v, yes] : e[i]) {
            int x = scc[u], y = scc[v];
            if(x != y) {
                che[x].push_back(y);
                deg[y] ++;
            }
        }
    }
}
```

##### 分块-由乃打扑克 and 快读

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9 + 7, MAXN = 1e5 + 9, mod = 998244353;
void read() {}
template<typename T,typename... Ts>
inline void read(T &arg,Ts&... args) {
    T x = 0, f = 1;
    char c = getchar();
    while(!isdigit(c)){if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)){x = (x << 3) +(x << 1) + (c - '0');c = getchar();}
    arg = x * f;
    read(args...);
}
int n, m, BS;
ll a[MAXN];
int _1[MAXN], _2[MAXN], t1, t2;
struct BLOCK {
    int l, r;
    ll ex;
    vector<ll> B;
    vector<int> mp;
    BLOCK(int s) {
        B.resize(s);
        ex = 0;
    }
    BLOCK(int _l, int _r) {
        ex = 0;
        l = _l, r = _r;
        int s = r - l + 1;
        B.resize(s);
        mp.resize(s);
        for(int i = l; i <= r; ++ i) {
            mp[i - l] = i;
        }
        sort(mp.begin(), mp.end(), [&] (int x, int y)  {
            return a[x] < a[y];
        });
        for(int i = 0; i < s; i ++) {
            B[i] = a[mp[i]];
        }
    }
    void rebuild(int s, int t, int k) {
        t1 = t2 = 0;
        for(int i = 0; i < mp.size(); ++ i) {
            int x = mp[i];
            if(x >= s && x <= t) _1[t1 ++] = x;
            else _2[t2 ++] = x;
        }
        for(int i = 0; i < t1; ++ i) a[_1[i]] += k;
        int  i = 0, j = 0, c = 0;
        while(i < t1 && j < t2) {
            if(a[_1[i]] < a[_2[j]]) mp[c ++] = _1[i ++];
            else mp[c ++] = _2[j ++];
        }
        while(i < t1) mp[c ++] = _1[i ++];
        while(j < t2) mp[c ++] = _2[j ++];
        for(int i = 0; i < mp.size(); i ++) B[i] = a[mp[i]];
    }
};
vector<BLOCK> block;
inline void add(int l, int r, int k) {
    int lb = l / BS, rb = r / BS;
    if(lb == rb) {
        block[lb].rebuild(l, r, k);
    } else {
        block[lb].rebuild(l, block[lb].r, k);
        block[rb].rebuild(block[rb].l, r, k);
        for(int i = lb + 1; i < rb; i ++) {
            block[i].ex += k;
        }
    }
}
inline ll query(int l, int r, int k) {
    int lb = l / BS, rb = r / BS;
    if(lb == rb) {
        int c = 0;
        for(int i : block[lb].mp) {
            if(i >= l && i <= r) c ++;
            if(c == k) return a[i] + block[lb].ex;
        }
    } else {
        BLOCK _ex(block[lb].r - l + 1 + r - block[rb].l + 1);
        t1 = t2 = 0;
        for(int i : block[lb].mp) {
            if(i >= l) _1[t1 ++] = a[i] + block[lb].ex;
        }
        for(int i : block[rb].mp) {
            if(i <= r) _2[t2 ++] = a[i] + block[rb].ex;
        }
        int c = 0, i = 0, j = 0;
        while(i < t1 && j < t2) {
            if(_1[i] < _2[j]) _ex.B[c ++] = _1[i ++];
            else _ex.B[c ++] = _2[j ++];
        }
        while(i < t1) _ex.B[c ++] = _1[i ++];
        while(j < t2) _ex.B[c ++] = _2[j ++];
        ll L = 1e18, R = -1e18;
        L = min(L, _ex.B[0]);
        R = max(R, _ex.B.back());
        for(int i = lb + 1; i < rb; ++ i) {
            L = min(L, block[i].B[0] + block[i].ex);
            R = max(R, block[i].B.back() + block[i].ex);
        }
        L --, R ++;
        while(R > L + 1) {
            ll M = L + R  >> 1;
            int cnt = 0;
            cnt += lower_bound(_ex.B.begin(), _ex.B.end(), M) - _ex.B.begin();
            for(int i = lb + 1; i < rb; i ++) {
                cnt += lower_bound(block[i].B.begin(), block[i].B.end(), M - block[i].ex) - block[i].B.begin();
            }
            if(cnt >= k) R = M;
            else L = M;
        }
        return R - 1;
    }
}
int main() {
    read(n, m);
    for(int i = 0; i < n; ++ i) {
        read(a[i]);
    }
    BS = 912;
    for(int i = 0; 1ll * i * BS < n; ++ i) {
        int l = i * BS, r = min(n - 1, (i + 1) * BS - 1);
        block.push_back(BLOCK(l, r));
    }
    while(m --) {
        int op, l, r, k;
        read(op, l, r, k);
        l --, r --;
        if(op == 1) {
            if(r - l + 1 < k) cout << "-1\n";
            else cout << query(l, r, k);
        } else {
            add(l, r, k);
        }
    }
}
```

##### 线段树

```cpp
const int M = 5e5 + 10;
int n, m, a[M], f[4 * M];
void build(int k, int l, int r) {
    if(l == r) {
        f[k] = a[l];
        return;
    }
    int m = l + r >> 1;
    build(k << 1, l, m), build(k << 1 | 1, m + 1, r);
    f[k] = f[k << 1] + f[k << 1 | 1];
}
void add(int k, int l, int r, int x, int y) {
    f[k] += y;
    if(l == r) return;
    int m = l + r >> 1;
    if(x <= m) {
        add(k << 1, l, m, x, y);
    } else {
        add(k << 1 | 1, m + 1, r, x, y);
    }
}
int ask(int k, int l, int r, int s, int t) {
    if(l == s && r == t) return f[k];
    int m = l + r >> 1;
    if (m >= t) {
        return ask(k << 1, l, m, s, t);
    } else if(m < s) {
        return ask(k << 1 | 1, m + 1, r, s, t);
    } else {
        return ask(k << 1, l, m, s, m) + ask(k << 1 | 1, m + 1, r, m + 1, t);
    }
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef pair<int, int> PII;
const int INF = 2147483647, mod = 998244353, MAXN = 1e5 + 10;
// [l, r)
template<typename T, typename F, typename L, typename Map, typename Com>
struct Lazy_Segtre {
    int n;
    const F f;                  // 二元运算
    const T e  = T();           // 单位元
    const L e1 = L();           // 懒标记单位元
    const Map mapping;          // 解懒标记
    const Com composition;      // 添加(合并)懒标记
    vector<T> tree;
    vector<L> lazy;
    Lazy_Segtre(int n, F f, Map mapping, Com c) : n(n), tree(4 << __lg(n)), lazy(4 << __lg(n)), f(f), mapping(mapping), composition(c) {}
    Lazy_Segtre(vector<T> a, F f, Map m, Com c) : Lazy_Segtre(a.size(), f, m, c) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if(r - l == 1) {
                tree[p] = a[l];
                return;
            }
            int m = l + r >> 1;
            build(p << 1, l, m), build(p << 1 | 1, m, r);
            push_up(p);
        };
        build(1, 0, n);
    };
    void push_up(int p) {
        tree[p] = f(tree[p << 1], tree[p << 1 | 1]);
    }
    void push_down(int p, int l, int r) {
        tree[p] = mapping(tree[p], lazy[p], l, r);
        if(r - l > 1) {
            int m = l + r >> 1;
            lazy[p << 1] = composition(lazy[p << 1], lazy[p]);
            lazy[p << 1 | 1] = composition(lazy[p << 1 | 1], lazy[p]);
        }
        lazy[p] = e1;
    }
    void modify(int p, int l, int r, int s, int t, const L v) {
        push_down(p, l, r);
        if(l >= t || r <= s) {
            return;
        } 
        if(l >= s && r <= t) {
            lazy[p] = v;
            push_down(p, l, r);
            return;
        }
        int m = l + r >> 1;
        modify(p << 1, l, m, s, t, v);
        modify(p << 1 | 1, m, r, s, t, v);
        push_up(p);
    }
    T query(int p, int l, int r, int s, int t) {
        push_down(p, l, r);
        if(l >= t || r <= s) {
            return e;
        }
        if(l >= s && r <= t) {
            return tree[p];
        }
        int m = l + r >> 1;
        T res = f(query(p << 1, l, m, s, t), query(p << 1 | 1, m, r, s, t));
        return res;
    }
};
struct node {
    i64 v;
    node() : v(0) {}
    node(i64 v) : v(v) {}
    node& operator+= (const node& p) {
        v += p.v;
        return *this;
    }
};
struct Lazy : node {
    Lazy() : node() {}
    Lazy(int v) : node(v) {}
};
auto f = [&](node a, node b) {
    return node(a.v + b.v);
};
auto Map = [&](node a, Lazy b, int l, int r) {
    return node((r - l) * b.v + a.v);
};
auto Com = [&](Lazy a, Lazy b) {
    return Lazy(a.v + b.v);
};
void solve() {
    int n, q;
    cin >> n >> q;
    Lazy_Segtre<node, decltype(f), Lazy, decltype(Map), decltype(Com)> st(n, f, Map, Com);
    while(q --) {
        int op, x, y, z;
        cin >> op >> x >> y;
        x --, y --;
        if(op == 0) {
            cin >> z;
            st.modify(1, 0, n, x, y + 1, Lazy(z));
        } else {
            cout << st.query(1, 0, n, x, y + 1).v << '\n';
        }
    }
}
```

##### 树剖

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int INF = 1e9 + 7, MAXN = 1e5 + 10, mod = 998244353;
int N = 1e5 + 7;
int n, m, p, r;
vector<int> tre[MAXN];
int fa[MAXN], siz[MAXN], hson[MAXN], dfn[MAXN], dep[MAXN], top[MAXN], rnk[MAXN], tim;
ll d[MAXN << 2], v[MAXN << 2], a[MAXN];
// seg tre
void add(int k, int l, int r, int s, int t, int z) {
    if(l == s && r == t) {
        v[k] += z;
        return;
    }
    d[k] += (t - s + 1) * z;
    int m = l + r >> 1;
    if(m >= t) {
        add(k << 1, l, m, s, t, z);
    } else if(m < s) {
        add(k << 1 | 1, m + 1, r, s, t, z);
    } else {
        add(k << 1, l, m, s, m, z);
        add(k << 1 | 1, m + 1, r, m + 1, t, z); 
    }
}
ll ask(int k, int l, int r, int s, int t, ll z) {
    z += v[k];
    if(l == s && r == t) {
        return (t - s + 1) * z + d[k] ;
    }
    int m = l + r >> 1;
    if(m >= t) {
        return ask(k << 1, l, m, s, t, z) ;
    } else if(s > m) {
        return ask(k << 1 | 1, m + 1, r, s, t, z) ;
    } else {
        return ask(k << 1, l, m, s, m, z) +
               ask(k << 1 | 1, m + 1, r, m + 1, t, z) ;
    }
}
// 树链剖分
void dfs1(int r, int f) {
    siz[r] = 1;
    fa[r] = f;
    dep[r] = dep[f] + 1;
    hson[r] = -1;
    int maxsiz = -1;
    for(auto v : tre[r]) if(f != v) {
        dfs1(v, r);
        siz[r] += siz[v];
        if(siz[v] > maxsiz) {
            hson[r] = v;
            maxsiz = siz[v];
        }
    }
}
void dfs2(int r, int topf) {
    dfn[r] = ++ tim;
    rnk[tim] = r;
    add(1, 1, N, tim, tim, a[r]);
    top[r] = topf;
    if(hson[r] == -1) return ;
    dfs2(hson[r], topf);
    for(auto v : tre[r]) if(v != fa[r] && v != hson[r]) {
        dfs2(v, v);
    }
}
// 树上两点最短路径上的点加z
void op1(int x, int y, ll z) {
    if(top[x] == top[y]) {
        if(dep[x] > dep[y]) swap(x, y);
        add(1, 1, N, dfn[x], dfn[y], z);
    } else {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        add(1, 1, N, dfn[top[x]], dfn[x], z);
        op1(fa[top[x]], y, z);
    }
}
// 树上两点最短路径上的和
ll op2(int x, int y) {
    ll res = 0;
    if(top[x] == top[y]) {
        if(dep[x] > dep[y]) swap(x, y);
        (res += ask(1, 1, N, dfn[x], dfn[y], 0)) ;
    } else {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += ask(1, 1, N, dfn[top[x]], dfn[x], 0) +
               op2(fa[top[x]], y) ;
    }
    return res;
}
// 树上一点x的子树加z
void op3(int x, int z) {
    add(1, 1, N, dfn[x], dfn[x] + siz[x] - 1, z);
}
// 树上一点子树的和
ll op4(int x) {
    return ask(1, 1, N, dfn[x], dfn[x] + siz[x] - 1, 0);
}
```
