#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

// find a maximum gain perfect matching in the given bipartite complete
// graph.
// receives a matrix representing the gain of joining vertex x in set X with
// vertex y in set Y.
// after construction, the matching will be in xy[x] and yx[y].
// runtime: O(N^3)
struct Hungarian {
    int N, qi, root;
    vector<vector<ll>> gain;
    vector<int> xy, yx, p, q, slackx;
    vector<ll> lx, ly, slack;
    vector<bool> S, T;

    void add(int x, int px) {
        S[x] = true, p[x] = px;
        rep(y, N) if (lx[x] + ly[y] - gain[x][y] < slack[y]) {
            slack[y] = lx[x] + ly[y] - gain[x][y], slackx[y] = x;
        }
    }

    void augment(int x, int y) {
        while (x != -2) {
            yx[y] = x;
            swap(xy[x], y);
            x = p[x];
        }
    }

    void iterate() {
        S.assign(N, false), T.assign(N, false), p.assign(N, -1);
        qi = 0, q.clear();
        rep(x, N) if (xy[x] == -1) {
            q.push_back(root = x), p[x] = -2, S[x] = true;
            break;
        }
        rep(y, N) slack[y] = lx[root] + ly[y] - gain[root][y], slackx[y] = root;

        while (true) {
            while (qi < q.size()) {
                int x = q[qi++];
                rep(y, N) if (lx[x] + ly[y] == gain[x][y] && !T[y]) {
                    if (yx[y] == -1) return augment(x, y);
                    T[y] = true, q.push_back(yx[y]), add(yx[y], x);
                }
            }

            ll d = INF;
            rep(y, N) if (!T[y]) d = min(d, slack[y]);
            rep(x, N) if (S[x]) lx[x] -= d;
            rep(y, N) if (T[y]) ly[y] += d;
            rep(y, N) if (!T[y]) slack[y] -= d;

            rep(y, N) if (!T[y] && slack[y] == 0) {
                if (yx[y] == -1) return augment(slackx[y], y);
                T[y] = true;
                if (!S[yx[y]]) q.push_back(yx[y]), add(yx[y], slackx[y]);
            }
        }
    }

    Hungarian(vector<vector<ll>> g)
        : N(g.size()),
          gain(g),
          xy(N, -1),
          yx(N, -1),
          lx(N, -INF),
          ly(N),
          slack(N),
          slackx(N) {
        rep(x, N) rep(y, N) lx[x] = max(lx[x], ly[y]);
        rep(i, N) iterate();
    }
};

int N, O;
vector<vector<ll>> rawmat, mat;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rawmat.resize(N, vector<ll>(N));
    rep(i, N) rep(j, N) cin >> rawmat[i][j];

    O = (N + 1) / 2;
    mat.resize(O, vector<ll>(O));
    rep(i, O) rep(j, O) {
        if (2 * j - 1 >= 0) mat[i][j] -= rawmat[2 * i][2 * j - 1];
        if (2 * j + 1 < N) mat[i][j] -= rawmat[2 * i][2 * j + 1];
    }

    Hungarian h(mat);
    ll ans = 0;
    rep(y, O) ans -= mat[h.yx[y]][y];
    cout << ans << endl;
}
