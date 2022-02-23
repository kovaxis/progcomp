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

template <class T>
struct St {
    vector<T> node;

    St() {}

    template <class E, class OP>
    void build(const vector<E>& a, const OP& op, int v = 1, int vl = 0,
               int vr = -1) {
        node.resize(4 * a.size());
        if (a.size() == 0) return;
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] = op(a[vl]);  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, op, 2 * v, vl, vm);
        build(a, op, 2 * v + 1, vm + 1, vr);
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        T val = 0;  // neutral element
        if (node.size() == 0 || l > r) return val;
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        if (l <= vm) val += query(l, min(r, vm), 2 * v, vl, vm);  // query op
        if (r >= vm + 1)
            val += query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr);  // query op
        return val;
    }
};

int N;
vector<int> araw, braw;
vector<int> a;

// constant, c coefficient
ll addz;
vector<pair<ll, ll>> addp, addn;
St<ll> addp0, addp1;
St<ll> addn0, addn1;

//  objective: c, a2, a3, a4, a5
//
//  0,  0,  0,  0,  0
//    + c
//  c,  c,  c,  c,  c,  c
//    + a2 - c
//  c, a2,  c, a2,  c,  a2
//    + a3 - c
//  c, a2, a3, a2,  c, a2 + a3 - c
//    + a4 - a2
//  c, a2, a3, a4,  c, a2 + a3 - c
//    + a5 - c
//  c, a2, a3, a4, a5, a2 + a3 - c
//    + a6 - a2 - a3 + c
//  c, a2, a3, a4, a5, a6

// orders first degree polynomials by their zeros.
bool cmpzero(pair<ll, ll> l, pair<ll, ll> r) {
    // a0 + a1 * c == 0
    // c == -a0 / a1
    //
    // lc < rc
    // -l0 / l1 < -r0 / r1
    // l0 / l1 > r0 / r1
    // assume l1 > 0 && r1 > 0
    // l0 * r1 > r0 * l1
    assert(abs(l.first) < 1e9 && abs(l.second) < 1e9 && abs(r.first) < 1e9 &&
           abs(r.second) < 1e9);
    if (l.second < 0) l.second *= -1, l.first *= -1;
    if (r.second < 0) r.second *= -1, r.first *= -1;
    return l.first * r.second > r.first * l.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    araw.resize(N + 1), braw.resize(N + 1), a.resize(N + 1);
    rep(i, N) cin >> araw[i + 1];
    rep(i, N) cin >> braw[i + 1];
    rep(i, 1, N + 1) a[i] = braw[i] - araw[i];

    // constant, c coefficient
    vector<pair<ll, ll>> tmp(N + 1);
    rep(i, 1, N + 1) {
        pair<ll, ll> add = i == 1 ? pair<ll, ll>{0, 1} : pair<ll, ll>{a[i], 0};
        add.first -= tmp[i].first, add.second -= tmp[i].second;
        // cerr << "tmp[" << i << "] is {" << tmp[i].first << ", " <<
        // tmp[i].second
        //     << "}, adding {" << add.first << ", " << add.second
        //     << "} to all multiples" << endl;
        if (add.second > 0) addp.push_back(add);
        if (add.second < 0) addn.push_back(add);
        if (add.second == 0) addz += abs(add.first);
        for (int j = i; j <= N; j += i)
            tmp[j].first += add.first, tmp[j].second += add.second;
    }
    assert(tmp[1] == (pair<ll, ll>{0, 1}));
    rep(i, 2, N + 1) assert(tmp[i] == (pair<ll, ll>{a[i], 0}));

    sort(addp.begin(), addp.end(), cmpzero);
    sort(addn.begin(), addn.end(), cmpzero);

    /*
    cerr << "addz = " << addz << endl;
    cerr << "addp =";
    for (auto& p : addp) cerr << " (" << p.first << " + " << p.second << "*c)";
    cerr << endl;
    cerr << "addn =";
    for (auto& p : addn) cerr << " (" << p.first << " + " << p.second << "*c)";
    cerr << endl;
    // */

    addp0.build(addp, [](pair<ll, ll> a) { return a.first; });
    addp1.build(addp, [](pair<ll, ll> a) { return a.second; });
    addn0.build(addn, [](pair<ll, ll> a) { return a.first; });
    addn1.build(addn, [](pair<ll, ll> a) { return a.second; });

    int Q;
    cin >> Q;
    rep(q, Q) {
        int x;
        cin >> x;
        a[1] = x - araw[1];

        ll ans = addz;

        {
            int l = -1, r = addp.size() - 1;
            while (l != r) {
                int m = (l + r + 1) / 2;
                if (addp[m].first + addp[m].second * a[1] >= 0) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            int n = (int)addp.size() - 1;
            // cerr << "querying addp[0, " << l << "] - addp[" << l + 1 << ", "
            //     << n << "]" << endl;
            ans += addp0.query(0, l) - addp0.query(l + 1, n);
            ans += a[1] * (addp1.query(0, l) - addp1.query(l + 1, n));
        }

        {
            int l = 0, r = addn.size();
            while (l != r) {
                int m = (l + r) / 2;
                if (addn[m].first + addn[m].second * a[1] >= 0) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            int n = (int)addn.size() - 1;
            // cerr << "querying -addn[0, " << l - 1 << "] + addn[" << l << ", "
            // << n << "]" << endl;
            ans += -addn0.query(0, l - 1) + addn0.query(l, n);
            ans += a[1] * (-addn1.query(0, l - 1) + addn1.query(l, n));
        }

        cout << ans << "\n";
    }
}
