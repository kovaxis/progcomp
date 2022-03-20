
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll T, D, M;

    cin >> T >> D >> M;

    vector<ll> sweep;
    for (int i = 0; i < M; i++) {
        ll y;
        cin >> y;
        sweep.push_back(y);
    }

    sweep.push_back(D);
    sort(sweep.begin(), sweep.end());

    ll prev = 0;
    bool o = 0;
    for (auto it : sweep) {
        if (it - prev >= T) o = 1;

        prev = it;
    }

    if (o)
        cout << "Y\n";
    else
        cout << "N\n";
}