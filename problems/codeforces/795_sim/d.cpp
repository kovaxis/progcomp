#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct SparseMax {
    vector<vector<T>> st;

    // O(N log N) time
    // O(N log N) memory
    SparseMax(vector<T> a) {
        int N = a.size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        st[0] = a;
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));  // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return max(st[i][l], st[i][r - (1 << i)]);  // query op
    }
};
template <class T>
struct SparseMin {
    vector<vector<T>> st;

    // O(N log N) time
    // O(N log N) memory
    SparseMin(vector<T> a) {
        int N = a.size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        st[0] = a;
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));  // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return min(st[i][l], st[i][r - (1 << i)]);  // query op
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<ll> a(N), b(N + 1);
        vector<int> stk, lt(N), rt(N);
        rep(i, N) cin >> a[i];

        rep(i, N) b[i + 1] = b[i] + a[i];
        SparseMax bmx(b);
        SparseMin bmn(b);

        rep(i, N) {
            while (!stk.empty() && a[stk.back()] < a[i]) {
                rt[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        while (!stk.empty()) {
            rt[stk.back()] = N;
            stk.pop_back();
        }

        invrep(i, N) {
            while (!stk.empty() && a[stk.back()] < a[i]) {
                lt[stk.back()] = i + 1;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        while (!stk.empty()) {
            lt[stk.back()] = 0;
            stk.pop_back();
        }

        bool ok = true;
        rep(i, N) {
            int l = lt[i], r = rt[i];
            ll sm = bmx.query(i + 1, r + 1) - bmn.query(l, i + 1);
            // cerr << "at element " << i + 1 << ", max is " << a[i]
            //     << ", max range is [" << l + 1 << ", " << r << "], max sum is
            //     "
            //     << sm << endl;
            if (a[i] < sm) ok = false;
        }

        cout << (ok ? "YES" : "NO") << "\n";
    }
}
