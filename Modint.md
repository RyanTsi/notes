```cpp
struct Mint {
    const int mod = 998244353;
    ll v;
    Mint() {}
    Mint(int v) : v(v) {}
    friend ostream& operator<<(ostream& os, const Mint& v) {
        return os << v.v;
    }
    friend istream& operator>>(istream& is, Mint& v) {
        return is >> v.v;
    }
    Mint& operator+=(const Mint& a) {
        (v += a.v) %= mod;
        return *this;
    }
    Mint& operator-=(const Mint& a) {
        (v += mod - a.v) % mod;
        return *this;
    }
    Mint& operator*=(const Mint& a) {
        v = (v * a.v) % mod;
        return *this;
    }
    Mint operator+(const Mint& p) const {
        return Mint(*this) += p;
    }
    Mint operator-(const Mint& p) const {
        return Mint(*this) -= p;
    }
    Mint operator*(const Mint& k) const {
        return Mint(*this) *= k;
    }
};
```

