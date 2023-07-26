#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int INF = 1e9 + 7, MAXN = 2e5 + 10, mod = 998244353;
int n, m, k, cnt;
vector<int> gra[MAXN], tre[MAXN << 1];
int dfn[MAXN], low[MAXN], tim;
stack<int> stk;
void init() {
    for(int i = 0; i < n * 2; i ++) {
        tre[i].clear();
    }
    for(int i = 0; i < n; i ++) {
        dfn[i] = low[i] = -1;
    }
    tim = 0;
    cnt = n;
    while (!stk.empty()) {
        stk.pop();
    }
}
int Tarjan(int u, const vector<int>& del) {
    int res = (del[u] == 2);
    dfn[u] = low[u] = ++ tim;
    stk.push(u);
    for(int v : gra[u]) {
        if(dfn[v] == -1 && del[v] != 1) {
            res += Tarjan(v, del);
            low[u] = min(low[u], low[v]);
            if(low[v] == dfn[u]) {
                for(int x = 0; x != v; stk.pop()) {
                    x = stk.top();
                    tre[cnt].push_back(x);
                    tre[x].push_back(cnt);
                }
                tre[u].push_back(cnt);
                tre[cnt].push_back(u);
                cnt ++;
            }
        } else if(del[v] != 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    return res;
}
PII dfs(int u, int f, const vector<int>& del) {
    int res = - 1, count = ((u < n) && (del[u] == 2));
    for(int v : tre[u]) if(v != f) {
        auto x = dfs(v, u, del);
        count += x.second;
        if(x.first != -1) {
            res = x.first;
        } else if(res == -1 && count >= 2) {
            res = u;
        }
    }
    return {res, count};
}
PII dfs2(int u, int f, const vector<int>& del) {
    int res = 0, count = ((u < n) && (del[u] == 2));
    for(int v : tre[u]) if(v != f) {
        auto x = dfs(v, u, del);
        count += x.second;
        res |= (x.second >= 2);
    }
    return {res, count};
}
void solve() {
    cin >> n >> m >> k;
    for(int i = 0; i < m; i ++) {
        int a, b;
        cin >> a >> b;
        a --, b --;
        gra[a].push_back(b);
        gra[b].push_back(a);
    }
    vector<int> h(k);
    for(int i = 0; i < k; i ++) {
        cin >> h[i];
        h[i] --;
    }
    int l = -1, r = k + 1;
    vector<int> del(n);
    auto check = [&](int m) -> bool {
        init();
        for(int i = 0; i < n; i ++) {
            del[i] = 0;
        }
        for(int i = 0; i < k; i ++) {
            if(i < m) {
                del[h[i]] = 1;
            } else {
                del[h[i]] = 2;
            }
        }
        int counter = 0;
        bool ok = true;
        for(int i = 0; i < n; i ++) if(dfn[i] == -1 && del[i] != 1) {
            int w = Tarjan(i, del);
            stk.pop();
            counter += (w >= 2);
            if(w > 2) {
                int X = dfs(i, i, del).first;
                if(X >= n) {
                    ok = false;
                } else {
                    ok = !dfs2(X, X, del).first;
                }
            }
            if(counter >= 2) {
                ok = false;
            }
            if(! ok) {
                break;
            }
        }
        return ok;
    };
    while(r - l > 1) {
        int m = l + r >> 1;
        if(check(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << '\n';
    for(int i = 0; i < n; i ++) {
        gra[i].clear();
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while(_ --) {
        solve();
    }
}