#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int W = 128, H = 128;

struct Cloud {
    pair<int, int> d;
    vector<pair<int, int>> p;
};

int N;
vector<Cloud> clouds;
pair<int, int> src, dst;

int rcur = 0;
bool reach[2][W][H];
vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int dot(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first * y.first + x.second * y.second;
}

pair<int, int> rot(pair<int, int> x) { return {-x.second, x.first}; }

pair<int, int> sub(const pair<int, int>& x, const pair<int, int>& y) {
    return {x.first - y.first, x.second - y.second};
}

pair<int, int> add(const pair<int, int>& x, const pair<int, int>& y) {
    return {x.first + y.first, x.second + y.second};
}

pair<int, int> mul(int x, const pair<int, int>& y) {
    return {x * y.first, x * y.second};
}

bool is_inside(pair<int, int> x, Cloud& c, int t) {
    int z = 0;
    pair<int, int> last = mul(4, c.p.back());
    for (pair<int, int> p : c.p) {
        p = mul(4, p);
        pair<int, int> p1 = add(last, mul(t, c.d)), p2 = add(p, mul(t, c.d));
        if (p1.first != p2.first) continue;
        if (x.second <= min(p1.second, p2.second)) continue;
        if (x.second >= max(p1.second, p2.second)) continue;
        if (p1.second < p2.second) {
            // up (open)
            if (p1.first < x.first) continue;
            z += 1;
        } else {
            // down (close)
            if (p1.first <= x.first) continue;
            z -= 1;
        }
        last = p;
    }
    return z != 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> src.first >> src.second >> dst.first >> dst.second >> N;
    clouds.resize(N);
    rep(i, N) {
        Cloud& c = clouds[i];
        char d;
        int V;
        cin >> d >> V;
        if (d == 'N')
            c.d = {0, 1};
        else if (d == 'S')
            c.d = {0, -1};
        else if (d == 'W')
            c.d = {-1, 0};
        else if (d == 'E')
            c.d = {1, 0};
        c.p.resize(V);
        rep(i, V) cin >> c.p[i].first >> c.p[i].second;
    }

    int t = 0;
    reach[rcur][src.first][src.second] = true;
    while (!reach[rcur][dst.first][dst.second]) {
        // advance one
        rep(x, W) rep(y, H) {
            reach[!rcur][x][y] |= reach[rcur][x][y];
            for (auto d : dirs) {
                int x2 = x + d.first, y2 = y + d.second;
                if (x2 < 0 || x2 >= W || y2 < 0 || y2 >= H) continue;
                if (!reach[rcur][x][y]) continue;
                if (reach[rcur][x2][y2]) continue;
                if (reach[!rcur][x2][y2]) continue;

                // check if we can reach from (x, y) to (x, y) + d = (x2, y2) at
                // time t
                bool can_move = true;
                for (Cloud& c : clouds) {
                    pair<int, int> me = {x, y};
                    pair<int, int> me2 = sub(add(me, d), c.d);
                    if (is_inside(add(mul(3, me), me2), c, t) ||
                        is_inside(add(me, mul(3, me2)), c, t))
                        can_move = false;
                }
                reach[!rcur][x2][y2] = can_move;
                if (can_move)
                    cerr << "reached " << x2 << ", " << y2 << " at time "
                         << t + 1 << endl;
            }
        }
        rcur = !rcur;
        t += 1;
    }
    cout << t << endl;
}
