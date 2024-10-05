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

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

struct Meet {
    vector<ll> times;
    ll period;
};

ll N, R, K;

vector<ll> initial;
vector<vector<ll>> patterns;
vector<vector<Meet>> meet;

ll time_to_meet(ll time, ll rz, ll rv) {
    Meet& mt = meet[min(rz, rv)][max(rz, rv)];
    if (mt.times.empty()) return -1;
    auto it = lower_bound(mt.times.begin(), mt.times.end(), time % mt.period);
    if (it == mt.times.end()) it = mt.times.begin();
    return ((*it - time) % mt.period + mt.period) % mt.period;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        cin >> R >> K;
        initial.resize(R), patterns.assign(R, vector<ll>(K + 1)),
            meet.assign(R, vector<Meet>(R, Meet{}));
        rep(r, R) {
            cin >> initial[r];
            initial[r] -= 1;
        }
        rep(r, R) {
            ll acc = 0;
            rep(k, K) {
                ll jump;
                cin >> jump;
                acc += jump;
                patterns[r][k + 1] = acc;
            }
        }

        rep(r1, R) rep(r2, r1) {
            auto& mt = meet[r2][r1];
            ll B = patterns[r1][K] - patterns[r2][K];
            ll c1, c2;
            ll d = ext_gcd(B, N, c1, c2);
            ll m = abs(N / d);
            ll M = m * K;
            mt.period = M;
            rep(k, K) {
                ll A = initial[r1] - initial[r2] + patterns[r1][k] -
                       patterns[r2][k];
                if ((-A) % d != 0) continue;
                ll x = -A / d * c1;
                x = (x % m + m) % m;
                ll t = (x * K + k) % M;
                mt.times.push_back(t);
            }
            sort(mt.times.begin(), mt.times.end());
        }

        vector<ll> dists(R, INT64_MAX);
        dists[0] = 0;
        priority_queue<pair<ll, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            ll d = q.top().first;
            int v = q.top().second;
            q.pop();
            if (d > dists[v]) continue;
            rep(to, R) {
                ll w = time_to_meet(d, v, to);
                if (w == -1) continue;
                if (d + w < dists[to]) {
                    dists[to] = d + w;
                    q.push({dists[to], to});
                }
            }
        }

        ll maxt = 0, infect = 0;
        rep(r, R) {
            if (dists[r] == INT64_MAX) continue;
            maxt = max(maxt, dists[r]);
            infect += 1;
        }
        cout << infect << " " << maxt << "\n";

        /*
        vector<bool> infected(R);
        infected[0] = true;
        ll time = 0, icount = 1;
        while (true) {
            ll mindt = INT64_MAX, infect = -1;
            rep(rz, R) {
                if (!infected[rz]) continue;
                rep(rv, R) {
                    if (infected[rv]) continue;
                    ll dt = time_to_meet(time, rz, rv);
                    if (dt == -1) continue;
                    if (dt < mindt) mindt = dt, infect = rv;
                }
            }
            if (infect == -1) break;
            infected[infect] = true;
            time = (time + mindt) % (N * K);
            icount += 1;
        }
        cout << icount << " " << time << "\n";
        */
    }
}
