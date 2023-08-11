#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const int MX = 200001;
// const int MX = 21;

int N;
vector<ll> A;

bitset<MX> canreach;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    canreach.set(0);
    rep(i, N) {
        bitset<MX> mask = 0;
        mask = ~mask;
        cerr << "full mask: " << mask << endl;
        mask <<= i;
        mask &= canreach;
        mask <<= A[i];
        canreach |= mask;
        cerr << "canreach after " << i << ": " << canreach << endl;
    }

    ll sm = 0, best = 0;
    rep(i, 2 * N + 1) {
        if (i < N) sm += A[i];
        if (canreach[i]) {
            ll s = sm - i;
            best = max(best, s);
            cerr << "can lose at " << i << ", with " << i << " points towards unlock and " << sm - i << " victory points" << endl;
        } else {
            cerr << "cant lose at " << i << endl;
        }
    }

    cout << best << endl;
}
