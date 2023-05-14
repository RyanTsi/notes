#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef pair<int, int> PII;
const int INF = 2147483647, mod = 998244353, MAXN = 1e5 + 10;

// [l, r)
template<typename T, typename F, typename L, typename Map, typename Com>
struct SegmentTree {
    int n;
    const F f;                  // 二元运算
    const T e  = T();           // 单位元
    const L e1 = L();           // 懒标记单位元
    const Map mapping;          // 解懒标记
    const Com composition;      // 添加(合并)懒标记
    vector<T> tree;
    vector<L> lazy;
    SegmentTree(int n, F f, Map mapping, Com c) : n(n), tree(4 << __lg(n)), lazy(4 << __lg(n)), f(f), mapping(mapping), composition(c) {}
    SegmentTree(vector<T> a, F f, Map m, Com c) : SegmentTree(a.size(), f, m, c) {
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
            return 0;
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
    node() : v(2147483647) {}
    node(i64 v) : v(v) {}
    node& operator+= (const node& p) {
        v += p.v;
        return *this;
    }
};
struct Lazy : node {
    bool used;
    Lazy() : node(), used(false) {}
    Lazy(int v) : node(v), used(true) {}
};
auto f = [](node a, node b) {
    return node(a.v + b.v);
};
auto Map = [](node a, Lazy b, int l, int r) -> node {
    return node((b.used ? b.v : a.v) * (r - l));
};
auto Com = [](Lazy a, Lazy b) {
    return (b.used ? b : a) ;
};

void solve() {
    int n, q;
    cin >> n >> q;
    SegmentTree<node, decltype(f), Lazy, decltype(Map), decltype(Com)> st(vector<node> (n, 2147483647), f, Map, Com);
    while(q --) {
        int op, x, y, z;
        cin >> op >> x;
        if(op == 0) {
            cin >> y >> z;
            st.modify(1, 0, n, x, y + 1, Lazy(z));
        } else {
            cout << st.query(1, 0, n, x, x + 1).v << '\n';
        }
    }
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
}

