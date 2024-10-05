#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const ll Z = 235813;
const ll MOD = 1e9 + 7;

ll binexp(ll a, ll e, ll M = MOD) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

struct Node {
    ll mn1, mn2, mx, hs;

    Node() : mn1(1e9), mn2(1e9), mx(0), hs(0) {}
    Node(ll x) : mn1(x), mn2(1e9), mx(x), hs(binexp(Z, x)) {}
    Node(ll mn1, ll mn2, ll mx, ll hs) : mn1(mn1), mn2(mn2), mx(mx), hs(hs) {}
};

template <class T>
struct St3 {
    vector<T> a;

    T neutral() { return T(); }
    T merge(T l, T r) { return T(min(l.mn1, r.mn1), max(min(l.mn1, r.mn2), min(l.mn2, r.mn1)), max(l.mx, r.mx), (l.hs + r.hs) % MOD); }

    St3() {}
    St3(int N) : a(4 * N, neutral()) {} // node neutral

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v]; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return neutral();                                 // item neutral
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (vr - vl == 1) a[v] = val; // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]); // node merge
        }
    }
};

int N, Q;
St3<Node> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    a = {N};
    rep(i, N) {
        ll x;
        cin >> x;
        a.update(i, x);
    }

    rep(q, Q) {
        int t;
        cin >> t;
        if (t == 1) {
            // update
            ll i, x;
            cin >> i >> x;
            i--;
            a.update(i, x);
        } else if (t == 2) {
            // question
            int l, r;
            cin >> l >> r;
            l--;
            Node x = a.query(l, r);
            if (r - l <= 2 || x.mn1 == x.mx) {
                cout << "YES\n";
                continue;
            }
            cerr << "mn1 " << x.mn1 << " mn2 " << x.mn2 << " mx " << x.mx << " hs " << x.hs << endl;

            // b = mn
            // sum_{x=1}^{r-l} Z^(b + a*x)
            // Z^b * sum_{x=1}^{r-l} (Z^a)^x
            // c * sum_{x=0}^{n-1} r^x
            // r^0 + r^1 + r^2 + r^3 + ... + r^(n-1)
            // r*S - S = r^n - 1
            // S = (r^n - 1) / (r - 1)
            //
            // sum_{x=0}^{r-l-1} Z^(b + a*x)
            // Z^b * sum_{x=0}^{r-l-1} (Z^a)^x
            // Z^b * ((Z^a)^(r-l) - 1) / (Z^a - 1)
            cerr << "b = " << x.mn1 << ", a = " << x.mn2 - x.mn1 << endl;
            ll k = binexp(Z, x.mn2 - x.mn1);
            ll s = binexp(Z, x.mn1) * ((binexp(k, r - l) + MOD - 1) % MOD) % MOD * multinv((k + MOD - 1) % MOD) % MOD;

            cerr << "got " << x.hs << " expected " << s << endl;

            cout << (x.hs == s ? "YES" : "NO") << "\n";
        }
    }
}
