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
vector<int> a;
// {max_range, single_range}
vector<pair<int, int>> range;
vector<int> nxt, prv;
vector<bool> used;

void mark(int k) {
    nxt[prv[k]] = nxt[k];
    prv[nxt[k]] = prv[k];
    used[k] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N), range.resize(N), nxt.resize(N + 2), prv.resize(N + 2),
            used.assign(N + 2, false);
        rep(i, N) cin >> a[i];
        rep(i, N) range[i] = {(a[i] + 1) / 2 - 1, a[i]};
        sort(range.begin(), range.end());
        rep(i, N + 2) nxt[i] = i + 1;
        rep(i, N + 2) prv[i] = i - 1;
        rep(i, N) {
            int& k = range[i].second;
            if (k <= N && !used[k]) mark(k), k = 0;
        }
        int ops = 0;
        bool wrong = false;
        rep(i, N) {
            if (range[i].second == 0) continue;
            int hi = range[i].first;
            if (nxt[0] <= hi && nxt[0] <= N)
                mark(nxt[0]), ops += 1;
            else
                wrong = true;
        }
        if (wrong)
            cout << "-1\n";
        else
            cout << ops << "\n";
    }
}
