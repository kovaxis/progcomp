#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

typedef ll T;

struct P {
    T x, y;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(T r) const { return {x * r, y * r}; }
    friend P operator*(T r, P p) { return p * r; }

    T operator*(P r) const { return x * r.x + y * r.y; }
    T operator%(P r) const { return perp() * r; }
    P perp() const { return {-y, x}; }
};

int N;
ll ans_time;
pair<P, string> rabbits[11];
ll Dn[11];
P D[11][101];
P Dacc[11][101];
P Dfull[11];
bool pillado[11];

bool can_move_dist(P delta, ll dt) {
    return (abs(delta.x) <= dt && abs(delta.y) <= dt);
}

pair<ll, P> pillar_time(int i, P at, ll t) {
    // cerr << "checking conejo " << i << " at " << at.x << " " << at.y << " t = " << t << endl;
    P x = rabbits[i].first + Dfull[i] * (t / Dn[i]) + Dacc[i][(t % Dn[i])] - at;
    // if (t + abs(x.x) > ll(3e15) || t + abs(x.y) > ll(3e15)) return {-1, {0, 0}}; // todo: revisar
    if (x.x == 0 && x.y == 0) return {t, {0, 0}};

    ll cycles = 0;
    if (x.x != 0) {
        ll step = (x.x < 0 ? -Dn[i] : Dn[i]) - Dfull[i].x;
        if (step == 0) return {-1, {0, 0}};
        step = abs(step);
        cycles = max(cycles, (abs(x.x) + step - 1) / step);
    }
    if (x.y != 0) {
        ll step = (x.y < 0 ? -Dn[i] : Dn[i]) - Dfull[i].y;
        if (step == 0) return {-1, {0, 0}};
        step = abs(step);
        cycles = max(cycles, (abs(x.y) + step - 1) / step);
    }

    // cerr << "checking conejo " << i << " at " << at.x << " " << at.y << " t = " << t << endl;
    // if (t + cycles * Dn[i] > ll(2e15)) return {-1, {0, 0}};

    x = x + (cycles - 1) * Dfull[i];
    t = t + (cycles - 1) * Dn[i];

    ll l = 1, r = Dn[i];
    while (l != r) {
        ll m = (l + r) / 2;
        P delta = x + Dacc[i][t % Dn[i] + m] - Dacc[i][t % Dn[i]];
        if (can_move_dist(delta, (cycles - 1) * Dn[i] + m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    x = x + Dacc[i][t % Dn[i] + r] - Dacc[i][t % Dn[i]];
    t = t + r;

    return {t, x};
}

void backtrack(int i, P at, ll t) {
    if (t > ll(1e15) || t >= ans_time) return;
    // todo: podar
    // pillar conejo i
    auto [t_pillar, x_pillar] = pillar_time(i, at, t);
    if (t_pillar == -1) return;

    cerr << "catching bunnies";
    rep(i, N) if (pillado[i]) {
        cerr << " " << i + 1;
    }
    cerr << " at time " << t << endl;

    t = t_pillar;
    at = at + x_pillar;

    // pillar otros conejos
    pillado[i] = true;
    bool done = true;
    rep(j, N) if (!pillado[j]) {
        done = false;
        backtrack(j, at, t);
    }
    pillado[i] = false;

    if (done) {
        // encontramos una solucion
        if (t < ans_time) ans_time = t;
        return;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    rep(i, N) cin >> rabbits[i].first.x;
    rep(i, N) cin >> rabbits[i].first.y;
    rep(i, N) cin >> rabbits[i].second;

    mt19937 rng;
    shuffle(&rabbits[0], &rabbits[N], rng);

    rep(i, N) {
        string &s = rabbits[i].second;
        Dn[i] = s.size();
        rep(j, s.size()) {
            if (s[j] == 'U') D[i][j] = {0, 1};
            if (s[j] == 'D') D[i][j] = {0, -1};
            if (s[j] == 'L') D[i][j] = {-1, 0};
            if (s[j] == 'R') D[i][j] = {1, 0};
            Dacc[i][j + 1] = Dacc[i][j] + D[i][j];
        }
        rep(j, s.size()) {
            if (s[j] == 'U') D[i][Dn[i] + j] = {0, 1};
            if (s[j] == 'D') D[i][Dn[i] + j] = {0, -1};
            if (s[j] == 'L') D[i][Dn[i] + j] = {-1, 0};
            if (s[j] == 'R') D[i][Dn[i] + j] = {1, 0};
            Dacc[i][Dn[i] + j + 1] = Dacc[i][Dn[i] + j] + D[i][Dn[i] + j];
        }
        Dfull[i] = Dacc[i][Dn[i]];
    }

    ans_time = ll(1e15) + 1;
    rep(i, N) backtrack(i, {0, 0}, 0);

    if (ans_time > ll(1e15)) {
        cout << "-1" << endl;
    } else {
        cout << ans_time << endl;
    }
}
