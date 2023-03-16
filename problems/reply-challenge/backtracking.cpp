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

const int EXPLORE_DEPTH = 1;

const ll NOISE4 = 0;
const ll NOISEW = 0;
const ll NOISELIST = 1e9;

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
vector<P> worms;
ll gold[8192][8192];
bool worm[8192][8192];
bool used[8192][8192];

ll score, best_score;
vector<vector<P>> snakes, best_snakes;

P wrap(P u) {
    if (u.x < 0) u.x += W;
    if (u.y < 0) u.y += H;
    if (u.x >= W) u.x -= W;
    if (u.y >= H) u.y -= H;
    return u;
}

ll explore(int d, int i);

ll explore_seg(int d, int i, int j, P p) {
    if (d < 0) return score;
    if (j >= L[i]) {
        // finished this snake
        return explore(d - 1, i + 1);
    }
    p = wrap(p);
    if (worm[p.x][p.y]) {
        cerr << "exploring wormhole" << endl;
        ll m = INT64_MIN;
        for (P w : worms) {
            if (w == p) continue;
            snakes[i][j] = w;
            m = max(m, explore_seg(d - 1, i, j + 1, w + P(1, 0)));
            m = max(m, explore_seg(d - 1, i, j + 1, w + P(-1, 0)));
            m = max(m, explore_seg(d - 1, i, j + 1, w + P(0, 1)));
            m = max(m, explore_seg(d - 1, i, j + 1, w + P(0, -1)));
        }
        return m;
    }
    if (used[p.x][p.y]) return INT64_MIN;
    used[p.x][p.y] = true;
    score += gold[p.x][p.y];
    snakes[i][j] = p;
    cerr << "exploring recursive 4 with depth " << d << " at " << p.x << " " << p.y << endl;
    ll m = explore_seg(d - 1, i, j + 1, p + P(1, 0));
    m = max(m, explore_seg(d - 1, i, j + 1, p + P(-1, 0)));
    m = max(m, explore_seg(d - 1, i, j + 1, p + P(0, 1)));
    m = max(m, explore_seg(d - 1, i, j + 1, p + P(0, -1)));
    score -= gold[p.x][p.y];
    used[p.x][p.y] = false;
    return m;
}

ll explore(int d, int i) {
    if (d < 0) return score;
    if (i >= N) {
        // placed all snakes
        return score;
    }
    cerr << "exploring " << i << endl;
    ll m = explore(d - 1, i + 1);
    rep(x, W) rep(y, H) if (!worm[x][y]) m = max(m, explore_seg(d - 1, i, 0, {x, y}));
    return m;
}

void try_explore(ll noise, vector<pair<ll, P>> &opts, int i, int j, P p) {
    cerr << "starting explore at " << p.x << " " << p.y << endl;
    uniform_int_distribution<ll> distr(0, noise);
    ll s = explore_seg(EXPLORE_DEPTH, i, j, p) + distr(rng);
    opts.push_back({s, p});
}

void sortopts(vector<pair<ll, P>> &opts) {
    sort(opts.begin(), opts.end(), [](auto &l, auto &r) {
        return l.first > r.first;
    });
}

int place(int d, int i);

int place_seg(int d, int i, int j, P p) {
    rep(_, d) log << " ";
    cerr << "placing snake " << i << ", segment " << j << " at " << p.x << " " << p.y << endl;
    if (j >= L[i]) {
        // finished this snake
        return place(d + 1, i + 1);
    }
    p = wrap(p);
    if (worm[p.x][p.y]) {
        if (j == L[i] - 1) return 1;
        cerr << "entering wormhole" << endl;
        vector<pair<ll, P>> opts;
        opts.reserve((worms.size() - 1) * 4);
        for (P w : worms) {
            if (w == p) continue;
            snakes[i][j] = w;
            try_explore(NOISEW, opts, i, j + 1, w + P(1, 0));
            try_explore(NOISEW, opts, i, j + 1, w + P(-1, 0));
            try_explore(NOISEW, opts, i, j + 1, w + P(0, 1));
            try_explore(NOISEW, opts, i, j + 1, w + P(0, -1));
        }
        sortopts(opts);
        int fail = 0;
        for (auto &opt : opts) {
            int f = place_seg(d + 1, i, j + 1, opt.second);
            if (!f) return 0;
            fail += f;
            if (uniform_int_distribution<int>(0, 100)(rng) > 3) break;
            // if (fail >= 10) break;
        }
        return fail;
    }
    if (used[p.x][p.y]) return 1;
    used[p.x][p.y] = true;
    score += gold[p.x][p.y];
    snakes[i][j] = p;
    vector<pair<ll, P>> opts;
    opts.reserve(4);
    cerr << "exploring 4" << endl;
    try_explore(NOISE4, opts, i, j + 1, p + P(1, 0));
    try_explore(NOISE4, opts, i, j + 1, p + P(-1, 0));
    try_explore(NOISE4, opts, i, j + 1, p + P(0, 1));
    try_explore(NOISE4, opts, i, j + 1, p + P(0, -1));
    cerr << "finished exploring 4" << endl;
    sortopts(opts);
    int fail = 0;
    for (auto &opt : opts) {
        int f = place_seg(d + 1, i, j + 1, opt.second);
        if (!f) return 0;
        fail += f;
        if (uniform_int_distribution<int>(0, 100)(rng) > 3) break;
        // if (fail >= 10) break;
    }
    score -= gold[p.x][p.y];
    used[p.x][p.y] = false;
    return fail;
}

int place(int d, int i) {
    if (i >= N) {
        // placed all snakes
        rep(_, d) log << " ";
        // cerr << "finished snakes with score " << score << endl;
        if (score > best_score) {
            rep(_, d) log << " ";
            cerr << "new best: " << score << endl;
            best_snakes = snakes;
            best_score = score;
        }
        return 0;
    }
    rep(_, d) log << " ";
    cerr << "placing snake " << i << endl;
    vector<pair<ll, P>> opts;
    opts.reserve(W * H + 1);
    opts.push_back({INT64_MIN, {-1, -1}});
    rep(x, W) rep(y, H) if (!worm[x][y]) {
        try_explore(NOISELIST, opts, i, 0, {x, y});
    }
    sortopts(opts);
    int fail = 0;
    for (auto &opt : opts) {
        if (opt.second == P(-1, -1)) {
            int f = place(d + 1, i + 1);
            if (!f) return 0;
            fail += f;
        } else {
            int f = place_seg(d + 1, i, 0, opt.second);
            if (!f) return 0;
            fail += f;
        }
        if (uniform_int_distribution<int>(0, 100)(rng) > 3) break;
        // if (fail >= 10) break;
    }
    cerr << "skipping snake " << i << endl;
    return place(d + 1, i + 1);
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
            worms.push_back({x, y});
        } else {
            gold[x][y] = stoi(s);
        }
    }

    snakes.resize(N);
    rep(i, N) snakes[i].resize(L[i]);

    cerr << "searching..." << endl;
    place(0, 0);

    if (best_snakes.empty()) {
        cerr << "best_snakes is empty?!" << endl;
        exit(1);
    }

    rep(i, N) {
        if (!best_snakes[i].empty()) {
            P last = best_snakes[i][0];
            bool first = true;
            rep(j, L[i]) {
                P p = best_snakes[i][j];
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
}
