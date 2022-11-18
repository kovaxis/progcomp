#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, Q;
vector<int> a, z;
vector<pair<pair<int, int>, int>> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    a.resize(N);
    z.resize(N);
    b.resize(Q);
    rep(q, Q) {
        int i, j, x;
        cin >> i >> j >> x;
        i--, j--;
        if (j < i) swap(i, j);
        b[q].first.first = i;
        b[q].first.second = j;
        b[q].second = x;
        z[i] |= ~x;
        z[j] |= ~x;
    }
    sort(b.begin(), b.end());
    for (auto p : b) {
        int i = p.first.first;
        int j = p.first.second;
        int x = p.second;
        rep(b, 30) {
            if (!((x >> b) & 1)) continue;
            if ((z[j] >> b) & 1) a[i] |= 1 << b;
        }
    }
    for (auto p : b) {
        int i = p.first.first;
        int j = p.first.second;
        int x = p.second;
        rep(b, 30) {
            if (!((x >> b) & 1)) continue;
            if ((a[i] >> b) & 1) continue;
            a[j] |= 1 << b;
        }
    }
    rep(i, N) cout << a[i] << " \n"[i == N - 1];
}
