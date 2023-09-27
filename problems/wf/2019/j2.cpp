#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

struct Vertex {
    ll x, y, m;
};

int N, M;
vector<vector<ll>> H;
vector<vector<Vertex>> A;
vector<pair<ll, int>> E;

int signum(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    H.resize(N, vector<ll>(M));
    rep(i, N) rep(j, M) cin >> H[i][j];

    A.resize(N);
    rep(i, N) {
        sort(H[i].begin(), H[i].end());
        ll x = 0, y = 0, m = M;
        A[i].push_back({x, y, m});
        for (ll x2 : H[i]) {
            y += (x2 - x) * m;
            x += x2 - x;
            m -= 1;
            if (x == A[i].back().x) A[i].pop_back();
            A[i].push_back({x, y, m});
        }
        A[i].push_back({ll(1e15) + 2, A[i].back().y, 0});
    }

    rep(i, N) {
        cerr << "line " << i + 1 << ":";
        for (auto v : A[i]) cerr << " (" << v.x << ", " << v.y << ")";
        cerr << endl;
    }

    rep(i, N) {
        E.clear();
        rep(j, N) {
            cerr << "checking intersections between " << i + 1 << " and " << j + 1 << endl;
            int ik = 0, jk = 0;
            while (ik < (int)A[i].size() - 1 && jk < (int)A[j].size() - 1) {
                Vertex i1 = A[i][ik];
                Vertex j1 = A[j][jk];
                Vertex i2 = A[i][ik + 1];
                Vertex j2 = A[j][jk + 1];
                ll x1 = max(i1.x, j1.x);
                ll x2 = min(i2.x, j2.x);

                ll iy1 = i1.y + (x1 - i1.x) * i1.m;
                ll jy1 = j1.y + (x1 - j1.x) * j1.m;
                ll iy2 = i1.y + (x2 - i1.x) * i1.m;
                ll jy2 = j1.y + (x2 - j1.x) * j1.m;

                int l = signum(iy1 - jy1);
                int r = signum(iy2 - jy2);
                cerr << "    type (" << l << ", " << r << ") intersection at vertices " << ik << " and " << jk << endl;

                if (x2 == i2.x) ik++;
                if (x2 == j2.x) jk++;

                // add one when r < 0

                if (l * r > 0) continue;
                if (l * r < 0) {
                    // intersection
                    ll num = iy1 - jy1;
                    ll den = j1.m - i1.m;
                    assert(den != 0);
                    if (den < 0) {
                        num *= -1, den *= -1;
                    }
                    ll x;
                    if (r < 0) {
                        x = x1 + num / den + 1;
                        cerr << "    +1 at x = " << x << endl;
                        E.push_back({x, 1});
                    } else {
                        x = x1 + (num + den - 1) / den;
                        cerr << "    -1 at x = " << x << endl;
                        E.push_back({x, -1});
                    }
                    continue;
                }
                if (l == 0 && r == 0) continue;
                if (r < 0) {
                    cerr << "    +1 separate at x = " << x1 + 1 << endl;
                    E.push_back({x1 + 1, 1});
                }
                if (l < 0) {
                    cerr << "    -1 join at x = " << x2 << endl;
                    E.push_back({x2, -1});
                }
            }
        }

        sort(E.begin(), E.end());
        int acc = 0, ans = 0;
        for (int ei = 0; ei < (int)E.size();) {
            ll x = E[ei].first;
            while (ei < (int)E.size() && E[ei].first == x) {
                acc += E[ei].second;
                ei += 1;
            }
            ans = max(ans, acc);
        }
        cout << N - ans << "\n";
    }
}
