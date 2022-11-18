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

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> a(N);
        rep(i, N) cin >> a[i];

        map<int, int> cnt;
        rep(i, N) cnt[a[i]] += 1;
        int mx = 0, mxa;
        for (auto p : cnt)
            if (p.second > mx) mx = p.second, mxa = p.first;

        int ops = 0;
        while (mx < N) {
            ops += 1;
            int add = min(N - mx, mx);
            ops += add;
            mx += add;
        }

        cout << ops << "\n";
    }
}
