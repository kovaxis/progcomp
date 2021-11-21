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

int P;
int prof[6];
int total[6];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> P;
    rep(i, P) {
        rep(j, 6) prof[j] = 0;
        int C;
        cin >> C;
        rep(j, C) {
            char grade;
            cin >> grade;
            int g = grade - 'A';
            prof[g] += 1;
            total[g] += 1;
        }
        rep(g, 6) cout << (char)('A' + g) << ":" << prof[g] << " \n"[g == 5];
    }
    cout << "TOTAL: ";
    rep(g, 6) cout << (char)('A' + g) << ":" << total[g] << " \n"[g == 5];
}
