#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const int INF = 1e9;

int N, K;
vector<int> gold;
vector<set<int>> adj;

void maketree(int i) {
    for (int edge : adj[i]) {
        adj[edge].erase(i);
        maketree(edge);
    }
}

// i, k, l
// subtree root node, amount of paths, `l`
// l = 0 -> unconstrained
// l = 1 -> loose (restricted)
int subtree_dp[64][128][2];

// i, k, l
// up_to_child (base 1), total paths, amount of restricted children
int omega[64][128][64];

void compute_omega(int idx) {
    int n = adj[idx].size();
    rep(k, 2 * K + 1) rep(l, n + 1) omega[0][k][l] = l == 0 ? 0 : -INF;
    auto it = adj[idx].begin();
    rep(i, 1, n + 1) {
        rep(k, 2 * K + 1) rep(l, n + 1) {
            int mx = -INF;
            rep(m, k + 1) {
                mx = max(mx, omega[i - 1][k - m][l] + subtree_dp[*it][m][0]);
                if (l > 0) {
                    mx = max(
                        mx, omega[i - 1][k - m][l - 1] + subtree_dp[*it][m][1]);
                }
            }
            omega[i][k][l] = mx;
        }
        it++;
    }
}

void selmax(int mx[], int val, bool loose) {
    mx[0] = max(mx[0], val);
    if (loose) mx[1] = max(mx[1], val);
}

void compute_subtree(int idx, bool only_through) {
    int n = adj[idx].size();
    for (int child : adj[idx]) compute_subtree(child, false);
    compute_omega(idx);
    rep(k, 2 * K + 1) subtree_dp[idx][k][0] = 0, subtree_dp[idx][k][1] = -INF;
    rep(k, 1, 2 * K + 1) {
        int* mx = subtree_dp[idx][k];
        selmax(mx, omega[n][k - 1][0] + gold[idx], true);
        rep(m, n + 1) {
            if (k + m / 2 > 2 * K) break;
            if (only_through && m == 0) continue;
            selmax(mx, omega[n][k + m / 2][m] + (m == 0 ? 0 : gold[idx]),
                   m % 2);
        }
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        int T;
        cin >> T;
        rep(t, T) {
            cin >> N >> K;
            gold.resize(N);
            adj.clear();
            adj.resize(N);
            rep(i, N) cin >> gold[i];
            rep(i, N - 1) {
                int u, v;
                cin >> u >> v;
                adj[u - 1].insert(v - 1);
                adj[v - 1].insert(u - 1);
            }

            if (K == 0) {
                subtree_dp[0][K][0] = gold[0];
            } else {
                maketree(0);
                compute_subtree(0, true);
            }

            cout << "Case #" << t + 1 << ": " << subtree_dp[0][K][0] << "\n";
        }
    }
