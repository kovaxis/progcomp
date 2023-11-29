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

#define memzero(x) memset(&x, 0, sizeof(x))
#define memfill(x, v) memset(&x, v, sizeof(x))

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

clock_t start_time;

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

void validate(const Answer &ans) {
    // Validate
    rep(t, T) rep(k, K) {
        float ksum = 0;
        rep(r, R) {
            float rsum = 0;
            rep(n, N) {
                if (ans.P[t][r][k][n] < 0) {
                    cerr << "invalid power at t = " << t << ", k = " << k << ", r = " << r << ", n = " << n << ": " << ans.P[t][r][k][n] << endl;
                    throw "invalid";
                }
                rsum += ans.P[t][r][k][n];
            }
            if (rsum > 4) {
                cerr << "invalid power sum at t = " << t << ", k = " << k << ", r = " << r << ": " << rsum << endl;
                throw "invalid";
            }
            ksum += rsum;
        }
        if (ksum > R) {
            cerr << "invalid power sum at t = " << t << ", k = " << k << ": " << ksum << endl;
            throw "invalid";
        }
    }
}

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

    vector<short> missing_frames;
    short missing_frames_rev[5000];
    float bandpower[1000][10][10]; // t, r, k

    short frameptr[1000][100]; // t, n

    // reset the entire scorekeep, including the answer, score and auxiliary data
    void reset() {
        memzero(ans);
        reset_score();
        memzero(frameptr);
        rep(j, J) {
            repx(t, F[j].l, F[j].r) frameptr[t][F[j].user] = j;
        }
    }

    // reset the score, keeping the answer intact
    void reset_score() {
        memzero(interf2);
        memzero(logsum);
        memzero(rcount);
        memzero(G);
        rep(t, 1000) rep(r, 10) active[t][r].clear();
        frames = 0;

        missing_frames.clear();
        rep(j, J) missing_frames.push_back(j);
        rep(j, J) missing_frames_rev[j] = j;
        memzero(bandpower);
    }

    // resync the score from scratch, from the answer
    void resync() {
        reset_score();

        rep(j, J) {
            Frame f = F[j];
            int n = f.user;
            repx(t, f.l, f.r) {
                rep(k, K) {
                    rep(r, R) {
                        if (ans.P[t][r][k][n] != 0) {
                            float interf1 = 0;
                            rep(m, N) if (m != n) {
                                if (ans.P[t][r][k][m] != 0) {
                                    interf1 += D[r][k][n][m];
                                }
                            }

                            rep(k2, K) if (k2 != k) {
                                rep(n2, N) if (n2 != n) {
                                    interf2[t][r][k][n] += S0[t][r][k2][n] * ans.P[t][r][k2][n2] * exp(-D[r][k2][n][n2]);
                                }
                            }

                            logsum[t][k][n] += log(S0[t][r][k][n] * ans.P[t][r][k][n] / (1 + interf2[t][r][k][n])) + interf1;
                            rcount[t][k][n] += 1;
                            active[t][r].push_back({k, n});

                            bandpower[t][r][k] += ans.P[t][r][k][n];
                        }
                    }
                    if (rcount[t][k][f.user] != 0) G[j] += rcount[t][k][n] * log1p(exp(logsum[t][k][n] / rcount[t][k][n]));
                }
            }
            modify_frame_status(j, W * G[j] - EPS >= f.thresh);
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
                int delta = (W * G[j] - EPS >= F[j].thresh);
                G[j] += rcount[t][k2][n2] * (log1p(exp(logsum[t][k2][n2] / rcount[t][k2][n2])) - log1p(exp(old_logsum / rcount[t][k2][n2])));
                delta -= (W * G[j] - EPS >= F[j].thresh);
                modify_frame_status(j, -delta);
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
        int delta = (W * G[j] - EPS >= F[j].thresh);
        if (myold_rcount) G[j] -= myold_rcount * log1p(exp(myold_logsum / myold_rcount));
        if (rcount[t][k][n]) G[j] += rcount[t][k][n] * log1p(exp(logsum[t][k][n] / rcount[t][k][n]));
        delta -= (W * G[j] - EPS >= F[j].thresh);
        modify_frame_status(j, -delta);

        // cerr << "after setting t = " << t << ", r = " << r << ", k = " << k << ", n = " << n << " from p = " << ans.P[t][r][k][n] << " to p = " << p << ", transmitted for the active frame is " << W * G[frameptr[t][n]] << "/" << F[frameptr[t][n]].thresh << " and total score is " << frames << endl;

        // maintain the sum of power in each band
        bandpower[t][r][k] += p - ans.P[t][r][k][n];

        // update the actual P value
        ans.P[t][r][k][n] = p;
    }

    void modify_frame_status(int j, int delta) {
        frames += delta;

        // maintain a list of frames that are not ready
        if (delta < 0) {
            missing_frames_rev[j] = missing_frames.size();
            missing_frames.push_back(j);
        } else if (delta > 0) {
            int idx = missing_frames_rev[j];
            missing_frames_rev[j] = -1;
            swap(missing_frames[idx], missing_frames.back());
            missing_frames_rev[missing_frames[idx]] = idx;
            missing_frames.pop_back();
        }
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
        // assert(ceil(newscore) == tmp->frames);
        if (newscore > curscore) {
            curscore = newscore;
            swap(ans, tmp);
        }
    }
};

