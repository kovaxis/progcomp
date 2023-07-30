#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ii, ii> iiii;
vector<vector<ll>> costo;
vector<ll> dp;
ll grande = 1000000000000000000;

ll DP(int n) {
    if (dp[n] != -1) {
        return dp[n];
    }

    dp[n] = costo[n - 1][0] + DP(n - 1);
    if (n > 0) {
        dp[n] = min(dp[n], costo[n - 1][1] + DP(n - 2));
    }
    if (n > 1) {
        dp[n] = min(dp[n], costo[n - 1][2] + DP(n - 3));
    }

    return dp[n];
}

ll C1(iiii a) {
    if (a.first.second / 2 != a.second.second / 2) {
        return abs(a.first.first - a.second.first);
    }
    return grande;
}

ll C2(iiii a, iiii b) {

    if (a.first.second / 2 != b.first.second / 2 && a.second.second / 2 != b.second.second / 2) {
        return abs(a.first.first - b.first.first) + abs(a.second.first - b.second.first);
    }
    if (a.first.second / 2 != b.second.second / 2 && a.second.second / 2 != b.first.second / 2) {
        return abs(a.first.first - b.second.first) + abs(a.second.first - b.first.first);
    }

    return grande;

    return 0;
}

ll C3(iiii a, iiii b, iiii c) {

    vector<ii> A(6);
    A[0] = a.first;
    A[1] = a.second;
    A[2] = b.first;
    A[3] = b.second;
    A[4] = c.first;
    A[5] = c.second;

    ll mini = grande;

    sort(A.begin(), A.end());

    do {
        ll sum = 0;
        for (int i = 0; i < 3; i++) {
            sum = sum + C1({A[2 * i], A[2 * i + 1]});
        }

        mini = min(mini, sum);

    } while (next_permutation(A.begin(), A.end()));

    return mini;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ii> A(2 * n);

    for (int i = 0; i < 2 * n; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }

    sort(A.begin(), A.end());

    vector<iiii> B(n);
    for (int i = 0; i < n; i++) {
        B[i].first = A[2 * i];
        B[i].second = A[2 * i + 1];
    }

    costo.resize(n, vector<ll>(3, grande));
    dp.resize(n + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        costo[i][0] = C1(B[i]);
        if (i > 0) {
            costo[i][1] = C2(B[i], B[i - 1]);
        }
        if (i > 1) {
            costo[i][2] = C3(B[i], B[i - 1], B[i - 2]);
        }
    }

    cout << DP(n) << endl;

    return 0;
}