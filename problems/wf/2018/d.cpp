#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

ll N, D, R;
double DP[501][501], Q[501][501], Qsum[501][502];

double dp(int n, int k) {
    if (k < 0 || k > D) return 0.0;
    return DP[n][k];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> D >> R;

    double ans = 0;
    repx(x, 1, 1 + D + 1) {
        int y = x - 2;
        memset(&DP, 0, sizeof(DP));
        DP[0][0] = 1;
        if (y >= 0) {
            repx(n, 1, N + 1) rep(k, D + 1) {
                DP[n][k] = dp(n, k - 1) + dp(n - 1, k) - dp(n - 1, k - y - 1);
            }
        }

        memset(&Q, 0, sizeof(Q));
        rep(u, N + 1) {
            if (u * x > D) break;
            rep(m, N + 1) {
                int d = N - u - m;
                int A = D - x * u - (x - 1) * m;
                if (A < 0) break;

                double num = 1, den = 1;
                repx(nn, N - u - d + 1, N + 1) num *= nn;
                repx(uu, 1, u + 1) den *= uu;
                repx(dd, 1, d + 1) den *= dd;
                repx(nd, N, N + D) den *= nd;

                double q = 0;
                if (u == 0) {
                    repx(d, 1, D + 1) num *= d;
                    q += dp(d, A) * num / den;
                } else {
                    repx(ab, A + 1, D + 1) num *= ab;
                    repx(uab, u, u + A) num *= uab;
                    rep(b, A + 1) {
                        q += dp(d, b) * num / den;

                        num *= A - b;
                        den *= u + A - b - 1;
                    }
                }
                Q[u][d] = q;
            }
        }

        memset(&Qsum, 0, sizeof(Qsum));
        rep(u, N + 1) {
            rep(d, N + 1) Qsum[u][d + 1] = Qsum[u][d] + Q[u][d];
        }

        repx(i, 1, R + 1) {
            double p = 0;
            rep(u, i) p += Qsum[u][N - i + 1];
            ans += x * p;
        }
    }

    cout << fixed << setprecision(16) << ans << endl;
}
