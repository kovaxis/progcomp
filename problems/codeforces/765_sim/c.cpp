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

int N, L, K;
vector<ll> d, a;
vector<bool> rem;
vector<int> nxt, prv;
priority_queue<pair<ll, pair<int, pair<int, int>>>> que;

void pushstop(int j) {
    int i = prv[j], k = nxt[j];
    ll area = (d[k] - d[j]) * (a[j] - a[i]);
    que.push({area, {j, {i, k}}});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L >> K;
    d.resize(N + 1);
    rep(i, N) cin >> d[i];
    d[N] = L;
    a.resize(N + 1);
    rep(i, N) cin >> a[i];
    a[N] = 0;

    nxt.resize(N + 1);
    rep(i, N + 1) nxt[i] = i + 1;
    prv.resize(N + 1);
    rep(i, N + 1) prv[i] = i - 1;
    rem.assign(N + 1, false);

    rep(j, 1, N) pushstop(j);

    while (!que.empty() && K) {
        auto it = que.top();
        que.pop();
        int j = it.second.first;
        int i = it.second.second.first;
        int k = it.second.second.second;
        if (rem[j] || rem[i] || rem[k]) continue;

        if (it.first <= 0) break;
        nxt[i] = k;
        prv[k] = i;
        rem[j] = true;
        K -= 1;

        if (i > 0) pushstop(i);
        if (k < N) pushstop(k);
    }

    ll time = 0;
    int i = 0;
    while (i < N) {
        ll timeperkm = a[i];
        ll d0 = d[i];
        i = nxt[i];
        ll d1 = d[i];
        time += timeperkm * (d1 - d0);
    }
    cout << time << endl;
}
