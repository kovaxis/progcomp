#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<int> a;

int nxt(int i) {
    return (i + 1) % a.size();
}
int prv(int i) {
    return (i - 1 + a.size()) % a.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        {
            int N;
            cin >> N;
            a.resize(N);
            rep(i, N) cin >> a[i];
        }

        bool uni = false;
        rep(i, a.size()) {
            if (a[prv(i)] != a[nxt(i)] && prv(i) != nxt(i)) uni = true;
        }
        int ans = a.size();
        if (!uni && ans > 2) ans = (ans - 2) / 2 + 2;

        cout << ans << "\n";
    }
}
