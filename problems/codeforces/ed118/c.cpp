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

inline ll ceildiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0)) + 1;
}

ll N, H;
vector<ll> a;

// {k, {base, mult}}
vector<pair<ll, pair<ll, ll>>> atks;

bool cankill(ll k) {
    int l = 0, r = atks.size() - 1;
    while (l != r) {
        int m = l + (r - l + 1) / 2;
        if (atks[m].first > k) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    auto& atk = atks[l];

    // acc + m * dk >= H
    // m * dk >= H - acc
    // dk >= (H - acc)/m
    // dk >= ceil((H - acc) / m)
    // cerr << "attacking with k = " << k << ": " << atk.second.first << " + "
    //     << atk.second.second << " * " << k - atk.first << " damage" << endl;
    return (k - atk.first) >= ceildiv(H - atk.second.first, atk.second.second);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> H;
        a.resize(N), atks.resize(N);
        rep(i, N) cin >> a[i];

        atks[0] = {0, {0, 0}};
        rep(i, 1, N) atks[i] = {a[i] - a[i - 1], {0, 0}};
        sort(atks.begin(), atks.end());
        ll acc = 0, lastk = 0;
        rep(i, N) {
            acc += (atks[i].first - lastk) * (N - i + 1);
            lastk = atks[i].first;
            atks[i].second = {acc, N - i};
            // cerr << "attack with k >= " << lastk << " deals " << acc << " + "
            //     << N - i << " * (k - " << lastk << ") damage" << endl;
        }

        ll l = 0, r = H;
        while (l != r) {
            ll m = l + (r - l) / 2;
            if (cankill(m)) {
                // cerr << "k = " << m << " kills the dragon" << endl;
                r = m;
            } else {
                // cerr << "k = " << m << " does not kill the dragon" << endl;
                l = m + 1;
            }
        }

        cout << l << "\n";
    }
}
