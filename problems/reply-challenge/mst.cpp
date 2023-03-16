#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define log \
    if (0) cerr

struct P {
    int x, y;

    P(int x, int y) : x(x), y(y) {}
    P() : x(0), y(0) {}

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }

    bool operator==(P r) const { return x == r.x && y == r.y; }
    bool operator<(P r) const { return x != r.x ? x < r.x : y < r.y; }
};

int W, H, N;
vector<int> L;
ll gold[8192][8192];
bool worm[8192][8192];
int used[8192][8192];

ll goldhalf[4096][4096];

vector<vector<P>> snakes;

P wrap(P u) {
    if (u.x < 0) u.x += W;
    if (u.y < 0) u.y += H;
    if (u.x >= W) u.x -= W;
    if (u.y >= H) u.y -= H;
    return u;
}

void solve() {
    rep(x, W / 2) rep(y, H / 2) {
        goldhalf[x][y] = gold[2 * x][2 * y] + gold[2 * x + 1][2 * y] + gold[2 * x][2 * y + 1] + gold[2 * x + 1][2 * y + 1];
    }

    vector<pair<ll, P>> ordered;
    rep(x, W / 2) rep(y, H / 2) if (!worm[2 * x][2 * y] && !worm[2 * x + 1][2 * y] && !worm[2 * x][2 * y + 1] && !worm[2 * x + 1][2 * y + 1]) ordered.push_back({-goldhalf[x][y], {x, y}});
    sort(ordered.begin(), ordered.end(), [](auto l, auto r) { return l.first < r.first; });

    rep(i, N) {
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> H >> W >> N;
    L.resize(N);
    rep(i, N) cin >> L[i];
    rep(y, H) rep(x, W) {
        cin >> s;
        if (s[0] == '*') {
            worm[x][y] = true;
        } else {
            gold[x][y] = stoi(s);
        }
    }

    rep(x, W) rep(y, H) used[x][y] = -1;

    vector<pair<ll, P>> ordered;
    rep(x, W) rep(y, H) if (!worm[x][y]) ordered.push_back({-gold[x][y], {x, y}});
    sort(ordered.begin(), ordered.end(), [](auto l, auto r) { return l.first < r.first; });

    priority_queue<pair<ll, P>> q;
    // rep(i, N) q.push(ordered[i]);

    while (true) {
        if (q.empty()) q.push(ordered[oi++]);
    }
}
