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

const float EPS = 1e-6;

// static mt19937 rng(7641206241ll);
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Frame {
    int thresh;
    int user;
    int l, r;
};

const float W = 192 / log(2.0);

int N, K, T, R, J;
float S0[1000][10][10][100]; // t, r, k, n
float D[10][10][100][100];   // r, k, n1, n2
Frame F[5000];               // j

struct Answer {
    float P[1000][10][10][100]; // t, r, k, n

    Answer() {
        memset(&P, 0, sizeof(P));
    }
};

float score_bits(int j, int t, const Answer &ans) {
    float transmitted = 0;
    Frame f = F[j];
    rep(k, K) {
        int bands = 0;
        float logsum = 0;
        rep(r, R) {
            if (ans.P[t][r][k][f.user] > 0) {
                float interf1 = 0;
                rep(m, N) if (m != f.user) {
                    if (ans.P[t][r][k][m] > 0) {
                        interf1 += D[r][k][f.user][m];
                    }
                }

                float interf2 = 0;
                rep(k2, K) if (k2 != k) {
                    rep(n2, N) if (n2 != f.user) {
                        interf2 += S0[t][r][k2][f.user] * ans.P[t][r][k2][n2] * exp(-D[r][k2][f.user][n2]);
                    }
                }

                logsum += log(S0[t][r][k][f.user] * ans.P[t][r][k][f.user] / (1 + interf2)) + interf1;
                bands += 1;
            }
        }
        if (bands != 0) transmitted += bands * log1p(exp(logsum / bands));
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
        frames += (W * transmitted - EPS >= f.thresh);
    }
    return frames;
}

float score(const Answer &ans) {
    int frames = score_frames(ans);

    float power = 0;
    rep(t, T) rep(r, R) rep(k, K) rep(n, N) power += ans.P[t][r][k][n];

    return frames - power * 1e-6f;
}

struct ScoreKeep {
    Answer ans;
    float interf2[1000][10][10][100]; // t, r, k, n
    float logsum[1000][10][100];      // t, k, n
    int rcount[1000][10][100];        // t, k, n
    float G[5000];                    // j
    int frames = 0;

    int frameptr[1000][100]; // t, n

    ScoreKeep() {
        memset(&logsum, 0, sizeof(logsum));
        memset(&rcount, 0, sizeof(rcount));
        memset(&interf2, 0, sizeof(interf2));
        memset(&G, 0, sizeof(G));
        memset(&frameptr, -1, sizeof(frameptr));
        rep(j, J) {
            repx(t, F[j].l, F[j].r) frameptr[t][F[j].user] = j;
        }
    }

    void set(int t, int r, int k, int n, float p) {
        // remove all cell scores in this band from their frame scores
        rep(k2, K) rep(n2, N) if ((k2 == k && n2 == n) || ans.P[t][r][k2][n2] > 0) {
            int j = frameptr[t][n2];
            float old = G[j];
            if (rcount[t][k2][n2]) G[j] -= rcount[t][k2][n2] * log1p(exp(logsum[t][k2][n2] / rcount[t][k2][n2]));
            if (W * old - EPS >= F[j].thresh && W * G[j] - EPS < F[j].thresh) {
                frames -= 1;
            }
        }

        // update type-2 interference on other cells
        rep(k2, K) if (k2 != k) rep(n2, N) if (n2 != n && ans.P[t][r][k2][n2] > 0) {
            logsum[t][k2][n2] += log1p(interf2[t][r][k2][n2]);
            interf2[t][r][k2][n2] += S0[t][r][k][n2] * (p - ans.P[t][r][k][n]) * exp(-D[r][k][n][n2]);
            logsum[t][k2][n2] -= log1p(interf2[t][r][k2][n2]);
        }

        if (ans.P[t][r][k][n] > 0) {
            // deactivate this point

            // remove type-1 interference on my cell and other cells
            rep(m, N) if (m != n && ans.P[t][r][k][m] > 0) {
                logsum[t][k][m] -= D[r][k][n][m];
                logsum[t][k][n] -= D[r][k][n][m];
            }

            // remove myself from my cell
            logsum[t][k][n] -= log(S0[t][r][k][n] * ans.P[t][r][k][n] / (1 + interf2[t][r][k][n]));
            rcount[t][k][n] -= 1;
        }

        ans.P[t][r][k][n] = p;

        if (p > 0) {
            // add the value

            // add type-1 interference on my cell and other cells
            rep(m, N) if (m != n && ans.P[t][r][k][m] > 0) {
                logsum[t][k][m] += D[r][k][n][m];
                logsum[t][k][n] += D[r][k][n][m];
            }

            // calculate type-2 interference on myself
            interf2[t][r][k][n] = 0;
            rep(k2, K) if (k2 != k) rep(n2, N) if (n2 != n && ans.P[t][r][k2][n2] > 0) {
                interf2[t][r][k][n] += S0[t][r][k2][n] * ans.P[t][r][k2][n2] * exp(-D[r][k2][n][n2]);
            }

            // add myself to my cell
            logsum[t][k][n] += log(S0[t][r][k][n] * ans.P[t][r][k][n] / (1 + interf2[t][r][k][n]));
            rcount[t][k][n] += 1;
        }

        // re-add all cell score in this band to their frame scores
        rep(k2, K) rep(n2, N) if ((k2 == k && n2 == n) || ans.P[t][r][k2][n2] > 0) {
            int j = frameptr[t][n2];
            float old = G[j];
            if (rcount[t][k2][n2]) G[j] += rcount[t][k2][n2] * log1p(exp(logsum[t][k2][n2] / rcount[t][k2][n2]));
            if (W * old - EPS < F[j].thresh && W * G[j] - EPS >= F[j].thresh) {
                frames += 1;
            }
        }

        // cerr << "after setting t = " << t << ", r = " << r << ", k = " << k << ", n = " << n << " to p = " << p << ", transmitted for the active frame is " << W * G[frameptr[t][n]] << "/" << F[frameptr[t][n]].thresh << " and total score is " << frames << endl;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    // Read input
    cin >> N >> K >> T >> R;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) S0[t][r][k][n] = quickread();
    rep(k, K) rep(r, R) rep(m, N) rep(n, N) D[r][k][m][n] = quickread();
    cin >> J;
    rep(j, J) {
        int _j, s, u, l, d;
        cin >> _j >> s >> u >> l >> d;
        F[j] = {s, u, l, l + d};
    }

    // Test score function
    unique_ptr<ScoreKeep> sf = make_unique<ScoreKeep>();
    rep(tries, 1000) {
        rep(iter, 1000) {
            int j = uniform_int_distribution<int>(0, J - 1)(rng);
            int t = uniform_int_distribution<int>(F[j].l, F[j].r - 1)(rng);
            int r = uniform_int_distribution<int>(0, R - 1)(rng);
            int k = uniform_int_distribution<int>(0, K - 1)(rng);
            float p = uniform_real_distribution<float>()(rng);
            sf->set(t, r, k, F[j].user, p);
        }
        if (score_frames(sf->ans) != sf->frames) {
            cerr << "real: " << score_frames(sf->ans);
            cerr << "online: " << sf->frames;
            throw "not equal!";
        }
    }
    Answer &ans = sf->ans;

    // Print output
    cout << fixed << setprecision(10);
    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << ans.P[t][r][k][n] << " ";
        cout << "\n";
    }

    cerr << "score: " << score(ans) << endl;
    cerr << "sf score: " << sf->frames << endl;
}
