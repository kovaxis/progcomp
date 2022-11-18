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
        vector<int> a(N);
        rep(i, N) cin >> a[i];

        int l = 0, r = N;
        while (l < N && a[l] == 0) l++;
        while (r > 0 && a[r - 1] == 0) r--;

        bool z = false;
        repx(i, l, r) if (a[i] == 0) z = true;

        bool allz = true;
        repx(i, l, r) if (a[i] != 0) allz = false;

        int ans;
        if (allz)
            ans = 0;
        else if (z)
            ans = 2;
        else
            ans = 1;
        cout << ans << "\n";
    }
}
