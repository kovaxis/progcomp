#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef int T;

struct P {
    T x;
    T y;

    P(T x_, T y_) : x{x_}, y{y_} {}
    P() : x{0}, y{0} {}

    friend ostream &operator<<(ostream &s, const P &self) {
        s << self.x << " " << self.y;
        return s;
    }
    friend istream &operator>>(istream &s, P &self) {
        s >> self.x;
        s >> self.y;
        return s;
    }

    P &operator+=(const P &r) {
        this->x += r.x;
        this->y += r.y;
        return *this;
    }
    friend P operator+(P l, const P &r) { return {l.x + r.x, l.y + r.y}; }

    P &operator-=(const P &r) {
        this->x -= r.x;
        this->y -= r.y;
        return *this;
    }
    friend P operator-(P l, const P &r) { return {l.x - r.x, l.y - r.y}; }
    P operator-() { return {-this->x, -this->y}; }

    P &operator*=(const T &r) {
        this->x *= r;
        this->y *= r;
        return *this;
    }
    friend P operator*(P l, const T &r) { return {l.x * r, l.y * r}; }
    friend P operator*(const T &l, P r) { return {l * r.x, l * r.y}; }

    P &operator/=(const T &r) {
        this->x /= r;
        this->y /= r;
        return *this;
    }
    friend P operator/(P l, const T &r) { return {l.x / r, l.y / r}; }

    // Dot product
    friend T operator*(P l, const P &r) { return l.x * r.x + l.y * r.y; }

    // Cross product (equiv to l.rotated() * r in 2D)
    friend T operator^(P l, const P &r) { return l.x * r.y - l.y * r.x; }

    T magsq() { return this->x * this->x + this->y * this->y; }
    T mag() { return sqrt(this->magsq()); }
    P unit() { return (1. / this->mag()) * (*this); }

    P rotated() { return {-this->y, this->x}; }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
    static P from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

int N, M;
char mp[64][64];
int seen[64][64];

bool in_range(P u) {
    return u.x >= 0 && u.x < N && u.y >= 0 && u.y < M;
}

vector<int> calc_convex(P u, P x, P y) {
    vector<int> conv;
    {
        int i = 0;
        while (in_range(u)) {
            P t = u;
            conv.push_back(0);
            while (in_range(t) && mp[t.x][t.y] == '.') t += y, conv[i] += 1;
            u += x;
            i += 1;
        }
    }

    int n = conv.size();
    int mn_i = 0;
    rep(i, n) if (conv[i] < conv[mn_i]) mn_i = i;
    {
        int mn = INT32_MAX;
        repx(i, 0, mn_i) {
            mn = min(mn, conv[i]);
            conv[i] = mn;
        }
    }
    {
        int mn = INT32_MAX;
        invrepx(i, mn_i, n) {
            mn = min(mn, conv[i]);
            conv[i] = mn;
        }
    }

    return conv;
}

bool mark(P u, int m) {
    if (!in_range(u)) return false;
    if (mp[u.x][u.y] != '#') return false;
    if (seen[u.x][u.y]) return false;
    seen[u.x][u.y] = m;
    mark(u + P(1, 0), m);
    mark(u + P(-1, 0), m);
    mark(u + P(0, 1), m);
    mark(u + P(0, -1), m);
    return true;
}

void flip() {
    rep(i, N) rep(j, M / 2) swap(mp[i][j], mp[i][M - j - 1]);
    rep(i, N) rep(j, M / 2) swap(seen[i][j], seen[i][M - j - 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        rep(i, N) rep(j, M) cin >> mp[i][j];

        vector<int> lt = calc_convex({0, 0}, {1, 0}, {0, 1});
        vector<int> rt = calc_convex({0, M - 1}, {1, 0}, {0, -1});
        rep(i, N) {
            repx(j, lt[i], M - rt[i]) {
                mp[i][j] = '#';
            }
        }

        vector<int> tp = calc_convex({0, 0}, {0, 1}, {1, 0});
        vector<int> bt = calc_convex({N - 1, 0}, {0, 1}, {-1, 0});
        rep(j, M) {
            repx(i, tp[j], N - bt[j]) {
                mp[i][j] = '#';
            }
        }

        rep(i, N) rep(j, M) seen[i][j] = 0;
        vector<P> islands;
        rep(i, N) rep(j, M) {
            if (mark({i, j}, islands.size() + 1)) islands.push_back({i, j});
        }

        if (islands.size() > 1) {
            assert(islands.size() == 2);
            P u = islands[0], v = islands[1];
            // cerr << "correcting islands at " << u << " and " << v << endl;
            if (u.x > v.x) swap(u, v);
            bool f = (u.y > v.y);
            if (f) flip(), u.y = M - u.y - 1, v.y = M - v.y - 1;

            // cerr << "  correcting islands at " << u << " and " << v << endl;
            int um = seen[u.x][u.y], vm = seen[v.x][v.y];
            P ucorner = {0, 0};
            rep(i, N) rep(j, M) if (seen[i][j] == um) {
                ucorner.x = max(ucorner.x, i);
                ucorner.y = max(ucorner.y, j);
            }
            P vcorner = {N, M};
            rep(i, N) rep(j, M) if (seen[i][j] == vm) {
                vcorner.x = min(vcorner.x, i);
                vcorner.y = min(vcorner.y, j);
            }

            // cerr << "ucorner = " << ucorner << ", vcorner = " << vcorner << endl;

            repx(j, ucorner.y, vcorner.y + 1) mp[ucorner.x][j] = '#';
            repx(i, ucorner.x, vcorner.x + 1) mp[i][vcorner.y] = '#';

            if (f) flip();
        }

        rep(i, N) {
            rep(j, M) cout << mp[i][j];
            cout << "\n";
        }
        cout << "\n";
        //<< endl;
    }
}
