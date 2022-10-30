#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

string a;
string b;

// a_from, b_from
// min_cost, child_start
pair<int, int> dp[1001][1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b;
    rep(i, a.size()) { dp[i][b.size()] = {a.size() - i, b.size()}; }
    rep(j, b.size() + 1) { dp[a.size()][j] = {b.size() - j, b.size()}; }
    invrep(i, a.size()) {
        int min_noreplace = a.size() - i;
        int min_cost = a.size() - i;
        int min_pos = b.size();
        invrep(j, b.size()) {
            int delcost = 1 + dp[i + 1][j].first;
            if (b[j] == a[i]) {
                min_cost = min_noreplace - 1;
            }
            dp[i][j].first = min(delcost, min_cost);
            if (dp[i][j].first == delcost) {
                dp[i][j].second = j;
            } else if (dp[i][j].first == min_cost) {
                dp[i][j].second = min_pos;
            }
            min_noreplace = min(delcost, min_noreplace + 1);
            min_cost = min(delcost, min_cost + 1);
            if (delcost == min_cost) {
                min_pos = j;
            }
        }
    }

    cout << dp[0][0].first << endl;
    int j = 0;
    rep(i, a.size() + 1) {
        int next_j = dp[i][j].second;
        if (next_j == j) {
            if (i < a.size()) {
                cout << "DELETE " << (j + 1) << endl;
            }
        } else {
            bool skip = true;
            invrep(k, j, next_j) {
                if (skip && i < a.size() && a[i] == b[k]) {
                    skip = false;
                } else {
                    if (j == next_j - 1 && i < a.size()) {
                        cout << "REPLACE ";
                    } else {
                        cout << "INSERT ";
                    }
                    cout << (j + 1) << " " << b[k] << endl;
                }
            }
            j = next_j;
        }
    }
}
