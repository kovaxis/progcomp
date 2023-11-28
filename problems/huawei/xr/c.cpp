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

float quickread() {
    static string s;
    cin >> s;
    s.push_back(0);
    char *c = &s[0];
    bool neg = false;
    if (*c == '-') c++, neg = true;
    float x = 0;
    while (*c && *c != '.') x = 10 * x + (*c - '0'), c++;
    if (*c == '.') c++;
    float mult = 1;
    while (*c) mult *= 0.1, x += mult * (*c - '0'), c++;
    if (neg) x = -x;
    return x;
}

struct Frame {
    int thresh;
    int user;
    int l, r;
};

const float W = 192 / log(2.0);

int N, K, T, R, J;
float S0[1000][10][10][100]; // t, k, r, n
float D[10][10][100][100];   // k, r, n1, n2
Frame F[5000];               // j

struct Answer {
    float P[1000][10][10][100]; // t, k, r, n

    Answer() {
        memset(&P, 0, sizeof(P));
    }
};

Answer ans;

float score_bits(int j, int t, const Answer &ans) {
    float transmitted = 0;
    Frame f = F[j];
    rep(k, K) {
        int bands = 0;
        float logsum = 0;
        rep(r, R) {
            if (ans.P[t][k][r][f.user] > 0) {
                float interf1 = 0;
                rep(m, N) if (m != f.user) {
                    if (ans.P[t][k][r][m] > 0) {
                        interf1 += D[k][r][f.user][m];
                    }
                }

                float interf2 = 0;
                rep(k2, K) if (k2 != k) {
                    rep(n2, N) if (n2 != f.user) {
                        interf2 += S0[t][k2][r][f.user] * ans.P[t][k2][r][n2] * exp(-D[k2][r][f.user][n2]);
                    }
                }

                // logsum += log(S0[t][k][r][f.user] * ans.P[t][k][r][f.user] / (1 + interf2)) + interf1;
                logsum += log(S0[t][k][r][f.user] * ans.P[t][k][r][f.user]) + interf1 - interf2;
                bands += 1;
            }
        }
        if (bands != 0) transmitted += bands * log1p(exp(logsum / bands));
        // if (bands != 0) transmitted += logsum;
    }
    return transmitted;
}

int score_frames(const Answer &ans) {
    int frames = 0;
    rep(j, J) {
        Frame f = F[j];
        float transmitted = 0;
        repx(t, f.l, f.r) {
            transmitted += score_bits(j, t, ans);
        }
        frames += (W * transmitted >= f.thresh);
    }
    return frames;
}

float score(const Answer &ans) {
    int frames = score_frames(ans);

    float power = 0;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) power += ans.P[t][k][r][n];

    return frames - power * 1e-6f;
}

float score_without_interference(const Answer &ans, int t, int k, int n) {
    int bands = 0;
    float product = 1;
    rep(r, R) if (ans.P[t][k][r][n] > 0) {
        bands += 1;
        product *= S0[t][k][r][n] * ans.P[t][k][r][n];
    }
    return bands * log1p(powf(product, 1.0f / bands));
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    // Read input
    cin >> N >> K >> T >> R;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) S0[t][k][r][n] = quickread();
    rep(k, K) rep(r, R) rep(m, N) rep(n, N) D[k][r][m][n] = quickread();
    cin >> J;
    rep(j, J) {
        int _j, s, u, l, d;
        cin >> _j >> s >> u >> l >> d;
        F[j] = {s, u, l, l + d};
    }

    // Read solution
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) ans.P[t][k][r][n] = quickread();

    cerr << "score: " << score(ans) << endl;
}
