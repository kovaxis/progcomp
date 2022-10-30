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

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

const ll INF = 1e18;

int N, M;
ll C;
vector<ll> unitsraw, unitcost, monsters;
vector<pair<ll, ll>> unitsort;
vector<pair<ll, ll>> units;
vector<ll> cost2u;
map<ll, ll> u2cost;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> C;
    unitsraw.resize(N), unitcost.resize(N), unitsort.resize(N);
    rep(i, N) {
        ll c, d, h;
        cin >> c >> d >> h;
        unitsraw[i] = d * h;
        unitcost[i] = c;
    }
    cin >> M;
    monsters.resize(M);
    rep(i, M) {
        ll d, h;
        cin >> d >> h;
        monsters[i] = d * h;
    }

    rep(i, N) unitsort[i] = {unitcost[i], unitsraw[i]};
    sort(unitsort.begin(), unitsort.end());
    rep(i, N) {
        if (units.empty() || units.back().first != unitsort[i].first)
            units.push_back(unitsort[i]);
        else
            units.back().second = unitsort[i].second;
    }

    cost2u.assign(C + 1, 0);
    for (auto unit : units) {
        ll cost = unit.first;
        ll u = unit.second;
        rep(n, 1, C + 1) {
            ll totalcost = n * cost;
            if (totalcost > C) break;
            cost2u[totalcost] = max(cost2u[totalcost], u * n);
        }
    }

    ll high_u = 0;
    rep(cost, C + 1) {
        if (cost2u[cost] == 0) continue;
        high_u = max(high_u, cost2u[cost]);
        cost2u[cost] = high_u;
    }

    rep(cost, C + 1) {
        ll u = cost2u[cost];
        if (!u2cost.count(u)) {
            // cerr << "adding u -> cost pair of u = " << u
            //     << " and cost = " << cost << endl;
            u2cost[u] = cost;
        }
    }

    rep(j, M) {
        ll m_u = monsters[j];
        auto it = u2cost.lower_bound(m_u + 1);
        if (it == u2cost.end()) {
            cout << "-1";
        } else {
            cout << it->second;
        }
        cout << " \n"[j == M - 1];
    }
}
