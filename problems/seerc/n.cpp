#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, M;
    cin >> N >> M;
    vector<ll> S(N);
    rep(i, N) cin >> S[i];

    priority_queue<pair<ll, int>> q;
    rep(i, N) q.push({S[i], i});

    while (!q.empty()) {
        ll s = q.top().first;
        int i = q.top().second;
        q.pop();
        if (s != S[i]) continue;

        if (i - 1 >= 0 && S[i - 1] < S[i] - M) {
            S[i - 1] = S[i] - M;
            q.push({S[i - 1], i - 1});
        }
        if (i + 1 < N && S[i + 1] < S[i] - M) {
            S[i + 1] = S[i] - M;
            q.push({S[i + 1], i + 1});
        }
    }

    rep(i, N) cout << S[i] << " \n"[i == N - 1];
}