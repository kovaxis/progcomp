#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

/*
template <class T>
struct St {
    int n;
    vector<T> a;

    T neut() { return 0; }
    T merge(T x, T y) { return x + y; }

    St(int n = 0) : n(n), a(2 * n, neut()) {}

    T query(int l, int r) {
        T x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, T x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};
*/

struct St {
    int n;
    vector<ll> a;

    ll neut() { return 0; }
    ll merge(ll x, ll y) { return x + y; }

    St(int n = 0) : n(n), a(2 * n, neut()) {}

    ll query(int l, int r) {
        ll x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, ll x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;
    St st(N);

    rep(i, N) {
        int x;
        cin >> x;
        st.update(i, x);
    }

    rep(q, Q) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, x;
            cin >> i >> x;
            st.update(i, st.query(i, i + 1) + x);
        } else if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << "\n";
        }
    }
}
