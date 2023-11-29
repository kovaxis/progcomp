#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#ifndef ENABLE_CERR
#define cerr \
    if (0) cerr
#endif

int main() {
    ll seed;
    cin >> seed;
    static mt19937 rng(seed);

    int N = int(1e4);

    vector<float> vals(N);
    rep(i, N) vals[i] = rng();
    vector<int> ivals(N);
    rep(i, N) ivals[i] = uniform_int_distribution<int>(1, 10)(rng);

    float acc = 0;
    rep(i, N) rep(j, N) {
        // acc += powf(vals[i], 1.0 / ivals[j]);
        acc += exp(vals[i]) / ivals[j];
    }

    cout << acc << endl;
}