void solve_greedy(Answer &ans) {
    vector<pair<int, vector<int>>> time_order(T);
    rep(t, T) time_order[t].first = t;
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) time_order[t].second.push_back(j);
    }

    sort(time_order.begin(), time_order.end(), [](auto &a, auto &b) {
        return a.second.size() < b.second.size();
    });

    vector<float> transmitted(J);
    for (auto [t, js] : time_order) {
        // assign time slot t to frames js

        // assign the R bands in time t in all cells between frames js
        int jcnt = js.size();
        // cerr << "assigning " << jcnt << " users in time " << t << endl;

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
                logsum += log(S0[t][r][k][n]);
                float inc = score() - oldscore;
                return inc;
            }
        };
        vector<vector<UserCell>> user_cell(jcnt, vector<UserCell>(K));
        vector<bool> assigned(R);
        while (true) { // at most R times
            float best_scorewin = 0;
            int best_jj = -1;
            int best_r = -1;
            rep(jj, jcnt) {
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
                    scorewin /= (f.thresh - W * curbits + 0.1); // greedily try to finish frames as quickly as possible
                    // cerr << "  band " << r << " to user " << f.user << " has scorewin " << scorewin << endl;
                    if (scorewin > best_scorewin) {
                        best_scorewin = scorewin;
                        best_jj = jj;
                        best_r = r;
                    }
                }
            }

            // assign band r to frame/user best_jj
            if (best_jj == -1) break;
            // cerr << "  assigning band " << best_r << " to user " << F[js[best_jj]].user << " with scorewin " << best_scorewin << endl;
            int j = js[best_jj];
            Frame f = F[j];
            assigned[best_r] = true;
            rep(k, K) {
                UserCell &uc = user_cell[best_jj][k];
                uc.increase(t, k, best_r, f.user);
                ans.P[t][best_r][k][f.user] = 1;
            }
        }

        // update the transmitted bits for all frames
        rep(jj, jcnt) {
            int j = js[jj];
            rep(k, K) transmitted[j] += user_cell[jj][k].score();
        }
    }
}

