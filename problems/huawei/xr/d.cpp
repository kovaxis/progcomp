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

static mt19937 rng(7641206241ll);
// static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
    float interf2[1000][10][10][100];              // t, r, k, n
    float logsum[1000][10][100];                   // t, k, n
    int8_t rcount[1000][10][100];                  // t, k, n
    float G[5000];                                 // j
    vector<pair<int8_t, int8_t>> active[1000][10]; // t, r -> k, n
    int frames;

    short frameptr[1000][100]; // t, n

    void reset() {
        memset(&ans, 0, sizeof(ans));
        memset(&interf2, 0, sizeof(interf2));
        memset(&logsum, 0, sizeof(logsum));
        memset(&rcount, 0, sizeof(rcount));
        memset(&G, 0, sizeof(G));
        rep(t, 1000) rep(r, 10) active[t][r].clear();
        frames = 0;
        memset(&frameptr, -1, sizeof(frameptr));
        rep(j, J) {
            repx(t, F[j].l, F[j].r) frameptr[t][F[j].user] = j;
        }
    }

    void set(int t, int r, int k, int n, float p) {
        if (ans.P[t][r][k][n] == p) return;

        float myold_logsum = logsum[t][k][n];
        int myold_rcount = rcount[t][k][n];

        // update type-1 and type-2 interference
        for (auto [k2, n2] : active[t][r])
            if (n2 != n) {
                float old_logsum = logsum[t][k2][n2];
                if (k2 == k) {
                    // type-1 interference
                    if (p == 0) {
                        // remove type-1 interference from my point and the other
                        logsum[t][k2][n2] -= D[r][k][n][n2];
                        logsum[t][k][n] -= D[r][k][n][n2];
                    } else if (ans.P[t][r][k][n] == 0) {
                        // add type-1 interference from my point and the other
                        logsum[t][k2][n2] += D[r][k][n][n2];
                        logsum[t][k][n] += D[r][k][n][n2];
                    }
                } else {
                    // update type-2 interference on other cells
                    logsum[t][k2][n2] += log1p(interf2[t][r][k2][n2]);
                    interf2[t][r][k2][n2] += S0[t][r][k][n2] * (p - ans.P[t][r][k][n]) * exp(-D[r][k][n][n2]);
                    logsum[t][k2][n2] -= log1p(interf2[t][r][k2][n2]);
                }

                // update the frame scores
                int j = frameptr[t][n2];
                bool ok_old = (W * G[j] - EPS >= F[j].thresh);
                G[j] += rcount[t][k2][n2] * (log1p(exp(logsum[t][k2][n2] / rcount[t][k2][n2])) - log1p(exp(old_logsum / rcount[t][k2][n2])));
                bool ok_new = (W * G[j] - EPS >= F[j].thresh);
                frames += int(ok_new) - int(ok_old);
            }

        if (p == 0) {
            // deactivate this point

            // remove myself from my cell
            logsum[t][k][n] -= log(S0[t][r][k][n] * ans.P[t][r][k][n] / (1 + interf2[t][r][k][n]));
            rcount[t][k][n] -= 1;

            // mark as inactive
            rep(u, active[t][r].size()) if (active[t][r][u] == make_pair((int8_t)k, (int8_t)n)) {
                swap(active[t][r][u], active[t][r].back());
                active[t][r].pop_back();
                break;
            }
        } else if (ans.P[t][r][k][n] == 0) {
            // activate this point

            // calculate type-2 interference on myself
            interf2[t][r][k][n] = 0;
            for (auto [k2, n2] : active[t][r])
                if (k2 != k && n2 != n) {
                    interf2[t][r][k][n] += S0[t][r][k2][n] * ans.P[t][r][k2][n2] * exp(-D[r][k2][n][n2]);
                }

            // add myself to my cell
            logsum[t][k][n] += log(S0[t][r][k][n] * p / (1 + interf2[t][r][k][n]));
            rcount[t][k][n] += 1;

            // mark as active
            active[t][r].push_back({k, n});
        } else {
            // just update my cell score
            logsum[t][k][n] += log(p / ans.P[t][r][k][n]);
        }

        // update my frame score
        int j = frameptr[t][n];
        bool ok_old = (W * G[j] - EPS >= F[j].thresh);
        if (myold_rcount) G[j] -= myold_rcount * log1p(exp(myold_logsum / myold_rcount));
        if (rcount[t][k][n]) G[j] += rcount[t][k][n] * log1p(exp(logsum[t][k][n] / rcount[t][k][n]));
        bool ok_new = (W * G[j] - EPS >= F[j].thresh);
        frames += int(ok_new) - int(ok_old);

        // cerr << "after setting t = " << t << ", r = " << r << ", k = " << k << ", n = " << n << " from p = " << ans.P[t][r][k][n] << " to p = " << p << ", transmitted for the active frame is " << W * G[frameptr[t][n]] << "/" << F[frameptr[t][n]].thresh << " and total score is " << frames << endl;

        // update the actual P value
        ans.P[t][r][k][n] = p;
    }
};

struct AnswerStore {
    unique_ptr<ScoreKeep> ans = make_unique<ScoreKeep>(), tmp = make_unique<ScoreKeep>();
    float curscore = 0;

    ScoreKeep &temp() {
        tmp->reset();
        return *tmp;
    }

    Answer &answer() {
        return ans->ans;
    }

    void update() {
        float newscore = score(tmp->ans);
        assert(ceil(newscore) == tmp->frames);
        if (newscore > curscore) {
            curscore = newscore;
            swap(ans, tmp);
        }
    }
};

void solve(AnswerStore &out) {
    ScoreKeep &sf = out.temp();

    out.update();
}

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
    sf->reset();
    rep(tries, 1000) {
        rep(iter, 1000) {
            int j = uniform_int_distribution<int>(0, J - 1)(rng);
            int t = uniform_int_distribution<int>(F[j].l, F[j].r - 1)(rng);
            int r = uniform_int_distribution<int>(0, R - 1)(rng);
            int k = uniform_int_distribution<int>(0, K - 1)(rng);
            float p = uniform_real_distribution<float>()(rng);
            if (uniform_int_distribution<int>(1, 100)(rng) <= 5) p = 0;
            sf->set(t, r, k, F[j].user, p);
        }
        if (score_frames(sf->ans) != sf->frames) {
            cerr << "real: " << score_frames(sf->ans) << endl;
            cerr << "online: " << sf->frames << endl;
            throw "not equal!";
        }
    }
    Answer &ans = sf->ans;

    // Optimize
    /*
    AnswerStore out;
    solve(out);
    Answer &ans = out.answer();
    */

    // Print output
    cout << fixed << setprecision(10);
    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << ans.P[t][r][k][n] << " ";
        cout << "\n";
    }

    cerr << "score: " << score(ans) << endl;
}
