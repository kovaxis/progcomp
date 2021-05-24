#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    unordered_map<int, long long> repeat;
    rep(t, ts) {
        int n;
        cin >> n;
        repeat.clear();
        long long w = 0;
        rep(i, n) {
            int x;
            cin >> x;
            w += repeat[x] * ((long long)(n - i));
            repeat[x] += (long long)(i + 1);
        }
        cout << w << '\n';
    }
}
