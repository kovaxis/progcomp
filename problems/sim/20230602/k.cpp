#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

int N, M, K;
vector<string> ans;

bool solve() {
    if (M >= K) return false;
    // M < K
    if (M == 0) {
        if (N > 26) return false;
        ans.resize(N);
        rep(i, N) {
            rep(k, K) ans[i].push_back('a' + i);
        }
        return true;
    }
    if (M == 1) {
        rep(ai, 26) {
            char a = 'a' + ai;
            repx(bi, ai, 26) {
                if (ans.size() >= N) break;
                char b = 'a' + bi;
                string s;
                rep(k, K) s.push_back(k % 2 ? b : a);
                ans.push_back(s);
            }
        }
        return true;
    }
    // M >= 2
    rep(ai, 20) rep(bi, 20) {
        if (ans.size() >= N) break;
        char a = 'a' + ai, b = 'b' + bi;
        string s;
        rep(k, K) {
            if (k % 3 == 0) s.push_back(a);
            else if (k % 3 == 1) s.push_back(b);
            else s.push_back('x');
        }
        ans.push_back(s);
    }
    rep(m, M) ans[0][m] = 'w';
    ans[0][M] = 'y';
    rep(m, M) ans[1][m] = 'w';
    ans[1][M] = 'z';
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    if (solve()) {
        cout << "Yes" << endl;
        rep(i, N) cout << ans[i] << endl;
    } else {
        cout << "No" << endl;
    }
}