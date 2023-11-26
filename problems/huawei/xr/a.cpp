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

static mt19937 rng(7641206241ll);

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

                logsum += log(S0[t][k][r][f.user] * ans.P[t][k][r][f.user] / (1 + interf2)) + interf1;
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

struct AnswerStore {
    unique_ptr<Answer> ans = make_unique<Answer>(), tmp = make_unique<Answer>();
    float curscore = 0;

    Answer &temp() {
        memset(&*tmp, 0, sizeof(*tmp));
        return *tmp;
    }

    void update() {
        float newscore = score(*tmp);
        if (newscore > curscore) {
            curscore = newscore;
            swap(ans, tmp);
        }
    }
};

float score_without_interference(const Answer &ans, int t, int k, int n) {
    int bands = 0;
    float product = 1;
    rep(r, R) if (ans.P[t][k][r][n] > 0) {
        bands += 1;
        product *= S0[t][k][r][n] * ans.P[t][k][r][n];
    }
    return bands * log1p(powf(product, 1.0f / bands));
}

void solve_naive(AnswerStore &out) {
    Answer &ans = out.temp();

    vector<bool> used(T);
    rep(j, J) {
        Frame f = F[j];
        float transmitted = 0;
        repx(t, f.l, f.r) {
            if (W * transmitted >= f.thresh) break;
            if (used[t]) continue;
            used[t] = true;
            rep(r, R) {
                rep(k, K) {
                    ans.P[t][k][r][f.user] = 1;
                }
            }
            rep(k, K) {
                transmitted += score_without_interference(ans, t, k, f.user);
            }
            // cerr << "frame " << j << " transmitted " << W * transmitted << "/" << f.thresh << " at time interval [" << f.l << ", " << t << "]" << endl;
        }
    }

    out.update();
}

void solve_tiecells(AnswerStore &out) {
    Answer &ans = out.temp();

    vector<vector<int>> pertime(T);
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) pertime[t].push_back(j);
    }

    vector<pair<int, int>> ordered(T);
    rep(t, T) {
        ordered[t].first = pertime[t].size();
        ordered[t].second = t;
    }
    sort(ordered.begin(), ordered.end());

    vector<float> transmitted(J);
    for (auto [_s, t] : ordered) {
        // assign time slot t to frames js
        vector<int> &js = pertime[t];

        // assign the R bands in time t in all cells between frames js

        // first, let each user rank the bands
        vector<vector<pair<float, int>>> bands_per_user;
        for (int j : js) {
            // rank the bands for user n
            Frame f = F[j];
            int n = f.user;

            vector<pair<float, int>> bands(R);
            rep(r, R) {
                float rank = 1;
                rep(k, K) rank *= S0[t][k][r][n];
                bands[r] = {-rank, r}; // TODO: try other heuristics
            }
            sort(bands.begin(), bands.end());
            bands_per_user.push_back(bands);
        }

        // now, alternate between users to assign the bands
        vector<bool> assigned(R, false);
        rep(_iter, R) {
            rep(jj, js.size()) {
                int j = js[jj];
                Frame f = F[j];
                int n = f.user;
                if (W * transmitted[j] >= f.thresh) continue;
                vector<pair<float, int>> &bands = bands_per_user[jj];

                // assign a band to this user/frame
                for (auto [_, r] : bands)
                    if (!assigned[r]) {
                        // assign all cells of r to user n
                        rep(k, K) ans.P[t][k][r][n] = 1;

                        assigned[r] = true;
                        break;
                    }
            }
        }
        for (int j : js) {
            Frame f = F[j];

            // count how many bits were transmitted
            rep(k, K) {
                transmitted[j] += score_without_interference(ans, t, k, f.user);
            }
        }
    }

    out.update();
}

