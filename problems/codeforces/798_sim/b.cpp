#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<int> p(N), q(N);
        rep(i, N) cin >> p[i];

        if (N == 1) {
            cout << "-1\n";
            continue;
        }

        set<int> a;
        rep(i, N) a.insert(i + 1);
        rep(i, N) {
            auto it = a.begin();
            if (*it == p[i])
                if (a.size() == 1) {
                    q[i] = q[i - 1];
                    q[i - 1] = *it;
                    a.erase(it);
                    continue;
                } else {
                    ++it;
                }
            q[i] = *it;
            a.erase(it);
        }

        rep(i, N) cout << q[i] << " \n"[i == N - 1];
    }
}
