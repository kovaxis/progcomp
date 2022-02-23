#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll INF = 1e15;

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll& x) const {
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

template <class T>
struct Sparse {
    vector<vector<T>> st;

    Sparse() {}

    void resize(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }
    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        rep(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));  // query op
    }

    // query minimum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return min(st[i][l], st[i][r - (1 << i)]);  // query op
    }
};

using Node = map<ll, int>;
Node merge(Node a, Node b) {
    if (b.size() > a.size()) swap(a, b);
    for (auto p : b) a[p.first] += p.second;
    return a;
}

struct St {
    vector<Node> node;

    St() {}
    void resize(int N) { node.resize(4 * N); }

    void build(const vector<ll>& a, int k, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            if (vl % 2 == k % 2) {
                node[v] = Node{
                    {a[vl], 1}  // construction
                };
            } else {
                node[v] = Node{};  // construction
            }
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, k, 2 * v, vl, vm);
        build(a, k, 2 * v + 1, vm + 1, vr);
        node[v] = merge(node[2 * v], node[2 * v + 1]);  // query op
    }

    int query(int l, int r, ll val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v][val];
        int vm = (vl + vr) / 2;
        int cnt = 0;  // neutral element
        if (l <= vm)
            cnt += query(l, min(r, vm), val, 2 * v, vl, vm);  // query op
        if (r >= vm + 1)
            cnt += query(max(l, vm + 1), r, val, 2 * v + 1, vm + 1,
                         vr);  // query op
        return cnt;
    }
};

int N;
vector<ll> a, b;
Sparse<ll> bmin[2];
St bcount[2];

ll getoffset(int i, int k) {
    ll b0 = b[i - 1];
    if (k % 2 == i % 2) b0 = -b0;
    return b0;
}

ll getbmin(int l, int r) {
    ll mn = INF;
    rep(k, 2) {
        ll submn = bmin[k].query(l, r) - getoffset(l, k);
        mn = min(mn, submn);
    }
    return mn;
}

ll getbcount(int l, int r, ll v) {
    ll cnt = 0;
    rep(k, 2) cnt += bcount[k].query(l, r, v + getoffset(l, k));
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.assign(N + 1, 0), b.assign(N + 1, 0);
        rep(i, N) cin >> a[i + 1];

        rep(i, 1, N + 1) b[i] = a[i] - b[i - 1];

        rep(k, 2) {
            bmin[k].resize(N + 1);
            rep(i, N + 1) bmin[k].set(i, i % 2 == k ? b[i] : INF);
            bmin[k].init();
        }

        rep(k, 2) bcount[k].build(b, k);

        ll ans = 0;
        rep(i, 1, N + 1) {
            ll offset = b[i - 1];

            int j;
            {
                int l = i, r = N;
                while (l != r) {
                    int m = (l + r + 1) / 2;
                    if (getbmin(i, m) >= 0) {
                        l = m;
                    } else {
                        r = m - 1;
                    }
                }
                j = l;
            }

            ans += getbcount(i, j, 0);
        }

        cout << ans << "\n";
    }
}