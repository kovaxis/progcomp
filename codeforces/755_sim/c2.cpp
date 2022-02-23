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

// b(i, j): sum i <= k <= j (-1)^(j - k) * a[k]

struct Node {
    // amount of subsegments such that b(i, k) >= 0 for all i <= k <= j
    // and b(i, j) == 0
    ll count;
    // values of a[] for the represented segment
    vector<ll> pref;
    // subsegments [i', j] such that their end coincides with the end of the
    // segment, and b(i', k) >= 0 for all i' <= k <= j. stores pairs of b() ->
    // amount of subsegments
    umap<ll, int> suff;

    Node() : count(0) {}
    Node(ll a) : count(a == 0), pref{a}, suff{{a, 1}} {}
};

int N;
vector<ll> a;

Node merge(int vl, int vr) {
    if (vl == vr) return Node(a[vl]);

    int vm = (vl + vr) / 2;
    Node l = merge(vl, vm), r = merge(vm + 1, vr);

    l.count += r.count;
    // combine suffixes of the left segment with prefixes of the right segment
    ll rsum = 0, rmin = -INF, rmax = INF;
    rep(i, r.pref.size()) {
        // the b() sum of the rprefix up to now
        rsum = r.pref[i] - rsum;

        // depending on the parity of `i`, the condition that b(lsuff..rpref) >=
        // 0 imposes different conditions on b(lsuff):
        //
        // i % 2 == 0: b(rpref) - b(lsuff) >= 0
        // i % 2 == 1: b(rpref) + b(lsuff) >= 0
        //
        // these conditions are accumulated for all k <= i

        // the value such that b(lsuff..rpref) == 0
        ll need = i % 2 ? -rsum : rsum;
        if (i % 2) rmin = max(rmin, need);
        if (i % 2 - 1) rmax = min(rmax, need);
        if (need < rmin || need > rmax) continue;
        if (!l.suff.count(need)) continue;
        l.count += l.suff[need];
    }

    // new valid suffixes are: all right suffixes plus the left suffixes that
    // can be concatenated with the entire right segment.
    // this means that if rmin <= b(lsuff) <= rmax, then a new suffix zsuff can
    // be created from the concatenation of lsuff and rseg, with b(zsuff) = +/-
    // b(lsuff) + b(rseg)
    auto& zsuff = r.suff;
    for (auto suff : l.suff) {
        ll lsum = suff.first;
        if (lsum < rmin || lsum > rmax) continue;
        if (r.pref.size() % 2) lsum = -lsum;
        zsuff[lsum + rsum] += suff.second;
    }
    swap(l.suff, zsuff);

    for (ll a : r.pref) l.pref.push_back(a);

    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        ll ans = merge(0, N - 1).count;

        cout << ans << "\n";
    }
}