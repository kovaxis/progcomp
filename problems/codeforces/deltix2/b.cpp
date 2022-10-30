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

int N;
vector<bool> a;
int counts[2];

ll getcost(bool nxt) {
    int ptr = 0;
    ll cost = 0;
    rep(i, N) {
        nxt = !nxt;
        if (!nxt) continue;
        if (ptr >= N) return INT64_MAX;
        while (!a[ptr]) {
            if (++ptr >= N) return INT64_MAX;
        }
        cost += abs(i - ptr);
        ptr += 1;
    }
    rep(i, ptr, N) if (a[i]) return INT64_MAX;
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.clear();
        rep(i, 2) counts[i] = 0;
        rep(i, N) {
            int x;
            cin >> x;
            a.push_back(x % 2 == 1);
            counts[x % 2] += 1;
        }
        ll mincost = INT64_MAX;
        rep(i, 2) mincost = min(mincost, getcost(i));
        cout << (mincost >= INT64_MAX ? -1 : mincost) << "\n";
    }
}
