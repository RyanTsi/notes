#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef pair<int, int> PII;
const int INF = 2147483647, mod = 998244353, MAXN = 1e5 + 10;

template<typename T, typename F>
struct SegmentTree {
    int n;
    const F f; // 二元运算
    const T e = T(); // 单位元
    vector<T> tree;
    SegmentTree(int n, F f) : n(n), tree(4 << __lg(n)), f(f) {}
    SegmentTree(vector<T> a, F f) : SegmentTree(a.size(), f) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if(r - l == 1) {
                tree[p] = a[l];
                return;
            }
            int m = l + r >> 1;
            build(p << 1, l, m), build(p << 1 | 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    };
    void pull(int p) {
        tree[p] = f(tree[p << 1], tree[p << 1 | 1]);
    }
    void modify(int p, int l, int r, int x, const T& v) {
        if(r - l == 1) {
            tree[p] = v;
            return;
        }
        int m = l + r >> 1;
        if(x < m) modify(p << 1, l, m, x, v);
        else modify(p << 1 | 1, m, r, x, v);
        pull(p);
    }
    // [l, r)
    T query(int p, int l, int r, int s, int t) {
        if(l >= t || r <= s) {
            return T();
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
    int v;
    node() : v(2147483647) {}
    node(int v) : v(v) {}
    bool operator<(const node& p) const{
        return v < p.v;
    }
};
auto f = [](node a, node b) {
    return min(a, b); 
};

void solve() {
    int n, q;
    cin >> n >> q;
    SegmentTree<node, decltype(f)> st(n + 1, f);
    while(q --) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 0) {
            st.modify(1, 0, n, x, node(y));
        } else {
            cout << st.query(1, 0, n, x, y + 1).v << '\n';
        }
    }
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
}

