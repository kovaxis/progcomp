#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const ll P = chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
const ll MOD = 1e9 + 7;

int W, H;
vector<string> mp;
vector<pair<int, int>> marks;
vector<pair<int, int>> spiral;

bool marked(int x, int y) {
    if (x < 0 || x >= W || y < 0 || y >= H) return false;
    return mp[y][x] == 'X';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H;
    mp.resize(H);
    invrep(y, H) cin >> mp[y];

    rep(y, H) rep(x, W) {
        if (marked(x, y)) marks.push_back({x, y});
    }

    for (auto [x, y] : marks) cerr << "mark at " << x + 1 << ", " << y + 1 << endl;

    {
        int x = 0, y = 0, d = 0;
        spiral.push_back({0, 0});
        while (abs(x) <= 101 && abs(y) <= 101) {
            d += 1;
            rep(i, d) y += 1, spiral.push_back({x, y});
            rep(i, d) x += 1, spiral.push_back({x, y});
            d += 1;
            rep(i, d) y -= 1, spiral.push_back({x, y});
            rep(i, d) x -= 1, spiral.push_back({x, y});
        }
    }

    ll p = 1;
    vector<vector<ll>> hashes(H, vector<ll>(W, 0));
    unordered_map<ll, unordered_set<ll>> cnt;
    vector<vector<int>> ans(H, vector<int>(W, -1));
    vector<int> check;
    rep(y, H) rep(x, W) cnt[0].insert(y * W + x);
    rep(iter, spiral.size()) {
        p = p * P % MOD;
        cerr << "iteration " << iter << " with p = " << p << endl;
        check.clear();
        for (auto [mx, my] : marks) {
            auto [dx, dy] = spiral[iter];
            int ox = mx - dx;
            int oy = my - dy;

            if (ox < 0 || ox >= W || oy < 0 || oy >= H) continue;
            ll &h = hashes[oy][ox];
            ll old_h = h;
            h = (h + p) % MOD;
            cnt[old_h].erase(oy * W + ox);
            cnt[h].insert(oy * W + ox);
            check.push_back(old_h);
            check.push_back(h);
            cerr << "  checking " << ox + 1 << ", " << oy + 1 << endl;
        }
        if (iter == 0) {
            check.clear();
            rep(y, H) rep(x, W) check.push_back(hashes[y][x]);
        }

        for (ll h : check) {
            if (cnt[h].size() == 1) {
                ll xy = *cnt[h].begin();
                int x = xy % W, y = xy / W;
                if (ans[y][x] == -1) {
                    cerr << "  hash at " << x + 1 << ", " << y + 1 << " is unique" << endl;
                    ans[y][x] = iter;
                }
            }
        }
    }

    double ex = 0.;
    int mx = -1e9;
    vector<pair<int, int>> mxcoords;
    rep(y, H) rep(x, W) {
        ex += ans[y][x];
        if (ans[y][x] > mx) mx = ans[y][x], mxcoords.clear();
        if (ans[y][x] == mx) mxcoords.push_back({x, y});
    }
    ex /= W * H;

    cout << fixed << setprecision(3) << setw(3) << ex << "\n";
    cout << mx << "\n";
    rep(i, mxcoords.size()) cout << "(" << mxcoords[i].first + 1 << "," << mxcoords[i].second + 1 << ")"
                                 << " \n"[i == mxcoords.size() - 1];
}
