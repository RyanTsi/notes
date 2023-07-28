#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int INF = 1e9 + 7, MAXN = 1e3 + 10, mod = 998244353;
int dp[MAXN][MAXN];

vector<tuple<int, int, int>> res;

int dfs(int x, int y) {
    if(x == y) {
        if(x == 1) {
            return 0;
        }
        return dp[x][y] = 1;
    }
    if(dp[x][y]) return dp[x][y];
    if(x > y) {
        return dp[x][y] = 1 + dfs(x - y, y);
    } else {
        return dp[x][y] = 1 + dfs(x, y - x);
    }
}

void ft1(int x1, int y1, int x2, int y2);

void ft2(int x1, int y1, int x2, int y2);

void ft1(int x1, int y1, int x2, int y2) {
    int len = x2 - x1 + 1;
    if(len <= 7) {
        if(len > 1) {
            res.push_back({x1, y1, len});
        }
        return;
    }
    if(len % 2 == 0) {
        len /= 2;
        ft1(x1, y1, x1 + len - 1, y1 + len - 1);
        ft1(x1 + len, y1 + len, x2, y2);
        ft1(x1 + len, y1, x2, y1 + len - 1);
        ft1(x1, y1 + len, x1 + len - 1, y2);
        len *= 2;
    } else {
        int d = 0, ming = INF;
        for(int i = 1; i <= len / 2; i ++) {
            int x = dfs(i, len - i);
            if(x < ming) {
                ming = x;
                d = i; 
            }
        }
        len = d;
        ft1(x1, y1, x1 + len - 1, y1 + len - 1);
        ft1(x1 + len, y1 + len, x2, y2);
        ft2(x1 + len, y1, x2, y1 + len - 1);
        ft2(x1, y1 + len, x1 + len - 1, y2);
        len = x2 - x1 + 1;
    }

    res.push_back({x1, y1, len});
}

void ft2(int x1, int y1, int x2, int y2) {
    if(x1 == x2 || y1 == y2) {
        return;
    }
    int lenx = x2 - x1 + 1;
    int leny = y2 - y1 + 1;
    if(lenx == leny) {
        ft1(x1, y1, x2, y2);
        return;
    }
    if(lenx > leny) {
        ft1(x1, y1, x1 + leny - 1, y1 + leny - 1);
        ft2(x1 + leny, y1, x2, y2);
    } else {
        ft1(x1, y1, x1 + lenx - 1, y1 + lenx - 1);
        ft2(x1, y1 + lenx, x2, y2);
    }
}


void solve() {
    int n;
    cin >> n;
    ft1(1, 1, n, n);
    cout << res.size() << '\n';
    for(auto [x, y, len] : res) {
        cout << x << " " << y << " " << len << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _ = 1;
    // cin >> _;
    while(_ --) {
        solve();
    }
}