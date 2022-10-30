#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)
/*
struct P {
    int x0, y0, x1, y1;
};

struct Hash2d {
    ll HMOD;
    int W, H;
    vector<int> h;
    vector<int> p;

    Hash2d() {}
    Hash2d(const string& s, int W_, int H_)
        : HMOD(1000003931), W(W_ + 1), H(H_ + 1) {
        const ll P = 15647;
        p.resize(W * H);
        p[0] = 1;
        rep(i, W * H - 1) p[i + 1] = p[i] * P % HMOD;
        h.assign(W * H, 0);
        rep(y, 1, H) rep(x, 1, W) {
            ll c = (ll)s[(y - 1) * (W - 1) + x - 1] * p[y * W + x] % HMOD;
            h[y * W + x] = (HMOD + h[y * W + x - 1] + h[(y - 1) * W + x] -
                            h[(y - 1) * W + x - 1] + c) %
                           HMOD;
        }
    }

    bool isout(P s) {
        return s.x0 < 0 || s.x0 >= W || s.x1 < 0 || s.x1 >= W || s.y0 < 0 ||
               s.y0 >= H || s.y1 < 0 || s.y1 >= H;
    }

    pair<ll, int> get(P s) {
        return {(2 * HMOD + h[s.y1 * W + s.x1] - h[s.y1 * W + s.x0] -
                 h[s.y0 * W + s.x1] + h[s.y0 * W + s.x0]) %
                    HMOD,
                s.y0 * W + s.x0};
    }

    bool cmp(pair<ll, int> x0, pair<ll, int> x1) {
        int d = x0.second - x1.second;
        ll& lo = d < 0 ? x0.first : x1.first;
        lo = lo * p[abs(d)] % HMOD;
        return x0.first == x1.first;
    }
};

int N, M;
int X, Y;
string s, p;
Hash2d hs, hp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> M;
        s.resize(N * M);
        rep(y, N) rep(x, M) cin >> s[y * M + x];
        cin >> X >> Y;
        p.assign(N * M, 0);
        rep(y, X) rep(x, Y) cin >> p[y * M + x];

        if (X > N || Y > M) {
            cout << "0\n";
            continue;
        }

        hs = Hash2d(s, M, N);
        hp = Hash2d(p, M, N);

        int ans = 0;
        auto xp = hp.get({0, 0, Y, X});
        rep(y, N) rep(x, M) {
            P l = {x, y, x + Y, y + X};
            if (hs.isout(l)) continue;
            ans += hs.cmp(xp, hs.get(l));
        }

        cout << ans << "\n";
    }
}
*/

using Hash = pair<ll, int>;

struct Block {
    int x0, y0, x1, y1;
};

struct Hash2d {
    ll HMOD;
    int W, H;
    vector<int> h;
    vector<int> p;

    Hash2d() {}
    Hash2d(const string& s, int W_, int H_, ll HMOD_ = 1000003931)
        : W(W_ + 1), H(H_ + 1), HMOD(HMOD_) {
        static const ll P =
            chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
        p.resize(W * H);
        p[0] = 1;
        rep(i, W * H - 1) p[i + 1] = p[i] * P % HMOD;
        h.assign(W * H, 0);
        rep(y, 1, H) rep(x, 1, W) {
            ll c = (ll)s[(y - 1) * (W - 1) + x - 1] * p[y * W + x] % HMOD;
            h[y * W + x] = (HMOD + h[y * W + x - 1] + h[(y - 1) * W + x] -
                            h[(y - 1) * W + x - 1] + c) %
                           HMOD;
        }
    }

    bool isout(Block s) {
        return s.x0 < 0 || s.x0 >= W || s.x1 < 0 || s.x1 >= W || s.y0 < 0 ||
               s.y0 >= H || s.y1 < 0 || s.y1 >= H;
    }

    Hash get(Block s) {
        return {(2 * HMOD + h[s.y1 * W + s.x1] - h[s.y1 * W + s.x0] -
                 h[s.y0 * W + s.x1] + h[s.y0 * W + s.x0]) %
                    HMOD,
                s.y0 * W + s.x0};
    }

    bool cmp(Hash x0, Hash x1) {
        int d = x0.second - x1.second;
        ll& lo = d < 0 ? x0.first : x1.first;
        lo = lo * p[abs(d)] % HMOD;
        return x0.first == x1.first;
    }
};

struct Hash2dM {
    int N;
    vector<Hash2d> sub;

    Hash2dM() {}
    Hash2dM(const string& s, int W, int H, const vector<ll>& mods)
        : N(mods.size()) {
        sub.resize(N);
        rep(i, N) sub[i] = Hash2d(s, W, H, mods[i]);
    }

    bool isout(Block s) { return sub[0].isout(s); }

    vector<Hash> get(Block s) {
        vector<Hash> hs(N);
        rep(i, N) hs[i] = sub[i].get(s);
        return hs;
    }

    bool cmp(const vector<Hash>& x0, const vector<Hash>& x1) {
        rep(i, N) if (!sub[i].cmp(x0[i], x1[i])) return false;
        return true;
    }

    bool cmp(Block s0, Block s1) {
        rep(i, N) if (!sub[i].cmp(sub[i].get(s0), sub[i].get(s1))) return false;
        return true;
    }
};

const vector<ll> HMOD = {1000002649, 1000000933, 1000003787, 1000002173};

int N, M;
int X, Y;
string s, p;
Hash2dM hs, hp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> M;
        s.resize(N * M);
        rep(y, N) rep(x, M) cin >> s[y * M + x];
        cin >> X >> Y;
        p.assign(N * M, 0);
        rep(y, X) rep(x, Y) cin >> p[y * M + x];

        if (X > N || Y > M) {
            cout << "0\n";
            continue;
        }

        hs = Hash2dM(s, M, N, HMOD);
        hp = Hash2dM(p, M, N, HMOD);

        int ans = 0;
        auto xp = hp.get({0, 0, Y, X});
        rep(y, N) rep(x, M) {
            Block l = {x, y, x + Y, y + X};
            if (hs.isout(l)) continue;
            ans += hs.cmp(xp, hs.get(l));
        }

        cout << ans << "\n";
    }
}