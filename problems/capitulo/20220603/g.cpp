#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int A, B;
string a, b;

vector<int> fw, bk;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b;
    A = a.size(), B = b.size();
    fw.resize(B + 1), bk.resize(B + 1);

    fw[0] = 0;
    repx(j, 1, B + 1) {
        int x = fw[j - 1];
        while (x < A && a[x] != b[j - 1]) x += 1;
        fw[j] = x;
    }

    bk[B] = A;
    invrep(j, B) {
        int x = max(-1, bk[j] - 1);
        while (x >= 0 && a[x] != b[j]) x -= 1;
    }

    int ans = 1e9, l, r;
    rep(j1, B + 1) {
        int i1 = fw[j1];
        int i2 = lower_bound(bk.begin(), bk.end(), i1) - bk.begin();
        if (i2 < i1) continue;
        int rem = i2 - i1;
        if (rem < ans) {
            ans = rem;
            l =
        }
    }
}
