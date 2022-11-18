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

        vector<int> s(N), p(N);
        rep(i, N) cin >> s[i];

        int i = 0;
        bool ok = true;
        while (i < N) {
            int j = i;
            while (j < N && s[j] == s[i]) j++;
            if (j - i == 1) ok = false;
            repx(k, i, j - 1) p[k] = k + 1;
            p[j - 1] = i;
            i = j;
        }

        if (ok) {
            rep(i, N) cout << p[i] + 1 << " \n"[i == N - 1];
        } else {
            cout << "-1\n";
        }
    }
}
