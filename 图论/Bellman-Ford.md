```cpp
bool Bellmanford(int n, int s) {
    dis.resize(n + 1, 0x3f3f3f3f);
    dis[s] = 0;
    bool flag = 0;
    for(int i = 1; i <= n; i ++) {
        flag = 0;
        //vector<int>tmpdis = dis;
        for(int j = 1; j <= n; j ++) {
            for(auto it : e[j]) {
                int u = it.first, w = it.second;
                if(dis[u] > dis[j] + w) {
                    dis[u] = dis[j] + w;
                    flag = 1;
                }
                //if(dis[u] > tmpdis[j] + w) {
                //    dis[u] = tmpdis[j] + w;
                //    flag = 1;
                //}
            }
        }
    }
    //返回是否存在负环
    return flag;
}
```