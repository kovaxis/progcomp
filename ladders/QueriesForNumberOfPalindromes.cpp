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

struct St {
    vector<vector<int>> node;

    St() {}
    void resize(int N) { node.resize(4 * N); }

    void build(const vector<int>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl != vr) {
            int vm = (vl + vr) / 2;
            build(a, 2 * v, vl, vm);
            build(a, 2 * v + 1, vm + 1, vr);
        }
        node[v].resize(vr - vl + 2);
        rep(i, vl, vr + 1) node[v][i - vl + 1] = a[i];
        sort(node[v].begin() + 1, node[v].end());
        rep(i, 1, node[v].size()) node[v][i] += node[v][i - 1];
    }

    // return the sum of `min(x, mn)` for all elements `x`.
    int query(int l, int r, int mn, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            // binsearch
            int sl = 0, sr = node[v].size() - 1;
            while (sl != sr) {
                int m = (sl + sr + 1) / 2;
                if (node[v][m] - node[v][m - 1] <= mn) {
                    sl = m;
                } else {
                    sr = m - 1;
                }
            }
            return node[v][sl] + (node[v].size() - 1 - sl) * mn;
        }
        int vm = (vl + vr) / 2;
        int val = 0;  // neutral element
        if (l > r) return val;
        if (l <= vm)
            val += query(l, min(r, vm), mn, 2 * v, vl, vm);  // query op
        if (r >= vm + 1)
            val += query(max(l, vm + 1), r, mn, 2 * v + 1, vm + 1,
                         vr);  // query op
        return val;
    }
};

void manacher(const string& s, vector<int>& p) {
    int N = s.size(), P = 2 * N - 1;
    p.assign(P, 0);
    int l = 0, r = -1;
    rep(i, P) {
        int d = (r >= i ? min(p[l + r - i], r - i + 2) : i % 2);
        while (i - d >= 0 && i + d < P && s[(i - d) / 2] == s[(i + d) / 2])
            d += 2;
        p[i] = d;
        if (i + d - 2 > r) l = i - d + 2, r = i + d - 2;
    }
    rep(i, P) p[i] -= 1;
}

int N, P, Q;
string s;
vector<int> palis;
vector<int> up, dn;
St upst, dnst;

int upfn(int i) { return i < 0 ? (i - 1) / 2 : i / 2; }
int upfnacc(int i) {
    i++;
    return 2 * (i / 2 * (i / 2 - 1) / 2) + i % 2 * (i / 2);
}
int dnfn(int i) { return upfn(P - 1 - i); }
int dnfnacc(int i) { return upfnacc(P - 1 - i); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> Q;
    N = s.size(), P = 2 * N - 1;
    up.resize(P), dn.resize(P);

    manacher(s, palis);
    rep(i, P) palis[i] = (palis[i] + 1) / 2;
    rep(i, P) up[i] = palis[i] - upfn(i);
    rep(i, P) dn[i] = palis[i] - dnfn(i);
    upst.build(up), dnst.build(dn);

    cerr << "built" << endl;

    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        l = (l - 1) * 2, r = (r - 1) * 2;
        int c = (l + r) / 2;

        int ans = 0;
        ans += upst.query(l, c, -upfn(l - 1)) + upfnacc(c) - upfnacc(l - 1);
        ans += dnst.query(c + 1, r, -dnfn(r + 1)) + dnfnacc(c + 1) -
               dnfnacc(r + 1);
        cout << ans << '\n';
    }
}
