```cpp
typedef pair<int, int> PII;
vector<vector<PII>> adj;
vector<int> dis;
//vector<int> path;
int n, m;
void Dij(int n, int s) {
    dis.resize(n + 1,0x3f3f3f3f);
    //path.resize(n + 1, 0);
    //int pre = 0;
    dis[s] = 0;
    vector<bool> vis(n + 1);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, s});
    while(!q.empty()) {
        PII u = q.top();
        q.pop();
        int tmpdis = u.first, tmpu = u.second;
        if(vis[tmpu]) continue;
        vis[tmpu] = 1;
        for(auto it : adj[tmpu]) {
            int v = it.first, w = it.second;
            if(dis[v] > dis[tmpu] + w) {
                dis[v] = dis[tmpu] + w;
                q.push({dis[v], v});
                //path[v] = pre;
            }
        }
    }
}
```