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
};

int W, H, N;
vector<int> L;
ll gold[8192][8192];
bool worm[8192][8192];
bool used[8192][8192];

P wrap(P u) {
    if (u.x < 0) u.x += W;
    if (u.y < 0) u.y += H;
    if (u.x >= W) u.x -= W;
    if (u.y >= H) u.y -= H;
    return u;
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

    string line;
    rep(i, N) {
        rep(j, L[i]) {
            getline(cin, line);
            stringstream ss(line);
            if (line.size() <= 1) continue;
                }
    }
}
