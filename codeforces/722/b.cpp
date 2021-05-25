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

int as[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int n;
        cin >> n;
        int lez = 0;
        rep(i, n) {
            cin >> as[i];
            if (as[i] <= 0) {
                lez += 1;
            }
        }
        sort(as, as + n);
        int last = as[0];
        int mindiff = -1;
        rep(i, 1, lez) {
            if (mindiff == -1 || as[i] - last < mindiff) {
                mindiff = as[i] - last;
            }
            last = as[i];
        }
        int count = lez;
        if (lez < n && (mindiff == -1 || as[lez] <= mindiff)) {
            count += 1;
        }
        cout << count << '\n';
    }
}
