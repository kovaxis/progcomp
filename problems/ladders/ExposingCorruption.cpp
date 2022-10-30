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

struct Dsu {
    vector<int> p, r;

    Dsu() {}
    // initialize the disjoint-set-union to all unitary sets
    void resize(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two disjoint sets with leaders `i` and `j`
    // note: `i` and `j` must be LEADERS OF TWO SEPARATE SETS
    int unite(int i, int j) {
        if (r[i] > r[j]) {
            p[j] = i;
            return j;
        } else {
            if (r[i] == r[j]) r[j] += 1;
            p[i] = j;
            return i;
        }
    }
};

int N[2], R;
ll B;
vector<ll> prices[2];
Dsu groups;
// cost, benefit
// benefit = extra members to the current party
vector<pair<ll, ll>> deals;

bool cmpdeal(pair<ll, ll>& a, pair<ll, ll>& b) {
    if (a.second == 0) return false;
    if (b.second == 0) return true;
    return a.second * b.first > b.second * a.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N[0]) {
        cin >> N[1] >> R >> B;
        rep(k, 2) prices[k].resize(N[k]);
        rep(k, 2) rep(i, N[k]) cin >> prices[k][i];
        groups.resize(N[0] + N[1]);
        rep(i, R) {
            int x, y;
            cin >> x >> y;
            y += N[0];
            x = groups.find(x - 1);
            y = groups.find(y - 1);
            if (x != y) groups.unite(x, y);
        }

        deals.assign(N[0] + N[1], {0, 0});
        rep(k, 2) rep(i, N[k]) {
            int x = i;
            if (k) x += N[0];
            x = groups.find(x);
            deals[x].first += prices[k][i];
            deals[x].second += k ? 1 : -1;
        }

        rep(k, 2) {
            sort(deals.begin(), deals.end(), cmpdeal);

            /*
            cerr << "deals for k = " << k << endl;
            for (auto deal : deals) {
                cerr << "  " << deal.second << " people for $" << deal.first
                     << endl;
            }
            */

            ll b = B;
            ll n = N[k];
            for (auto deal : deals) {
                b -= deal.first;
                if (b < 0) break;
                if (deal.second < 0) break;
                n += deal.second;
            }

            for (auto& deal : deals) {
                deal.second *= -1;
            }

            cout << n << " \n"[k];
        }
    }
}
