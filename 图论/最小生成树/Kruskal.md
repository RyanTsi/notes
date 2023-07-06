```cpp
struct Edge {
    int v, u, w;
    bool operator< (const edge &a) const {
        return w < a.w;
    }
}
vector<Edge> e(m);
vector<int> pr (n + 1);
int root(int x) {
    return pr[x] == x ? x : pr[x] = root(pr[x]);
} 
int Kruskal() {    
    for(int i = 0; i <= n; i ++) {
        pr[i] = i;
    }
    int res = 0, cnt = 0;
    sort(e.begin(), e.end());
    for(auto it : e) {
        int x = root(it.v), y = root(it.u);
        if(x != y) {
            res += it.w;
            cnt ++;
            p[y] = x;
        }
    }
    if(cnt == n - 1) return res;
    return -1;//表示不存在最小生成树
}
```

- Kruskal 重构树

过程: 按照Kruskal最小生成树的加边顺序,对于边e[a, b],边权为c,令$x=fa[a],y=fa[b]$.若$x \neq y$,则新建一个点$z$,使得$fa[x]=z,fa[y]=z,val[z]=c$.
  
性质:

1. 叶子节点均为原先的点，非叶节点为原先的边
2. 重构树是一个总结点数为$2n-1$的二叉树，但不是满二叉树，最坏情况仍有长度为 $n$ 的链
3. 重构树是一个大根堆-最小生成树(小根堆-最大生成树)
4. 在最小生成树中, 原图中任意两点的最短路径中的最大边为重构树中这两点的lca. 最大生成树相反.

该重构树记录了整个 Kruskal 的过程，可以求子图（子树）相关的一些问题，利用倍增也能够在 $log$ 复杂度内进行 dp 转移的计算。

例题：2021 ICPC 上海 [TLife is a Gam](https://codeforces.com/gym/103446/problem/H)

```cpp
const int MAXN = 1e5 + 10;
struct EDGE {
    int u, v, w;
    bool operator< (const EDGE &a) const {
        return w < a.w;
    };
};
struct DSU {
    int N;
    vector<int> p;
    DSU(int n) {
        N = n;
        p.resize(n);
        for(int i = 0; i < n; i ++) {
            p[i] = i;
        }
    }
    int root(int x) {
        return p[x] == x ? x : p[x] = root(p[x]);
    }
    bool merge(int x, int y) {
        int X = root(x), Y = root(y);
        if(X == Y) return 1;
        p[X] = Y;
        return 0;
    }
};
struct NODE {
    int f = -1, w = 0;
    ll add = 0;
};
NODE node[MAXN << 1];
vector<EDGE> e;
ll bz[MAXN << 1][17];
int fa[MAXN << 1][17];
int n, m, q;
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    e.resize(m);
    vector<int> a(n);
    for(int i = 0; i < n; i ++) {
        cin >> a[i];
        node[i].add = a[i];
    }
    for(auto &[u, v, w] : e) {
        cin >> u >> v >> w;
        u --, v --;
    }
    sort(e.begin(), e.end());
    DSU dsu(2 * n + 10);
    for(auto &[u, v, w] : e) {
        int U = dsu.root(u), V = dsu.root(v);
        if(U != V) {
            dsu.merge(U, n), dsu.merge(V, n);
            node[U].f = node[V].f = n;
            node[n].add = node[U].add + node[V].add;
            node[n].w = w;
            n ++;
        }
    }
    for(int i = 0; i < n; i ++) {
        fa[i][0] = node[i].f;
        bz[i][0] = node[node[i].f].w - node[i].add;
    }
    for(int i = 1; i < 17; i ++) {
        for(int j = 0; j < n; j ++) {
            if(fa[j][i - 1] == - 1) {
                fa[j][i] = -1;
                continue;
            }
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            bz[j][i] = max(bz[j][i - 1], bz[fa[j][i - 1]][i - 1]);
        }
    }
    while(q --) {
        int x, k;
        cin >> x >> k;
        x --;
        for(int i = 16; i >= 0; i --) {
            if(fa[x][i] != -1) {
                if(bz[x][i] <= k) {
                    x = fa[x][i];
                }
            }
        }
        ll res = k + node[x].add;
        cout << res << '\n';
    }
}
```