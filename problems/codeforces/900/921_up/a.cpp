#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof rng
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int N, K, M;
string S, ans;

pair<int, char> findlast(int i) {
    bool found[26];
    int foundcnt = 0;
    rep(k, K) found[k] = false;
    repx(j, i, M) {
        int c = S[j] - 'a';
        if (!found[c]) {
            found[c] = true;
            foundcnt += 1;
            if (foundcnt == K) {
                return {j, S[j]};
            }
        }
    }
    rep(k, K) if (!found[k]) return {M, 'a' + k};
    assert(false);
}

bool solve() {
    int now = 0;
    ans.clear();
    rep(n, N) {
        auto [last, lastc] = findlast(now);
        if (last >= M) {
            ans.push_back(lastc);
            ans.resize(N, 'a');
            return true;
        } else {
            ans.push_back(lastc);
            now = last + 1;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K >> M >> S;
        if (!solve()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
            cout << ans << "\n";
        }
    }
}
