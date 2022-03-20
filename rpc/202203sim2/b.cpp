
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)
#define repx(i, a, n) for (int i = a; i < n; i++)

const int INF = 1e9;

template <class T>
struct Sparse {
    vector<vector<T>> st;

    void resize(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));
    }

    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return min(st[i][l], st[i][r - (1 << i)]);
    }
};

template <class T>
struct Stl {
    vector<pair<T, T>> node;
    void reset(int N) { node.assign(4 * N, {0, 0}); }

    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first += lazy;
        node[2 * v].second += lazy;
        node[2 * v + 1].first += lazy;
        node[2 * v + 1].second += lazy;
        lazy = 0;
    }

    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first += val;
            node[v].second += val;
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first = min(node[2 * v].first, node[2 * v + 1].first);
    }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        int vm = (vl + vr) / 2;
        T val = INF;
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val = min(val, query(l, min(r, vm), 2 * v, vl, vm));
        val = min(val, query(max(l, vm), r, 2 * v + 1, vm, vr));
        return val;
    }
};

vector<int> suffixarray(const string& s) {
    int N = s.size() + 1;
    vector<int> p(N), p2(N), c(N), c2(N), cnt(256);
    rep(i, N) cnt[s[i]] += 1;
    repx(b, 1, 256) cnt[b] += cnt[b - 1];
    rep(i, N) p[--cnt[s[i]]] = i;
    repx(i, 1, N) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    for (int k = 1; k < N; k <<= 1) {
        int C = c[p[N - 1]] + 1;
        cnt.assign(C + 1, 0);
        for (int& pi : p) pi = (pi - k + N) % N;
        for (int cl : c) cnt[cl + 1] += 1;
        rep(i, C) cnt[i + 1] += cnt[i];
        rep(i, N) p2[cnt[c[p[i]]]++] = p[i];
        c2[p2[0]] = 0;
        repx(i, 1, N) c2[p2[i]] =
            c2[p2[i - 1]] + (c[p2[i]] != c[p2[i - 1]] ||
                             c[(p2[i] + k) % N] != c[(p2[i - 1] + k) % N]);
        swap(c, c2), swap(p, p2);
    }
    p.erase(p.begin());
    return p;
}

vector<int> makelcp(const string& s, const vector<int>& p) {
    int N = p.size(), k = 0;
    vector<int> r(N), lcp(N);
    rep(i, N) r[p[i]] = i;
    rep(i, N) {
        if (r[i] + 1 >= N) {
            k = 0;
            continue;
        }
        int j = p[r[i] + 1];
        while (i + k < N && j + k < N && s[i + k] == s[j + k]) k += 1;
        lcp[r[i]] = k;
        if (k) k -= 1;
    }
    return lcp;
}

string A;
int N, M;
vector<string> S;
vector<int> sa, lcp;
Sparse<int> slcp;
vector<bool> isneedle, ishay;
vector<int> lookup, lookdown;
vector<int> common;
Stl<int> possible;

string tmps;

int getlcp(int i, int j) { return slcp.query(i, j); }

void blockrange(int l, int r) {
    l = (l % N + N) % N;
    r = (r % N + N) % N;
    if (r < l && r == 0) r = N;
    if (l == r) return;
    if (r < l) {
        // cerr << "    dividing blockrange on " << l << ", " << r << endl;
        blockrange(0, r);
        blockrange(l, N);
        return;
    }

    // cerr << "    blocking raw range [" << l << ", " << r << ")" << endl;
    possible.update(l, r, 1);
    // cerr << "    blocked" << endl;
}

// is the actual score equal to or lower than `score`?
bool canreach(int score) {
    // cerr << "checking score = " << score << endl;
    possible.reset(N);
    // cerr << "  reset stl" << endl;
    rep(i, N) {
        if (common[i] <= score) continue;
        int r = N - score;
        if (r == N) return false;
        // cerr << "  blocking range [" << i - r + 1 << ", " << i + 1 << ")"
        //     << endl;
        blockrange(i - r + 1, i + 1);
    }
    // cerr << "possible query is = " << possible.query(0, N) << endl;
    return possible.query(0, N) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    cin >> A;
    N = A.size();
    S.resize(M);
    rep(i, M) cin >> S[i];

    tmps += A;
    tmps += A;
    tmps += '$';
    rep(i, M) {
        tmps += S[i];
        tmps += '$';
    }
    // cerr << "tmpstring:" << endl << tmps << endl;

    ishay.assign(tmps.size(), false);
    isneedle.assign(tmps.size(), false);
    rep(i, N) ishay[i] = true;
    {
        int j = 2 * N;
        rep(i, M) {
            j += 1;
            for (char c : S[i]) isneedle[j++] = true;
        }
    }
    /*
    cerr << "ishay:" << endl;
    rep(i, ishay.size()) cerr << " H"[ishay[i]];
    cerr << endl;
    cerr << "isneedle:" << endl;
    rep(i, isneedle.size()) cerr << " N"[isneedle[i]];
    cerr << endl;
    */

    sa = suffixarray(tmps);
    lcp = makelcp(tmps, sa);
    slcp.resize(lcp.size());
    rep(i, lcp.size()) slcp.set(i, lcp[i]);
    slcp.init();
    /*
    cerr << "suff arr:" << endl;
    rep(i, sa.size()) cerr << i << ": " << tmps.substr(sa[i]) << endl;
    cerr << "lcp:" << endl;
    rep(i, lcp.size()) cerr << lcp[i] << " ";
    cerr << endl;
    */

    lookup.assign(sa.size(), -1);
    int lastneedle = -1;
    rep(i, sa.size()) {
        if (isneedle[sa[i]]) {
            lastneedle = i;
        }
        lookup[i] = lastneedle;
    }

    lookdown.assign(sa.size(), -1);
    lastneedle = -1;
    rep(ii, sa.size()) {
        int i = sa.size() - 1 - ii;
        if (isneedle[sa[i]]) lastneedle = i;
        lookdown[i] = lastneedle;
    }

    common.resize(N);
    rep(i, sa.size()) {
        if (ishay[sa[i]]) {
            // cerr << "checking hay " << tmps.substr(sa[i]) << " at " << i
            //     << endl;
            int sscore = 0;
            int up = lookup[i];
            if (up != -1) sscore = max(sscore, getlcp(up, i));
            int dn = lookdown[i];
            if (dn != -1) sscore = max(sscore, getlcp(i, dn));
            // cerr << "  subscore is " << sscore << endl;
            // cerr << "  up is " << up << endl;
            // cerr << "  down is " << dn << endl;
            common[sa[i]] = min(sscore, N);
        }
    }
    /*
    cerr << "common:" << endl;
    rep(i, N) cerr << common[i] << " ";
    cerr << endl;
    */

    int l = 0, r = A.size();
    while (l != r) {
        int m = (l + r) / 2;
        bool canr = canreach(m);
        // cerr << "  works: " << canr << endl;
        if (canr) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << endl;
}