void solve_anneal(AnswerStore &out) {
    ScoreKeep &sf = out.temp();

    // start from an interference-free solution
    solve_greedy(sf.ans);
    sf.resync();

    validate(sf.ans);

    vector<vector<int>> pertime(T);
    rep(j, J) repx(t, F[j].l, F[j].r) {
        pertime[t].push_back(j);
    }

    cerr << (start_time + 1.9 * CLOCKS_PER_SEC - clock()) / (double)CLOCKS_PER_SEC << " seconds left" << endl;
    double anneal_start = clock();
    int iters = 0, no_r_src = 0, no_j_src = 0, no_r_dst = 0;
    double accept_prob = 1;
    double inc = -3e-5;
    while (clock() < start_time + 1.8 * CLOCKS_PER_SEC) {
        // rep(_iter, 600000) {
        // choose a random perturbation
        float delta = 1;

        // pick a random destination frame, that needs some bits
        if (sf.missing_frames.empty()) break;
        int j_idx = uniform_int_distribution<int>(0, sf.missing_frames.size() - 1)(rng);
        int j_dst = sf.missing_frames[j_idx];
        // int j_dst = uniform_int_distribution<int>(0, J - 1)(rng);
        int n_dst = F[j_dst].user;

        // pick a random time in its lifetime
        int t = uniform_int_distribution<int>(F[j_dst].l, F[j_dst].r - 1)(rng);

        // pick a random other active frame at this time
        int jj_src = uniform_int_distribution<int>(0, pertime[t].size() - 1)(rng);
        int j_src = pertime[t][jj_src];
        if (false && j_dst == j_src) {
            // TODO: maybe disallow moves between the same user
            no_j_src += 1;
            continue;
        }
        int n_src = F[j_src].user;

        // pick a random k
        int k = uniform_int_distribution<int>(0, K - 1)(rng);

        // pick a random destination r
        int r_dst = uniform_int_distribution<int>(0, R - 1)(rng);
        if (sf.bandpower[t][r_dst][k] + delta > 4) {
            no_r_dst += 1;
            continue;
        }

        // pick a random source r among those with nonzero value
        int r_src_candidates[10];
        int r_src_count = 0;
        rep(r, R) if ((j_src != j_dst || r != r_dst) && sf.ans.P[t][r][k][n_src] != 0) r_src_candidates[r_src_count++] = r;
        if (r_src_count == 0) {
            no_r_src += 1;
            continue;
        }
        int r_src = r_src_candidates[uniform_int_distribution<int>(0, r_src_count - 1)(rng)];

        // cerr << "transferring between t=" << t << ", k=" << k << ", from (r=" << r_src << ",n=" << n_src << ",bandpower=" << sf.bandpower[t][r_src][k] << ") to (r=" << r_dst << ",n=" << n_dst << ",bandpower=" << sf.bandpower[t][r_dst][k] << ")" << endl;

        // transfer power
        int old_score = sf.frames;
        float p_src = sf.ans.P[t][r_src][k][n_src];
        float p_dst = sf.ans.P[t][r_dst][k][n_dst];
        sf.set(t, r_src, k, n_src, p_src - delta);
        sf.set(t, r_dst, k, n_dst, p_dst + delta);
        iters += 1;

        // undo operation if it became worse
        double progress = (clock() - anneal_start) / (1.8 * CLOCKS_PER_SEC);
        accept_prob = 0; // exp(-progress * 30);
        // accept_prob_log += inc;
        if (sf.frames < old_score) {
            if (uniform_real_distribution<float>(0, 1)(rng) > accept_prob) {
                sf.set(t, r_src, k, n_src, p_src);
                sf.set(t, r_dst, k, n_dst, p_dst);
            }
        } else if (sf.frames > old_score) {
            cerr << "got to score " << sf.frames << " with accept_prob = " << accept_prob << endl;
        }
    }

    cerr << iters << " iterations" << endl;
    cerr << no_r_src << " no_r_src iterations" << endl;
    cerr << no_j_src << " no_j_src iterations" << endl;
    cerr << no_r_dst << " no_r_dst iterations" << endl;

    out.update();
}

int main() {
    start_time = clock();
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
    /*
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
        sf->resync();
    }
    Answer &ans = sf->ans;
    // */

    // Optimize
    //*
    AnswerStore out;
    solve_anneal(out);
    Answer &ans = out.answer();
    // validate(ans);
    // */

    // Print output
    cout << fixed << setprecision(10);
    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << ans.P[t][r][k][n] << " ";
        cout << "\n";
    }

    cerr << "score: " << score(ans) << endl;
}
