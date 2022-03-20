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

struct Query {
    int t, id;
    ll x;
};

ll N, L, U, Q;
vector<ll> a;
vector<Query> evs;
int nxt_q;
// real + offset = in-memory
ll offset;
map<ll, set<int>> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L >> U;
    a.resize(N);
    rep(i, N) cin >> a[i];
    cin >> Q;
    rep(i, Q) {
        int b, e;
        ll x;
        cin >> b >> e >> x;
        queries.push_back({b - 1, i, x});
        queries.push_back({e - 1, i, -1});
    }

    sort(queries.begin(), queries.end(),
         [](Query& l, Query& r) { return l.t < r.t; });

    rep(t, N) {
        while (nxt_q < queries.size() && queries[nxt_q].t <= t) {
            auto& q = queries[nxt_q];
            nxt_q += 1;

            if (q.x >= 0) {
                b.insert({q.x + offset, q.id});
            } else {
            }
            b.insert({queries[nxt_q].x + offset, queries[nxt_q].id});
        }

        b.
    }
}
