```cpp
void floyd() {
    dis.resize(n + 1, vector<int>(n + 1), 0x3f3f3f3f);
    for(int i = 0; i < m; i ++) {
        int v, u, w;
        cin >> v >> u >> w;
        dis[v][u] = min(dis[v][u], w);
    }
    for(int i = 0; i <= n; i ++) {
        dis[i][i] = 0;
    }
     for(int k = 1; k <= n; k ++) {
        for(int i = 1;i <= n; i ++) {
            for(in j = 1; j <= n; j ++) {
                dis[i][j] = min(dis[i][j], dis[k][j] + dis[i][k]);
            }
        }
    }   
}
```