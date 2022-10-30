#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N), b.resize(N);
        rep(i, N) cin >> a[i];
        sort(a.begin(), a.end());
        int l = 0, r = N, i = 0;
        while (l != r) {
            b[i++] = a[l++];
            if (l == r) break;
            b[i++] = a[--r];
        }
        invrep(i, N) cout << b[i] << " \n"[i == 0];
    }
}
