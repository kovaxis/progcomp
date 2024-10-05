#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

struct P {
    ll x, y;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(ll r) const { return {x * r, y * r}; }
    ll operator*(P r) const { return x * r.x + y * r.y; }
    P perp() const { return {-y, x}; }
    ll operator%(P r) const { return perp() * r; }

    int half() const {
        return (y == 0 && x < 0) || y < 0;
    }
    ll angcmp(P r) const {
        int h = half() - r.half();
        return h ? h : r % *this;
    }

    bool operator<(P r) const {
        return angcmp(r) < 0;
    }

    friend ostream &operator<<(ostream &s, P r) {
        return s << r.x << " " << r.y;
    }
};

struct Query {
    int lx, ly, rx, ry;
    int qi;
};

int N, Qn;
P ps[5000];
P p2p[5000][5000];
vector<Query> pq[5000];
int Q[4000000][3];
short Qans[4000000];

int countrange(int i, P l, P r) {
    // cerr << "counting range on " << i + 1 << " for " << l << " to " << r << endl;
    // cerr << "l < r? " << (l < r) << endl;
    // cerr << "r < l? " << (r < l) << endl;
    if (r < l) return countrange(i, {1, 0}, r) + countrange(i, l, P{ll(2e9) + 1, -1});
    return lower_bound(p2p[i], p2p[i] + N - 1, r) - lower_bound(p2p[i], p2p[i] + N - 1, l);
}

double now() {
    return clock() / (double)CLOCKS_PER_SEC;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        double t0 = now();
        cin >> N >> Qn;
        rep(i, N) cin >> ps[i].x >> ps[i].y;
        rep(qi, Qn) rep(k, 3) cin >> Q[qi][k];
        rep(qi, Qn) rep(k, 3) Q[qi][k] -= 1;

        double t1 = now();
        rep(i, N) {
            rep(j, N) p2p[i][j] = ps[j];
            swap(p2p[i][i], p2p[i][N - 1]);
            rep(j, N - 1) p2p[i][j] = p2p[i][j] - ps[i];
            sort(p2p[i], p2p[i] + N - 1);
        }
        double t2 = now();
        rep(qi, Qn) {
            P a = ps[Q[qi][0]], b = ps[Q[qi][1]], c = ps[Q[qi][2]];
            if ((b - a) % (c - a) < 0) swap(Q[qi][0], Q[qi][1]);
            rep(k, 3) {
                P l = ps[Q[qi][k]] - ps[Q[qi][(k + 2) % 3]];
                P r = ps[Q[qi][(k + 1) % 3]] - ps[Q[qi][k]];
                pq[Q[qi][k]].push_back(Query{(int)l.x, (int)l.y, (int)r.x, (int)r.y, qi});
            }
        }
        rep(i, N) {
            for (Query q : pq[i]) {
                Qans[q.qi] += countrange(i, {q.lx, q.ly}, {q.rx, q.ry});
            }
        }
        rep(qi, Qn) {
            cout << (Qans[qi] == N - 3 ? "YES" : "NO") << "\n";
        }
        double t3 = now();

        cerr << "input: " << t1 - t0 << endl;
        cerr << "presolve: " << t2 - t1 << endl;
        cerr << "solve: " << t3 - t2 << endl;
    }
}
