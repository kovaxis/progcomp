#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int W, H, K;
vector<vector<int>> def;
vector<pair<int, int>> winds;

bool is_inside(int x, int y) {
    return x >= 0 && x < W && y >= 0 && y < H;
}

int get(int x, int y) {
    if (is_inside(x, y)) return def[x][y];
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H >> K;
    def.assign(W, vector<int>(H, -1));
    winds.resize(K);
    rep(k, K) {
        int dx, dy;
        cin >> dx >> dy;
        winds[k] = {dx, dy};

        int n;
        cin >> n;
        rep(i, n) {
            int x, y;
            cin >> x >> y;
            x -= 1, y -= 1;
            def[x][y] = 1;
            if (is_inside(x - dx, y - dy)) def[x - dx][y - dy] = 0;
        }
    }

    vector<pair<int, int>> q;
    rep(x, W) rep(y, H) if (def[x][y] == -1) q.push_back({x, y});
    while (!q.empty()) {
        auto [x, y] = q.back();
        q.pop_back();

        if (def[x][y] != -1) continue;
        for (auto [wx, wy] : winds) {
            if (get(x - wx, y - wy) == 0) def[x][y] = 0;
            if (get(x + wx, y + wy) == 1) def[x][y] = 1;
        }
        if (def[x][y] != -1) {
            int dir = def[x][y] ? -1 : 1;
            for (auto [wx, wy] : winds) {
                int ox = x + dir * wx, oy = y + dir * wy;
                if (get(ox, oy) == -1) q.push_back({ox, oy});
            }
        }
    }

    rep(y, H) rep(x, W) cout << "..#"[def[x][y] + 1] << (x == W - 1 ? "\n" : "");
    cout << "\n";
    rep(y, H) rep(x, W) cout << "#.#"[def[x][y] + 1] << (x == W - 1 ? "\n" : "");
}
