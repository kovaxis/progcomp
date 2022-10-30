#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<ll> a;
// leftmost index of segments with r = n
vector<int> lpair;
vector<bool> dp;

// fw:
// l -> sum[l, R) - off
// real = mem + off
// mem = real - off
//
// inv:
// sum[l, R) - off -> set<l>
map<ll, set<int>> invs;
ll off;

void printsums(int R) {
    cerr << "sums at R = " << R << ":" << endl;
    for (auto& [smem, st] : invs) {
        ll s = smem + off;
        for (int l : st) {
            cerr << "  [" << l << ", " << R << ") = " << s << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        a.resize(N), lpair.resize(N + 1), dp.resize(N + 1);
        rep(i, N) cin >> a[i];
        rep(i, N) {
            ll x;
            cin >> x;
            a[i] = x - a[i];
        }
        rep(i, N + 1) lpair[i] = i;
        rep(i, M) {
            int l, r;
            cin >> l >> r;
            l -= 1;
            lpair[r] = min(lpair[r], l);
        }

        cerr << "a:";
        rep(i, N) cerr << " " << a[i];
        cerr << endl;

        invs.clear();
        off = 0;
        invs[0 - off].insert(0);
        dp[0] = true;
        bool ans = false;
        cerr << "dp[0] = 1" << endl;
        printsums(0);
        repx(r, 1, N + 1) {
            // move global R by 1
            off += a[r - 1];

            // cerr << "computing dp[" << r << "]" << endl;

            bool can = (a[r - 1] == 0 ? dp[r - 1] : false);
            int L = lpair[r];
            auto& st = invs[0 - off];
            if (st.lower_bound(L) != st.end()) {
                // found a segment that satisfies constraints
                int l = *st.lower_bound(L);
                cerr << "can clear [0, " << l << "), a segment exists in [" << L
                     << ", " << r << ") and the sum in [" << l << ", " << r
                     << ") is 0, so we can clear [0, " << r << ")" << endl;
                // cerr << "using segment [" << *(--st.end()) << ", " << r
                //     << ") for R = " << r << endl;
                can = true;
            }

            cerr << "dp[" << r << "] = " << can << endl;

            dp[r] = can;
            if (can) {
                // add sum [r, r)
                invs[0 - off].insert(r);
                if (r == N) ans = true;
            }
            printsums(r);
        }

        cout << (ans ? "YES" : "NO") << '\n';
    }
}
