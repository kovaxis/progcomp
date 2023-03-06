#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<pair<int, int>> a;
vector<pair<int, int>> ans;
void op(int i, int j) {
    ans.push_back({i, j});
    a[i].first = (a[i].first + a[j].first - 1) / a[j].first;
}

bool same() {
    bool same = true;
    rep(i, N) same &= (a[i].first == a[0].first);
    return same;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i].first;
        rep(i, N) a[i].second = i;

        if (same()) {
            cout << "0\n";
            continue;
        }

        {
            bool one = false;
            rep(i, N) one |= (a[i].first == 1);
            if (one) {
                cout << "-1\n";
                continue;
            }
        }

        ans.clear();

        while (!same()) {
            int mx = 0;
            int mx_i = -1;
            rep(i, N) if (a[i].first > mx) mx = a[i].first, mx_i = i;
            int mn_i = 0;
            rep(i, N) if (a[i].first < a[mn_i].first) mn_i = i;
            op(mx_i, mn_i);
        }

        cout << ans.size() << "\n";
        for (auto [i, j] : ans) {
            cout << i + 1 << " " << j + 1 << "\n";
        }
    }
}
