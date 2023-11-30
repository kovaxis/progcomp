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

double env_float(const char *name, double df) {
    char *s = getenv(name);
    if (!s) return df;
    return atof(s);
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

vector<pair<int, vector<int>>> time_order;

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

// go frame by frame, assigning entire timeslots to frames.
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

// visit timeslots from the least crowded to most crowded, letting each user rank all bands and then distributing the bands according to these rankings
// almost-superseeded by solve_tiecells_fine
void solve_tiecells(AnswerStore &out) {
    Answer &ans = out.temp();

    vector<float> transmitted(J);
    for (auto [t, js] : time_order) {
        // assign time slot t to frames js

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

// visit timeslots from least crowded to most crowded
// fully avoid interference (one user per band)
// maintain score, and greedily assign bands to whichever user maximizes score win
void solve_tiecells_fine(AnswerStore &out) {
    Answer &ans = out.temp();

    vector<float> transmitted(J);
    for (auto [t, js] : time_order) {
        // assign time slot t to frames js

        // assign the R bands in time t in all cells between frames js
        int jcnt = js.size();
        cerr << "assigning " << jcnt << " users in time " << t << endl;

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
        rep(jj, jcnt) {
            int j = js[jj];
            rep(k, K) transmitted[j] += user_cell[jj][k].score();
        }
    }

    out.update();
}

// visit timeslots from least crowded to most crowded
// assign at most 2 users per band
void solve_interference(AnswerStore &out) {
    Answer &ans = out.temp();

    // interference values are approximated, therefore the solver cannot shoot at the exact number of bits for each frame
    // however, we have a worst-case upper bound on the amount that the approximation can be off: by e^(-Dmin) bits per cell
    // anyway, its best to use an empirically best value
    // TODO: for each t-r-k we can know exactly what is the minimum D-value, but T*R*K*N^2 time is too slow (?)
    float approx_d = env_float("APPROX_D", 7.4);

    // bonus associated with completing a frame in a band
    float completion_bonus = env_float("COMPLETION_BONUS", 4);

    // determine the pairs of users with low interference
    vector<vector<vector<float>>> interf_score(R, vector<vector<float>>(N, vector<float>(N)));
    rep(r, R) rep(n1, N) rep(n2, N) {
        rep(k, K) interf_score[r][n1][n2] += D[k][r][n1][n2];
    }

    vector<float> transmitted(J);
    for (auto [t, js] : time_order) {
        // assign time slot t to frames js

        // assign the R bands in time t in all cells between frames js
        int jcnt = js.size();
        if (jcnt == 0) continue;
        cerr << "assigning " << jcnt << " users in time " << t << endl;

        // keep track of partial scores
        static float logsum[10][100];
        static int rcount[10][100];
        static float partialscore[100];
        rep(k, K) rep(jj, jcnt) logsum[k][jj] = 0;
        rep(k, K) rep(jj, jcnt) rcount[k][jj] = 0;
        rep(jj, jcnt) partialscore[jj] = 0;

        // go band by band assigning frames
        rep(r, R) {
            cerr << "  assigning band " << r << endl;
            // assign the best frames in every cell
            /*int cell_user[10];
            rep(k, K) {
                float best = 0;
                int best_jj = -1;
                rep(jj, jcnt) {
                    Frame f = F[js[jj]];

                    // check if the frame is done already
                    float bits = transmitted[js[jj]] + partialscore[jj];
                    if (W * bits > f.thresh) continue;

                    if (S0[t][k][r][f.user] > best) {
                        best = S0[t][k][r][f.user];
                        best_jj = jj;
                    }
                }
                cell_user[k] = best_jj;
            }*/

            // we want to assign the cells in this band to different users, maximizing the amount of score won
            // in order to do this, for each user we will consider all partitions of cells into two sets, the upper half and the lower half (divided by value of S0)
            // we will then choose upper halfs from all users such that the sum of scores is maximized

            // store the different score wins for each assignment of users to cells
            static float edge_score[1024];
            static int edge_jj[1024];
            rep(m, (1 << K)) {
                edge_score[m] = 0;
                edge_jj[m] = -1;
            }

            // consider all good assignments of users to cells
            rep(jj, jcnt) {
                Frame f = F[js[jj]];

                // get how many bits is this frame missing
                float bits = transmitted[js[jj]] + partialscore[jj];
                float missing_bits = max(f.thresh / W - bits + 1e-5f, 0.0f);
                if (missing_bits == 0) continue;

                // cerr << "    user " << js[jj] << " is missing " << missing_bits << " bits" << endl;

                // sort the cells by goodness for this user
                int ordered_cells[10];
                rep(k, K) ordered_cells[k] = k;
                sort(&ordered_cells[0], &ordered_cells[K], [&](int k1, int k2) {
                    return S0[t][k1][r][f.user] > S0[t][k2][r][f.user];
                });

                // consider all partitions of cells into taken and not taken
                int mask = 0;
                float base_scoredif = 0;
                rep(kk, K) {
                    // consider assigning the kk+1 best cells to this user, and the K-kk worst cells to other users
                    int k = ordered_cells[kk];

                    // precompute the sum of the K-kk worst cells
                    float rest = 0;
                    repx(kk2, kk + 1, K) rest += S0[t][ordered_cells[kk2]][r][f.user] * approx_d;

                    // include all previous base cell scores (see line tagged with `unnecessary`)
                    if (rcount[k][jj]) base_scoredif -= rcount[k][jj] * log1p(exp(logsum[k][jj] / rcount[k][jj]));

                    // approximate the change in score we would get by assigning the kk+1 best cells to this user
                    // note that the K-kk worst cells will be assigned to other users (we dont know which)
                    // approximate the interference with these other users by ignoring the e^(-D) term
                    // TODO: use an average e^(-D) term instead of fully ignoring it
                    float bitdif = base_scoredif;
                    rep(kk2, kk + 1) {
                        int k2 = ordered_cells[kk2];
                        float newlogsum = logsum[k2][jj] + log(S0[t][k2][r][f.user] / (1 + rest));
                        int newrcount = rcount[k2][jj] + 1;
                        bitdif += newrcount * log1p(exp(newlogsum / newrcount));
                        // unnecessary: this is handled by `base_scoredif`
                        // scoredif -= rcount[k2][jj] * log1p(exp(logsum[k2][jj] / rcount[k2][jj]));
                    }

                    // assigning more power than strictly necessary is useless
                    float scoredif = min(bitdif, missing_bits) / (f.thresh / W);
                    if (scoredif >= 1) scoredif = completion_bonus;
                    // scoredif = min(scoredif, estimated_missing_bits) / estimated_missing_bits;

                    // this mask has a bit set for each cell of the kk+1 best cells
                    mask |= (1 << k);

                    // cerr << "    assigning user " << js[jj] << " to cells " << mask << " has bitwin " << bitdif << ": scorewin " << scoredif << endl;

                    // for each mask, keep the best scoredif and the user associated with it
                    if (scoredif > edge_score[mask]) {
                        edge_score[mask] = scoredif;
                        edge_jj[mask] = jj;
                    }
                }
            }

            // bottom-up dp: for each bitmask (representing a set of cells), calculate the best sum of scoredifs that we can get
            // in order to do this, consider from each bitmask removing a set of cells (using entries in `edge`)
            static float dp[1024];
            static int dp_parent[1024];
            rep(m, (1 << K)) dp[m] = 0, dp_parent[m] = 0;
            rep(m, (1 << K)) {
                for (int edge = m; edge != 0; edge = (edge - 1) & m) {
                    float newscore = dp[m ^ edge] + edge_score[edge];
                    if (newscore > dp[m]) dp[m] = newscore, dp_parent[m] = edge;
                }
            }

            // determine to which user does each cell go
            int cell_user[10];
            rep(k, K) cell_user[k] = -1;
            int mask = (1 << K) - 1;
            // cerr << "    checking assignment from dp:" << endl;
            while (true) {
                int edge = dp_parent[mask];
                int jj = edge_jj[edge];
                if (jj == -1) break;
                // cerr << "    assigning block with scoredif " << edge_score[edge] << endl;
                rep(k, K) if ((edge >> k) & 1) {
                    // cerr << "    assigned cell " << k << " to user " << js[jj] << endl;
                    cell_user[k] = jj;
                }
                mask ^= edge;
            }

            // update answer and partial scores
            rep(k, K) {
                int jj = cell_user[k];
                if (jj == -1) continue;
                Frame f = F[js[jj]];
                ans.P[t][k][r][f.user] = 1;

                float interf2 = 0;
                rep(k2, K) if (k2 != k && cell_user[k2] != -1) {
                    int n2 = F[js[cell_user[k2]]].user;
                    if (n2 != f.user) interf2 += S0[t][k2][r][n2] * exp(-D[k2][r][f.user][n2]);
                }
                float s = log(S0[t][k][r][f.user] / (1 + interf2));
                logsum[k][jj] += s;
                rcount[k][jj] += 1;
            }

            // update the partial score for each frame
            rep(jj, jcnt) {
                partialscore[jj] = 0;
                rep(k, K) partialscore[jj] += rcount[k][jj] ? rcount[k][jj] * log1p(exp(logsum[k][jj] / rcount[k][jj])) : 0;
                if (partialscore[jj] != 0) {
                    cerr << "    frame " << js[jj] << " is now at " << W * (transmitted[js[jj]] + partialscore[jj]) << "/" << F[js[jj]].thresh << " bits" << endl;
                }
            }
        }

        // update the overall transmitted bits for all frames
        rep(jj, jcnt) {
            transmitted[js[jj]] += partialscore[jj];
        }
    }

    out.update();
}

// visit timeslots from least crowded to most crowded
// assign each cell independently
// within each cell, let each user rank the bands and then distribute the bands
// no type 1 interference occurs, but type 2 interference occurs and is ignored
// to compensate, the effect of interference is approximated as constant, with parameter alpha indicating how much the score decreases
void solve_percell(AnswerStore &out, float alpha) {
    Answer &ans = out.temp();

    vector<float> transmitted(J);
    for (auto [t, js] : time_order) {
        // assign time slot t to frames js

        // assign each cell independently, and never factor in type 2 interference
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

float monopolize_timeslot(Answer *ans, int t, int j) {
    float transmitted = 0;
    Frame f = F[j];
    rep(k, K) {
        // sort bands from best to worst
        vector<pair<float, int>> bands(R);
        rep(r, R) {
            bands[r] = {-S0[t][k][r][f.user], r};
        }
        sort(bands.begin(), bands.end());

        // assign bands until the score stops improving
        float logsum = 0;
        int rcount = 0;
        float score = 0;
        for (auto [_, r] : bands) {
            float newlogsum = logsum + log(S0[t][k][r][f.user]);
            int newrcount = rcount + 1;
            float newscore = newrcount * log1p(exp(newlogsum / newrcount));
            if (newscore > score) {
                logsum = newlogsum;
                rcount = newrcount;
                score = newscore;
                if (ans) ans->P[t][k][r][f.user] = 1;
            }
        }

        // if there is leftover power, use it
        if (rcount > 0) {
            float adj_p = max(1.0f, min(4.0f, R / rcount - 1e-8f));
            score += log(adj_p);
            if (ans) {
                rep(r, R) {
                    if (ans->P[t][k][r][f.user] != 0) {
                        ans->P[t][k][r][f.user] = adj_p;
                    }
                }
            }
        }

        // this cell contributes `score` bits
        transmitted += score;
    }
    return transmitted;
}

void time_order_heuristic() {
    vector<pair<float, pair<int, int>>> assignments;
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) {
            // figure out the best score we can get out of this timeslot
            float score = monopolize_timeslot(NULL, t, j);
            assignments.push_back({-score, {j, t}});
        }
    }
    sort(assignments.begin(), assignments.end());

    vector<bool> assigned(T);
    vector<float> transmitted(J);
    time_order.clear();
    time_order.reserve(T);
    for (auto [_, jt] : assignments) {
        auto [j, t] = jt;
        if (assigned[t]) continue;
        if (W * transmitted[j] > F[j].thresh) continue;
        assigned[t] = true;
        time_order.push_back({t, {}});

        transmitted[j] += monopolize_timeslot(NULL, t, j);
    }

    vector<vector<int>> pertime(T);
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) {
            pertime[t].push_back(j);
        }
    }

    for (auto &[t, js] : time_order) {
        swap(pertime[t], js);

        sort(js.begin(), js.end(), [](int a, int b) {
            return F[a].thresh < F[b].thresh;
        });
    }
}

void time_order_counts() {
    time_order.assign(T, {0, {}});
    rep(t, T) time_order[t].first = t;
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) time_order[t].second.push_back(j);
    }

    sort(time_order.begin(), time_order.end(), [](auto &a, auto &b) {
        return a.second.size() < b.second.size();
    });
}

// call the other solve functions, giving up on the most costly frames
// gives up on the (1 - beta) fraction of most costly frames
void metasolve_with_beta(float beta, AnswerStore &out) {
    // Limit to `beta` times the frames
    int realJ = J;
    J = beta * J;

    // Figure out order
    // time_order_heuristic();
    time_order_counts();

    // Try different solutions
    solve_percell(out, 0.51);
    // solve_tiecells(out); // better only in very few cases
    // solve_tiecells_fine(out);
    solve_interference(out);

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
