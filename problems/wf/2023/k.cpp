#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

ll MOD = 9223372036737335297ll, P = 4173715341681463ll;
string letters;
ll ltrhash[128];

int T = 100;

int N, F, W;
vector<string> labels;
vector<string> dict;
set<ll> dictset;
vector<bool> isword;
vector<double> dp, dplast, invmult;

template <class OP>
void iterf(int fn, OP op) {
    int f = 0;
    while (f < F) {
        op(f);
        rep(i, N) if (((f >> 3 * i) & 7) == fn - 1) {
            f |= 7 << 3 * i;
        }
        else break;
        f += 1;
    }
}

int withface(int f, int i, int ff) {
    f &= ~(7 << 3 * i);
    f |= ff << 3 * i;
    return f;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    {
        rep(c, 26) letters.push_back('A' + c);
        rep(c, 10) letters.push_back('0' + c);
        ll p = P;
        for (char c : letters) {
            ltrhash[c] = p;
            p = (__int128)p * P % MOD;
        }
    }

    cin >> N >> W;
    labels.resize(N);
    rep(i, N) cin >> labels[i];
    dict.resize(W);
    rep(j, W) cin >> dict[j];

    cerr << "processing dict" << endl;

    rep(w, W) {
        ll h = 0;
        for (char c : dict[w]) {
            h = (h + ltrhash[c]) % MOD;
        }
        dictset.insert(h);
    }

    cerr << "identifying winners" << endl;
    F = 1 << (3 * N);
    isword.resize(F);
    bool anywin = false;
    iterf(6, [&](int f) {
        ll h = 0;
        rep(i, N) {
            char c = labels[i][(f >> 3 * i) & 7];
            h = (h + ltrhash[c]) % MOD;
        }
        isword[f] = dictset.count(h);
        if (isword[f]) anywin = true;
    });
    if (!anywin) {
        cout << "impossible" << endl;
        return 0;
    }

    cerr << "invmult" << endl;
    invmult.resize(F);
    iterf(7, [](int f) {
        int mult = 1;
        rep(i, N) if (((f >> 3 * i) & 7) == 6) mult *= 6;
        invmult[f] = 1.0 / mult;
    });

    dplast.assign(F, 0);
    dp.assign(F, 0);
    rep(f, F) dp[f] = (double)isword[f];
    repx(t, 1, T + 1) {
        // cerr << "computing time " << t << endl;
        iterf(6, [](int f) {
            repx(m, 1, 1 << N) {
                int f2 = f;
                rep(i, N) if ((m >> i) & 1) f2 = withface(f2, i, 6);
                dp[f2] += dp[f] * invmult[f2];
            }
        });

        int fany = 0;
        rep(i, N) fany |= 6 << 3 * i;
        // cerr << "current answer is " << dp[fany] << endl;
        // ans += t * (dp[fany] - dplast[fany]);

        swap(dp, dplast);
        dp.assign(F, 0);

        iterf(6, [](int f) {
            if (isword[f]) {
                dp[f] = 1;
                return;
            }
            double res = 1e100;
            repx(m, 1, 1 << N) {
                int f2 = f;
                rep(i, N) if ((m >> i) & 1) f2 = withface(f2, i, 6);
                double d = 1 + dplast[f2];
                res = min(res, d);
            }
            dp[f] = res;
        });
    }

    int fany = 0;
    rep(i, N) fany |= 6 << 3 * i;
    double ans = dplast[fany];
    cout << fixed << setprecision(12) << ans << endl;
}
