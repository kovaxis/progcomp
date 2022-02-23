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

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int N;
vector<int> a, pt, order;

template <class OP>
bool ispali(OP incl) {
    int n = 0;
    rep(i, N) if (incl(a[i])) pt[n++] = a[i];
    if (n == 0) return true;
    int c = n - 1;
    for (int d = c % 2; c - d >= 0 && c + d < 2 * n; d += 2) {
        int l = (c - d) / 2, r = (c + d) / 2;
        if (pt[l] != pt[r]) return false;
    }
    return true;
}

void shuffle(int n) {
    int i = 0;
    while (++i < n) {
        uniform_int_distribution<int> distr(i, n - 1);
        int x = distr(rng);
        swap(order[i - 1], order[x]);
    }
}

int findwronger(int n) {
    shuffle(n);
    static vector<int> invorder;
    invorder.assign(N, 0);
    rep(i, n) invorder[order[i] - 1] = i + 1;
    int l = 1, r = n;
    while (l != r) {
        int m = (l + r) / 2;
        if (ispali([&](int x) { return invorder[x - 1] <= m; })) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N), pt.resize(N), order.resize(N);
        rep(i, N) cin >> a[i];

        rep(i, N) order[i] = i + 1;
        int m = N;
        while (m > 1) {
            int nm = findwronger(m);
            if (nm == m) break;
            m = nm;
        }
        int ans = order[m - 1];

        if (ispali([&](int x) { return x != ans; })) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
