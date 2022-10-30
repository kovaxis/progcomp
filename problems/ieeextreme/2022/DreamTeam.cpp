// incomplete

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int B;
int N[5];
vector<pair<string, ll>> P[5];

int f(int x) {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> B;
    rep(k, 5) {
        cin >> N[k];
        P[k].resize(N[k]);
        rep(i, N[k]) {
            cin >> P[k][i].first >> P[k][i].second;
        }
        sort(P[k].begin(), P[k].end());
    }

    vector<pair<ll, pair<int, int>>> combos;
    rep(i0, N[0]) rep(i1, N[1]) {
        ll bonus = P[0][i0].second + P[1][i1].second;
        ll xmax = B - bonus;
        combos.push_back({xmax, {i0, i1}});
    }
}
