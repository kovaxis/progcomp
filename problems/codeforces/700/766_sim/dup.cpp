#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

vector<int> a;
vector<bool> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];
    int A = 0;
    rep(i, N) A = max(A, a[i] + 1);
    b.assign(A, false);
    rep(i, N) b[a[i]] = true;
    int reach = 0;
    rep(n, 1, A) {
        int g = 0;
        for (int m = n; m < A; m += n) {
            if (b[m]) g = __gcd(g, m);
        }
        if (g == n) reach += 1;
    }
    cout << reach - N << endl;
}
