#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

int N, Q;
vector<int> a, acc;
vector<ll> sm;

// mapping from acc[i] -> i
// goes into inv[0] if i%2 == 0
// goes into inv[1] if i%2 == 1
umap<int, set<int>> inv[2];

int query(int l, int r) {
    // parity of all bits must be even
    int par = acc[r] ^ acc[l];
    if (par != 0) return -1;

    // if range is 0, 0 ops are needed
    if (sm[r] - sm[l] == 0) return 0;

    // if the length of the range is odd, 1 operation on the whole range is enough
    if ((r - l) % 2 == 1) return 1;

    // if there is one side that has no bits, in can be done in 1 op only
    if ((a[l] == 0) || (a[r - 1] == 0)) return 1;

    // otherwise, we can use 2 ops or it's impossible
    // check if there is a "splitting point"
    if (inv[!(l % 2)].count(acc[l])) {
        // check if it is in range
        set<int> &list = inv[!(l % 2)][acc[l]];
        auto it = list.lower_bound(l);
        if (it != list.end() && *it < r) return 2;
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    a.resize(N);
    rep(i, N) cin >> a[i];

    acc.resize(N + 1);
    rep(i, N) acc[i + 1] = acc[i] ^ a[i];

    sm.resize(N + 1);
    rep(i, N) sm[i + 1] = sm[i] + a[i];

    rep(i, N + 1) inv[i % 2][acc[i]].insert(i);

    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        l -= 1;

        cout << query(l, r) << "\n";
    }
}