void solve_tiecells_fine(AnswerStore &out) {
    Answer &ans = out.temp();

    vector<vector<int>> pertime(T);
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) pertime[t].push_back(j);
    }

    vector<pair<int, int>> ordered(T);
    rep(t, T) {
        ordered[t].first = pertime[t].size();
        ordered[t].second = t;
    }
    sort(ordered.begin(), ordered.end());

    vector<float> transmitted(J);
    for (auto [_s, t] : ordered) {
        // assign time slot t to frames js
        vector<int> &js = pertime[t];

        // assign the R bands in time t in all cells between frames js
        cerr << "assigning " << js.size() << " users in time " << t << endl;

        // greedily assign the band that maximizes the score win
        struct UserCell {
            int bands = 0;
            float logsum = 0;

            float score() const {
                if (bands == 0) return 0;
                return bands * log1p(exp(logsum / bands));
            }

            float increase(int t, int k, int r, int n) {
                float oldscore = score();
                int oldbands = bands;
                float oldlogsum = logsum;
                bands += 1;
                logsum += log(S0[t][k][r][n]);
                float inc = score() - oldscore;
                if (inc > 0) {
                    return inc;
                } else {
                    cerr << "oldscore = " << oldscore << ", newscore = " << score() << endl;
                    bands = oldbands;
                    logsum = oldlogsum;
                    return 0;
                }
            }
        };
        vector<vector<UserCell>> user_cell(js.size(), vector<UserCell>(K));
        vector<bool> assigned(R);
        while (true) { // at most R times
            float best_scorewin = 0;
            int best_jj = -1;
            int best_r = -1;
            rep(jj, js.size()) {
                int j = js[jj];
                Frame f = F[j];

                // determine the current score of the frame, in order to stop allocating bands if ready
                float curbits = transmitted[j];
                rep(k, K) curbits += user_cell[jj][k].score();
                if (W * curbits > f.thresh) continue;

                rep(r, R) if (!assigned[r]) {
                    // determine the score win of assigning band r to user f.user
                    float scorewin = 0;
                    rep(k, K) {
                        UserCell &uc = user_cell[jj][k];
                        UserCell nuc = uc;
                        scorewin += nuc.increase(t, k, r, f.user);
                    }
                    cerr << "  band " << r << " to user " << f.user << " has scorewin " << scorewin << endl;
                    if (scorewin > best_scorewin) {
                        best_scorewin = scorewin;
                        best_jj = jj;
                        best_r = r;
                    }
                }
            }

            // assign band r to frame/user best_jj
            if (best_jj == -1) break;
            cerr << "  assigning band " << best_r << " to user " << F[js[best_jj]].user << " with scorewin " << best_scorewin << endl;
            int j = js[best_jj];
            Frame f = F[j];
            assigned[best_r] = true;
            rep(k, K) {
                UserCell &uc = user_cell[best_jj][k];
                if (uc.increase(t, k, best_r, f.user) > 0) {
                    ans.P[t][k][best_r][f.user] = 1;
                }
            }
        }

        // update the transmitted bits for all frames
        rep(jj, js.size()) {
            int j = js[jj];
            rep(k, K) transmitted[j] += user_cell[jj][k].score();
        }
    }

    out.update();
}

void solve_percell(AnswerStore &out, float alpha) {
    Answer &ans = out.temp();

    vector<vector<int>> pertime(T);
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) pertime[t].push_back(j);
    }

    vector<pair<int, int>> ordered(T);
    rep(t, T) {
        ordered[t].first = pertime[t].size();
        ordered[t].second = t;
    }
    sort(ordered.begin(), ordered.end());

    vector<float> transmitted(J);
    for (auto [_s, t] : ordered) {
        // assign time slot t to frames js
        vector<int> &js = pertime[t];

        // assign each cell independently, and then factor in type 2 interference
        rep(k, K) {
            // first, let each user rank the bands
            vector<vector<pair<float, int>>> bands_per_user;
            for (int j : js) {
                // rank the bands for user n
                Frame f = F[j];
                int n = f.user;

                vector<pair<float, int>> bands(R);
                rep(r, R) {
                    bands[r] = {-S0[t][k][r][n], r};
                }
                sort(bands.begin(), bands.end());
                bands_per_user.push_back(bands);
            }

            // now, alternate between users to assign the bands
            vector<bool> assigned(R, false);
            vector<int> rcount_per_user(js.size());
            vector<float> logsum_per_user(js.size());
            rep(_iter, R) {
                rep(jj, js.size()) {
                    int j = js[jj];
                    Frame f = F[j];
                    int n = f.user;
                    int &rcount = rcount_per_user[jj];
                    float &logsum = logsum_per_user[jj];
                    float old_score = rcount ? rcount * log1p(exp(logsum / rcount)) : 0;
                    if (alpha * W * (transmitted[j] + old_score) >= f.thresh) continue; // TODO: consider interference
                    vector<pair<float, int>> &bands = bands_per_user[jj];

                    // assign a band to this user/frame
                    for (auto [_, r] : bands)
                        if (!assigned[r]) {
                            // check what would be the new score be
                            int new_rcount = rcount + 1;
                            float new_logsum = logsum + log(S0[t][k][r][n]);
                            float new_score = new_rcount * log1p(exp(new_logsum / new_rcount));
                            if (new_score > old_score) {
                                // keep it
                                ans.P[t][k][r][n] = 1;
                                assigned[r] = true;

                                rcount = new_rcount;
                                logsum = new_logsum;
                                break;
                            }
                        }
                }
            }
            for (int j : js) {
                Frame f = F[j];

                // count how many bits were transmitted
                transmitted[j] += alpha * score_without_interference(ans, t, k, f.user);
            }
        }
    }

    out.update();
}

void metasolve_with_beta(float beta, AnswerStore &out) {
    // Limit to `beta` times the frames
    int realJ = J;
    J = beta * J;

    // Try different solutions
    solve_percell(out, 0.51);
    // solve_tiecells(out); // better only in very few cases
    solve_tiecells_fine(out);

    J = realJ;
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

    AnswerStore out;

    // Solve once, shuffled
    shuffle(&F[0], &F[J], rng);
    metasolve_with_beta(1, out);

    // Sort by frame threshold
    sort(&F[0], &F[J], [](Frame &a, Frame &b) {
        return a.thresh < b.thresh;
    });

    // Solve sorted
    metasolve_with_beta(1, out);
    metasolve_with_beta(0.93, out);
    Answer &ans = *out.ans;

    // Print output
    cout << fixed << setprecision(10);
    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << ans.P[t][k][r][n] << " ";
        cout << "\n";
    }

    cerr << "score: " << score(ans) << endl;
}
