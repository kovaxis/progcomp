#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;

struct P {
    int x, y;

    P perp() { return {-y, x}; }
    P operator-() { return {-x, -y}; }
    P operator-(P r) { return {x - r.x, y - r.y}; }
    P operator+(P r) { return {x + r.x, y + r.y}; }

    int id() { return x + y * W; }
};

char mp[128][128];
vector<P> spiral;
vector<int> ans;

bool is_marked(P p) {
    int x = p.x, y = p.y;
    if (x < 0 || x >= W || y < 0 || y >= H) return false;
    return mp[x][y] == 'X';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H;
    invrep(y, H) rep(x, W) cin >> mp[x][y];

    {
        P dir = {0, 1}, cur = {0, 0};
        int d = 1;
        rep(stage, 2 + 4 * max(W, H)) {
            rep(i, d) {
                spiral.push_back(cur);
                cur = cur + dir;
            }
            dir = -dir.perp();
            if (stage % 2) d += 1;
        }
        // cerr << "spiral:";
        // for (P p : spiral) cerr << " (" << p.x << ", " << p.y << ")";
        // cerr << endl;
    }

    vector<vector<P>> groups, nxt;
    groups.push_back({});
    rep(y, H) rep(x, W) groups[0].push_back({x, y});

    ans.resize(W * H, 1e9);

    rep(i, (int)spiral.size()) {
        nxt.clear();
        for (auto &group : groups) {
            vector<P> out[2];
            for (P p : group) {
                out[is_marked(p + spiral[i])].push_back(p);
            }
            rep(k, 2) {
                if (out[k].size() >= 2) nxt.push_back(out[k]);
                else if (out[k].size() == 1) {
                    for (P p : out[k]) {
                        ans[p.id()] = i;
                    }
                }
            }
        }
        swap(groups, nxt);
    }

    ll sm = 0;
    int mx = 0;
    vector<P> mx_p;
    rep(y, H) rep(x, W) {
        P p = {x, y};
        int r = ans[p.id()];
        sm += r;
        if (r > mx) mx = r, mx_p.clear();
        if (r == mx) mx_p.push_back(p);
    }

    cout << fixed << setprecision(9) << (double)sm / (W * H) << endl;
    cout << mx << endl;
    for (P p : mx_p) {
        cout << "(" << p.x + 1 << "," << p.y + 1 << ") ";
    }
    cout << endl;
}
