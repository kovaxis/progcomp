#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a, b, ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N), b.resize(N), ans.resize(N);
    rep(i, N) cin >> a[i];
    rep(i, N) a[i] -= 1;

    rep(l, N) {
        b.assign(N, 0);
        int mcol = 0, mcnt = 0;
        repx(r, l, N) {
            int col = a[r];
            int& cnt = b[col];
            cnt += 1;
            if (cnt > mcnt || (cnt == mcnt && col < mcol))
                mcol = col, mcnt = cnt;
            ans[mcol] += 1;
        }
    }

    rep(i, N) cout << ans[i] << " \n"[i == N - 1];
}
