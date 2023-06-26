- 给出递推式, 对于质数$p$, 有
$$
\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p
$$


[例题](https://www.luogu.com.cn/problem/P3807)

因此当组合数过大的时候可以利用卢卡斯定理递归求解,时间复杂度为$O(f(p) + g(n)log\ n)$

```cpp
ll fact[mod], inv[mod];
ll qpow(ll x, ll y) {
    ll res = 1;
    while(y) {
        if(y & 1) {
            (res *= x) %= mod;
        }
        (x *= x) %= mod;
        y >>= 1;
    }
    return res;
}
void init() {
    fact[0] = inv[0] = 1;
    for(int i = 1; i < MAXN; i ++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv[MAXN - 1] = qpow(fact[MAXN - 1], mod - 2); 
    for(int i = mod - 2; i > 0; i --) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}
ll C(ll n, ll m) {
    if(m > n) return 0;
    return fact[n] * inv[m] * inv[n - m] % mod;
}
ll lucas(ll n, ll m) {
    if(m == 0) return 1;
    return C(n % mod, m % mod) * lucas(n / mod, m / mod);
}
```