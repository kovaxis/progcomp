#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll STRAIGHT_BONUS = 2;
const int ORDER_NOISE = 2;

#define log \
    if (0) cerr

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

vector<vector<P>> snakes;

P wrap(P u) {
    if (u.x < 0) u.x += W;
    if (u.y < 0) u.y += H;
    if (u.x >= W) u.x -= W;
    if (u.y >= H) u.y -= H;
    return u;
}

vector<P> snake;
ll score = 0;

vector<P> offsets = {P(1, 0), P(-1, 0), P(0, 1), P(0, -1)};

void drawmap() {
    int l = W, r = 0;
    int u = H, d = 0;
    rep(x, W) rep(y, H) if (used[x][y]) l = min(l, x), r = max(r, x), u = min(u, y), d = max(d, y);
    cerr << "drawing range [" << l << ", " << u << "] to [" << r << ", " << d << "]" << endl;
    repx(y, u, d + 1) {
        repx(x, l, r + 1) cerr << " X"[used[x][y]];
        cerr << endl;
    }
}

void savegold(string filename) {
    ofstream file;
    file.open(filename);
    file << "P3\n"
         << W << " " << H << "\n";
    ll mn = 1e9, mx = -1e9;
    rep(x, W) rep(y, H) mn = min(mn, gold[x][y]), mx = max(mx, gold[x][y]);
    ll mxabs = max(-mn, mx);
    const ll R = 1000;
    file << 2 * R << "\n";
    rep(y, H) {
        rep(x, W) file << max(-gold[x][y], 0ll) * R / mxabs << " " << max(gold[x][y], 0ll) * R / mxabs << " " << (worm[x][y] ? R : 0) << " ";
        file << "\n";
    }
    file.close();
}

void savemap(string filename) {
    ofstream file;
    file.open(filename);
    file << "P2\n"
         << W << " " << H << "\n";
    file << 2 * N << "\n";
    rep(y, H) {
        rep(x, W) file << (used[x][y] ? N + used[x][y] : 0) << " ";
        file << "\n";
    }
    file.close();
}

P applyoff(P p, int i) {
    return wrap(p + offsets[i]);
}

void trybest(pair<ll, int> &best, P u, int i, int prev) {
    u = applyoff(u, i);
    if (used[u.x][u.y]) return;
    if (worm[u.x][u.y]) return;
    ll g = gold[u.x][u.y];
    if (i == prev) g += STRAIGHT_BONUS;
    if (g > best.first) best = {g, i};
}

bool availmoves[4];

int bestmove(P u, int prev) {
    pair<ll, int> best = {INT64_MIN, -1};
    rep(k, 4) if (availmoves[k]) trybest(best, u, k, prev);
    return best.second;
}

bool place_snake(int i, int n, P u, int prev) {
    if (n >= L[i]) return true;
    u = wrap(u);
    if (used[u.x][u.y]) return false;
    used[u.x][u.y] = i + 1;
    score += gold[u.x][u.y];
    snake.push_back(u);
    // cerr << "placing segment " << n << " of snake " << i << " at " << u.x << " " << u.y << endl;
    int nxt = -1;
    int tries = 0;
    rep(k, 4) availmoves[k] = true;
    while (true) {
        nxt = bestmove(u, prev);
        if (nxt == -1) break;
        if (place_snake(i, n + 1, applyoff(u, nxt), nxt)) return true;
        tries += 1;
        availmoves[nxt] = false;
        if (tries < 4) continue;
        if (tries < 4 && uniform_int_distribution<int>(0, 0 * L[i])(rng) <= L[i] - n)
            continue;
        break;
    }
    snake.pop_back();
    score -= gold[u.x][u.y];
    used[u.x][u.y] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> H >> W >> N;
    L.resize(N);
    snakes.resize(N);
    rep(i, N) cin >> L[i];
    rep(y, H) rep(x, W) {
        cin >> s;
        if (s[0] == '*') {
            worm[x][y] = true;
        } else {
            gold[x][y] = stoi(s);
        }
    }

    rep(x, W) rep(y, H) used[x][y] = 0;

    savegold("images/gold2.ppm");
    return 0;

    vector<pair<int, int>> snakeorder(N);
    rep(i, N) snakeorder[i] = {-L[i] + uniform_int_distribution<int>(-ORDER_NOISE, ORDER_NOISE)(rng), i};
    sort(snakeorder.begin(), snakeorder.end());

    // vector<pair<ll, P>> biggest;
    // biggest.reserve(W * H);
    // rep(x, W) rep(y, H) biggest.push_back({gold[x][y], {x, y}});
    // sort(biggest.rbegin(), biggest.rend());
    // cerr << "sorted " << W * H << " elements" << endl;

    int done = 0, skipped = 0;
    ll total = 0;
    for (auto [_s, i] : snakeorder) {
        int metatries = 10;
        ll bestscore = 0;
        vector<P> bestsnake;
        while (metatries > 0) {
            int tries = 1000;
            int idxnoise = 0;
            rep(fulltries, 10000) {
                if (tries < 0) break;
                // double choose = (double)uniform_int_distribution<int>(0, W * H - 1)(rng) / (W * H);
                // choose = choose;
                // int choosei = choose * W * H;
                // int choosei = fulltries + uniform_int_distribution<int>(-idxnoise, idxnoise)(rng);
                // idxnoise += 1;
                // if (idxnoise < W * H) idxnoise = idxnoise * 5 / 2;
                // if (choosei < 0) choosei = 0;
                // if (choosei >= W * H) choosei = W * H - 1;
                // P start = biggest[choosei].second;

                P start = {
                    uniform_int_distribution<int>(0, W - 1)(rng),
                    uniform_int_distribution<int>(0, H - 1)(rng),
                };

                if (used[start.x][start.y]) continue;
                if (worm[start.x][start.y]) continue;
                tries -= 1;
                score = 0;
                snake.clear();
                if (place_snake(i, 0, start, uniform_int_distribution<int>(0, 3)(rng))) {
                    if (score >= bestscore) bestsnake = snake, bestscore = score;
                    for (P p : snake) used[p.x][p.y] = false;
                    break;
                }
            }
            metatries -= 1;
        }
        // cerr << "using snake with score " << bestscore << endl;
        for (P p : bestsnake) used[p.x][p.y] = true;
        total += bestscore;
        snakes[i] = bestsnake;
        if (bestsnake.empty()) {
            skipped += 1;
        }

        if (done % 20 == 0) {
            cerr << done << "/" << N << " snakes done, " << skipped << "/" << done << " skipped" << endl;
        }
        done += 1;
    }

    rep(i, N) {
        if (!snakes[i].empty()) {
            P last = snakes[i][0];
            bool first = true;
            rep(j, L[i]) {
                P p = snakes[i][j];
                P d = wrap(p - last);
                if (first) first = false;
                else cout << ' ';
                if (d == P(1, 0)) cout << 'R';
                else if (d == P(0, 1)) cout << 'D';
                else if (d == P(W - 1, 0)) cout << 'L';
                else if (d == P(0, H - 1)) cout << 'U';
                else cout << p.x << " " << p.y;
                last = p;
            }
        }
        cout << endl;
    }

    savemap("images/snakes.ppm");

    cerr << "score: " << total << endl;
}
