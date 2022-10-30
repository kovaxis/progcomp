#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<ll> a;
set<int> nonzero;
vector<vector<pair<int, int>>> b;
deque<pair<int, int>> rqueue;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        a.resize(N + 1), b.assign(N + 1, {});
        nonzero.clear(), rqueue.clear();
        rep(i, N) cin >> a[i + 1];
        rep(i, N) {
            ll b;
            cin >> b;
            a[i + 1] = b - a[i + 1];
        }
        rep(i, N) a[i + 1] += a[i];
        rep(i, M) {
            int l, r;
            cin >> l >> r;
            l -= 1;
            pair<int, int> range = {l, r};
            if (a[l] == 0 && a[r] == 0)
                rqueue.push_back(range);
            else
                b[l].push_back(range), b[r].push_back(range);
        }
        rep(i, N + 1) if (a[i] != 0) nonzero.insert(i);

        while (!rqueue.empty()) {
            auto [l, r] = rqueue.front();
            rqueue.pop_front();
            // cerr << "setting range [" << l + 1 << ", " << r << "] to zero"
            //     << endl;
            for (auto it = nonzero.lower_bound(l + 1);
                 it != nonzero.end() && *it < r; it = nonzero.erase(it)) {
                int i = *it;
                a[i] = 0;
                for (int j = 0; j < b[i].size();) {
                    auto [pl, pr] = b[i][j];
                    if (a[pl] == 0 && a[pr] == 0) {
                        swap(b[i][j], b[i].back());
                        b[i].pop_back();
                        rqueue.push_back({pl, pr});
                    } else {
                        j++;
                    }
                }
            }
        }

        cout << (nonzero.empty() ? "YES" : "NO") << "\n";
    }
}
