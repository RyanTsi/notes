
查询区间$[l,r]$看作$max([l,l + 2 ^ p],[r - 2 ^ p,r])$其中$p = {log_{2}{\lfloor r - l + 1\rfloor}}$就可以满足整个区间为$[l,r]$。

```cpp
struct ST {
    vector<vector<int>> st;
    ST(vector<int> a) {
        int n = a.size();
        st.resize(n, vector<int>(log2(n) + 1));
        for(int i = 0; i < n; i ++) {
            st[i][0] = a[i];
        }
        for(int j = 1; j <= log2(n); j ++) {
            for(int i = 0; i + (1 << j) - 1 < n; i ++) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
};
```