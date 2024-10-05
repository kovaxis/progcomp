// 5N

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

ll N, S;
vector<ll> atlvl;

ll leastsum(ll K) {
    cerr << "calculating sum for K = " << K << endl;
    ll sm = 0, pow = 1, n = N, d = 1;
    while (n > 0) {
        if (pow > n) pow = n;
        sm += d * pow;
        n -= pow;
        pow *= K;
        d += 1;
    }
    cerr << "sum for K = " << K << ": " << sm << endl;
    return sm;
}

ll findk() {
    ll l = 1, r = N;
    while (l != r) {
        ll m = (l + r) / 2;
        if (leastsum(m) <= S) r = m;
        else l = m + 1;
    }
    return l;
}

bool solve() {
    if (N * (N + 1) / 2 < S) return false;
    ll K = findk();
    if (K == N) return false;
    cerr << "using K = " << K << endl;
    S = N * (N + 1) / 2 - S;
    atlvl.assign(N, 1);
    ll depth = 1, total = 1, rem = 0, last = N;
    while (S > 0) {
        while (rem == 0) {
            depth += 1;
            total *= K;
            rem = total - 1;
        }
        ll mv = last - depth;
        // cerr << "moving node from depth " << last << " to " << depth << " (there are " << rem << " spaces remaining at this depth)";
        mv = min(mv, S);
        atlvl[last - 1] -= 1;
        atlvl[last - mv - 1] += 1;
        rem -= 1;
        S -= mv;
        last -= 1;
        // cerr << "  new remaining delta is " << S << endl;
    }
    rep(i, N) if (atlvl[i] == 0) {
        atlvl.resize(i);
        break;
    }

    // cerr << "answer:" << endl;
    // rep(i, atlvl.size()) cerr << "  depth " << i + 1 << ": " << atlvl[i] << endl;

    vector<vector<int>> ids(N);
    int nxtid = 1;
    cout << "Yes" << endl;
    rep(d, N) {
        rep(i, atlvl[d]) {
            if (d > 0) {
                int p = ids[d - 1][i / K];
                cout << p << " ";
            }
            ids[d].push_back(nxtid++);
        }
    }
    cout << endl;

    return true;
}

int main() {
    cin >> N >> S;
    if (!solve()) {
        cout << "No" << endl;
    }
}
