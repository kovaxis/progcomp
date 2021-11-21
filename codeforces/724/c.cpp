//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

ll normratio(int d, int k) {
    double a = (double)d / (double)k;
    ll norm = *reinterpret_cast<ll*>(&a);
    // cout << "normalized ratio " << d << "/" << k << " into " << norm << endl;
    return norm;
}

string s;
unordered_map<ll, int> dp[500001];

int maxways(int upto) {
    int dk[2] = {0, 0};
    int maxsplit = 1;
    invrep(splitat, upto) {
        dk[s[splitat] == 'K'] += 1;
        ll ratio = normratio(dk[0], dk[1]);
        int splitc;
        if (splitat == 0) {
            splitc = 1;
        } else {
            if (dp[splitat][ratio] == 0) {
                splitc = 0;
            } else {
                splitc = dp[splitat][ratio] + 1;
            }
        }
        dp[upto][ratio] = max(dp[upto][ratio], splitc);
        maxsplit = max(maxsplit, splitc);
    }
    return maxsplit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int n;
        cin >> n;
        cin >> s;
        rep(i, 1, n + 1) {
            dp[i].clear();
            if (i > 1) cout << ' ';
            cout << maxways(i);
        }
        cout << '\n';
    }
}
