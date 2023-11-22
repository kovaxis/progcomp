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

float score(const Answer &ans) {
    int frames = 0;
    rep(j, J) {
        Frame f = F[j];
        float transmitted = 0;
        repx(t, f.l, f.r) {
            rep(k, K) {
                int bands = 0;
                float product = 1;
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

                        product *= S0[t][k][r][f.user] * ans.P[t][k][r][f.user] * exp(interf1) / (1 + interf2);
                        bands += 1;
                    }
                }
                transmitted += bands * log1p(powf(product, 1.0f / bands));
            }
        }
        frames += (W * transmitted >= f.thresh);
    }

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

Answer solve_naive() {
    Answer ans;

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
            cerr << "frame " << j << " transmitted " << 192 * transmitted << "/" << f.thresh << " at time interval [" << f.l << ", " << t << "]" << endl;
        }
    }
    return ans;
}

Answer solve_smartgreedy() {
    Answer ans;

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
                bands[r] = {-rank, r};
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
                if (192 * transmitted[j] >= f.thresh) continue;
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

    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    // Read input
    cin >> N >> K >> T >> R;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) cin >> S0[t][k][r][n];
    rep(k, K) rep(r, R) rep(m, N) rep(n, N) cin >> D[k][r][m][n];
    cin >> J;
    rep(j, J) {
        int _j, s, u, l, d;
        cin >> _j >> s >> u >> l >> d;
        F[j] = {s, u, l, l + d};
    }

    // Optimize
    Answer ans = solve_smartgreedy();

    // Print output
    cout << fixed << setprecision(10);
    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << ans.P[t][k][r][n] << " ";
        cout << "\n";
    }
}
