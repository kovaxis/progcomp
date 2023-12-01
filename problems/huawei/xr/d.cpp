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

double env_float(const char *name, double df) {
    char *s = getenv(name);
    if (!s) return df;
    return atof(s);
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

vector<int> pertime[1000]; // t -> j

struct SubAnswer {
    float P[10][10][100]; // r, k, n

    SubAnswer() {
        reset();
    }

    void reset() {
        memzero(P);
    }
};

struct Answer {
    float P[1000][10][10][100]; // t, r, k, n

    Answer() {
        memzero(P);
    }

    SubAnswer &sub(int t) {
        return *(SubAnswer *)&P[t];
    }
    const SubAnswer &sub(int t) const {
        return *(SubAnswer *)&P[t];
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

float score_bits(int j, int t, const SubAnswer &ans) {
    float transmitted = 0;
    Frame f = F[j];
    rep(k, K) {
        int bands = 0;
        float logsum = 0;
        rep(r, R) {
            if (ans.P[r][k][f.user] > 0) {
                float interf1 = 0;
                rep(m, N) if (m != f.user) {
                    if (ans.P[r][k][m] > 0) {
                        interf1 += D[r][k][f.user][m];
                    }
                }

                float interf2 = 0;
                rep(k2, K) if (k2 != k) {
                    rep(n2, N) if (n2 != f.user) {
                        interf2 += S0[t][r][k2][f.user] * ans.P[r][k2][n2] * exp(-D[r][k2][f.user][n2]);
                    }
                }

                logsum += log(S0[t][r][k][f.user] * ans.P[r][k][f.user] / (1 + interf2)) + interf1;
                bands += 1;
            }
        }
        if (bands != 0) transmitted += bands * log1p(exp(logsum / bands));
    }
    return transmitted;
}

struct AnswerPerTime {
    Answer *ans;
    vector<float> transmitted, partial;
    int t;
    int cur_frames;
    float cur_bitsum;
    unique_ptr<SubAnswer> tmp = make_unique<SubAnswer>();

    AnswerPerTime(Answer *ans) : ans(ans), transmitted(J), partial(J) {}

    void begin_time(int t) {
        this->t = t;
        partial.assign(pertime[t].size(), 0);
        cur_frames = 0;
        cur_bitsum = 0;
    }

    void end_time() {
        rep(jj, pertime[t].size()) {
            transmitted[pertime[t][jj]] += partial[jj];
        }
    }

    SubAnswer &temp() {
        tmp->reset();
        return *tmp;
    }

    void update() {
        vector<float> thispartial(pertime[t].size());
        int frames = 0;
        float bitsum = 0;
        rep(jj, pertime[t].size()) {
            int j = pertime[t][jj];
            float bits = score_bits(j, t, *tmp);
            thispartial[jj] = bits;
            frames += (W * (transmitted[j] + bits) >= F[j].thresh);
            bitsum += max(min(bits, F[j].thresh / W - transmitted[j]), 0.0f);
        }
        if (frames > cur_frames || (frames == cur_frames && bitsum > cur_bitsum)) {
            ans->sub(t) = *tmp;
            partial = thispartial;
            cur_frames = frames;
            cur_bitsum = bitsum;
        }
    }
};

int score_frames(const Answer &ans) {
    int frames = 0;
    rep(j, J) {
        Frame f = F[j];
        float transmitted = 0;
        repx(t, f.l, f.r) {
            transmitted += score_bits(j, t, ans.sub(t));
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

template <class T>
struct UnorderedSet {
    T M;
    vector<T> values, indices;

    UnorderedSet() : M(0) {}
    UnorderedSet(int M) : M(M), indices(M, -1) {}

    void reset(int m) {
        M = m;
        indices.assign(M, -1);
        values.clear();
    }

    void add(int x) {
        if (indices[x] != -1) return;
        indices[x] = values.size();
        values.push_back(x);
    }

    void remove(int x) {
        if (indices[x] == -1) return;
        T idx = indices[x];
        swap(values[idx], values.back());
        values.pop_back();
        indices[values[idx]] = idx;
        indices[x] = -1;
    }
};

template <class T>
struct SlowSet {
    vector<T> values;

    void clear() {
        values.clear();
    }

    // add a value, assuming it is not already in the set
    void forceadd(T x) {
        values.push_back(x);
    }

    void remove(T x) {
        rep(i, int(values.size())) if (values[i] == x) {
            swap(values[i], values.back());
            values.pop_back();
            break;
        }
    }
};

struct ScoreKeep {
    Answer ans;
    float interf2[1000][10][10][100];              // t, r, k, n
    float logsum[1000][10][100];                   // t, k, n
    int8_t rcount[1000][10][100];                  // t, k, n
    float G[5000];                                 // j
    vector<pair<int8_t, int8_t>> active[1000][10]; // t, r -> k, n
    int frames;

    UnorderedSet<short> missing_frames;
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

        missing_frames.reset(J);
        rep(j, J) missing_frames.add(j);
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
            missing_frames.add(j);
        } else if (delta > 0) {
            missing_frames.remove(j);
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

void solve_greedy(AnswerPerTime &anspt) {
    int t = anspt.t;
    const vector<int> &js = pertime[t];
    SubAnswer &ans = anspt.temp();

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
            float curbits = anspt.transmitted[j];
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
            ans.P[best_r][k][f.user] = 1;
        }
    }

    anspt.update();
}

// visit timeslots from least crowded to most crowded
void solve_dp(AnswerPerTime &anspt) {
    int t = anspt.t;
    const vector<int> &js = pertime[t];
    SubAnswer &ans = anspt.temp();

    // interference values are approximated, therefore the solver cannot shoot at the exact number of bits for each frame
    // however, we have a worst-case upper bound on the amount that the approximation can be off: by e^(-Dmin) bits per cell
    // anyway, its best to use an empirically best value
    // TODO: for each t-r-k we can know exactly what is the minimum D-value, but T*R*K*N^2 time is too slow (?)
    float approx_d = env_float("APPROX_D", 7.4);

    // bonus associated with completing a frame in a band
    float completion_bonus = env_float("COMPLETION_BONUS", 4);

    // assign time slot t to frames js

    // assign the R bands in time t in all cells between frames js
    int jcnt = js.size();
    if (jcnt == 0) return;
    // cerr << "assigning " << jcnt << " users in time " << t << endl;

    // keep track of partial scores
    static float logsum[10][100];
    static int rcount[10][100];
    static float partialscore[100];
    rep(k, K) rep(jj, jcnt) logsum[k][jj] = 0;
    rep(k, K) rep(jj, jcnt) rcount[k][jj] = 0;
    rep(jj, jcnt) partialscore[jj] = 0;

    // go band by band assigning frames
    rep(r, R) {
        // cerr << "  assigning band " << r << endl;
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

                if (S0[t][r][k][f.user] > best) {
                    best = S0[t][r][k][f.user];
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
            float bits = anspt.transmitted[js[jj]] + partialscore[jj];
            float missing_bits = max(f.thresh / W - bits + 1e-5f, 0.0f);
            if (missing_bits == 0) continue;

            // cerr << "    user " << js[jj] << " is missing " << missing_bits << " bits" << endl;

            // sort the cells by goodness for this user
            int ordered_cells[10];
            rep(k, K) ordered_cells[k] = k;
            sort(&ordered_cells[0], &ordered_cells[K], [&](int k1, int k2) {
                return S0[t][r][k1][f.user] > S0[t][r][k2][f.user];
            });

            // consider all partitions of cells into taken and not taken
            int mask = 0;
            float base_scoredif = 0;
            rep(kk, K) {
                // consider assigning the kk+1 best cells to this user, and the K-kk worst cells to other users
                int k = ordered_cells[kk];

                // precompute the sum of the K-kk worst cells
                float rest = 0;
                repx(kk2, kk + 1, K) rest += S0[t][r][ordered_cells[kk2]][f.user] * approx_d;

                // include all previous base cell scores (see line tagged with `unnecessary`)
                if (rcount[k][jj]) base_scoredif -= rcount[k][jj] * log1p(exp(logsum[k][jj] / rcount[k][jj]));

                // approximate the change in score we would get by assigning the kk+1 best cells to this user
                // note that the K-kk worst cells will be assigned to other users (we dont know which)
                // approximate the interference with these other users by ignoring the e^(-D) term
                // TODO: use an average e^(-D) term instead of fully ignoring it
                float bitdif = base_scoredif;
                rep(kk2, kk + 1) {
                    int k2 = ordered_cells[kk2];
                    float newlogsum = logsum[k2][jj] + log(S0[t][r][k2][f.user] / (1 + rest));
                    int newrcount = rcount[k2][jj] + 1;
                    bitdif += newrcount * log1p(exp(newlogsum / newrcount));
                    // cerr << "approx_d = " << approx_d << ", rest = " << rest << ", newlogsum = " << newlogsum << ", newrcount = " << newrcount << endl;
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
            ans.P[r][k][f.user] = 1;

            float interf2 = 0;
            rep(k2, K) if (k2 != k && cell_user[k2] != -1) {
                int n2 = F[js[cell_user[k2]]].user;
                if (n2 != f.user) interf2 += S0[t][r][k2][n2] * exp(-D[r][k2][f.user][n2]);
            }
            float s = log(S0[t][r][k][f.user] / (1 + interf2));
            logsum[k][jj] += s;
            rcount[k][jj] += 1;
        }

        // update the partial score for each frame
        rep(jj, jcnt) {
            partialscore[jj] = 0;
            rep(k, K) partialscore[jj] += rcount[k][jj] ? rcount[k][jj] * log1p(exp(logsum[k][jj] / rcount[k][jj])) : 0;
            if (partialscore[jj] != 0) {
                // cerr << "    frame " << js[jj] << " is now at " << W * (transmitted[js[jj]] + partialscore[jj]) << "/" << F[js[jj]].thresh << " bits" << endl;
            }
        }
    }

    anspt.update();
}

void solve_heuristic(Answer &ans) {
    // go time-by-time using a few methods for each time

    vector<int> time_order(T);
    rep(t, T) time_order[t] = t;

    sort(time_order.begin(), time_order.end(), [](auto &a, auto &b) {
        return pertime[a].size() < pertime[b].size();
    });

    AnswerPerTime anspt(&ans);

    for (int t : time_order) {
        anspt.begin_time(t);
        solve_greedy(anspt);
        solve_dp(anspt);
        anspt.end_time();
    }
}

double anneal_start;
double anneal_time() {
    return (clock() - anneal_start) / double(start_time + 18 * CLOCKS_PER_SEC / 10 - anneal_start);
}

void solve_anneal(AnswerStore &out) {
    ScoreKeep &sf = out.temp();

    // start from an heuristic solution
    solve_heuristic(sf.ans);
    sf.resync();

    validate(sf.ans);

    anneal_start = clock();
    cerr << (start_time + 1.8 * CLOCKS_PER_SEC - clock()) / (double)CLOCKS_PER_SEC << " seconds left" << endl;
    int iters = 0, no_r_src = 0, no_j_src = 0, no_r_dst = 0;
    double accept_prob = 1;
    double inc = -3e-5;
    // rep(_iter, 600000) {
    while (anneal_time() < 1) {
        // choose a random perturbation
        float delta = 1;

        // pick a random destination frame, that needs some bits
        if (sf.missing_frames.values.empty()) {
            cerr << "reached optimality" << endl;
            break;
        }
        int j_idx = rng() % sf.missing_frames.values.size();
        int j_dst = sf.missing_frames.values[j_idx];
        // int j_dst = uniform_int_distribution<int>(0, J - 1)(rng);
        int n_dst = F[j_dst].user;

        // pick a random time in its lifetime
        int t = F[j_dst].l + rng() % (F[j_dst].r - F[j_dst].l);

        // pick a random other active frame at this time
        int jj_src = rng() % pertime[t].size();
        int j_src = pertime[t][jj_src];
        if (false && j_dst == j_src) {
            // TODO: maybe disallow moves between the same user
            no_j_src += 1;
            continue;
        }
        int n_src = F[j_src].user;

        // pick a random k
        int k = rng() % K;

        // pick a random destination r
        int r_dst = rng() % R;
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
        int r_src = r_src_candidates[rng() % r_src_count];

        // cerr << "transferring between t=" << t << ", k=" << k << ", from (r=" << r_src << ",n=" << n_src << ",bandpower=" << sf.bandpower[t][r_src][k] << ") to (r=" << r_dst << ",n=" << n_dst << ",bandpower=" << sf.bandpower[t][r_dst][k] << ")" << endl;

        // transfer power
        int old_score = sf.frames;
        float p_src = sf.ans.P[t][r_src][k][n_src];
        float p_dst = sf.ans.P[t][r_dst][k][n_dst];
        sf.set(t, r_src, k, n_src, p_src - delta);
        sf.set(t, r_dst, k, n_dst, p_dst + delta);
        iters += 1;

        // undo operation if it became worse
        // double progress = anneal_time();
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

    rep(j, J) repx(t, F[j].l, F[j].r) {
        pertime[t].push_back(j);
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
