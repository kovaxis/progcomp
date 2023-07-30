#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N;
        cin >> N;
        vector<string> A(N);
        rep(i, N) cin >> A[i];

        vector<pair<string, int>> B;
        rep(i, N) rep(j, (int)A[i].size()) repx(k, j + 1, (int)A[i].size() + 1) {
            B.push_back({A[i].substr(j, k - j), i});
        }

        sort(B.begin(), B.end());
        int ans = 0;
        rep(i, (int)B.size() - 1) {
            if (B[i].second == B[i + 1].second) continue;

            int com = 0;
            rep(k, (int)min(B[i].first.size(), B[i + 1].first.size())) {
                if (B[i].first[k] == B[i + 1].first[k]) com += 1;
                else break;
            }
            cerr << "pair '" << B[i].first << "' and '" << B[i + 1].first << "' have " << com << " chars in common" << endl;
            ans = max(ans, com);
        }

        cout << ans << "\n";
    }
}