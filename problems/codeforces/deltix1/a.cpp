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

string s;
int dist[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    s.reserve(1001);
    rep(t, ts) {
        int n, m;
        cin >> n >> m;
        s.clear();
        cin >> s;
        int distl = 2000000000;
        rep(i, n) {
            if (s[i] == '1') {
                distl = 0;
            }
            dist[i] = distl;
            distl += 1;
        }
        int distr = 2000000000;
        invrep(i, n) {
            if (s[i] == '1') {
                distr = 0;
            }
            if (dist[i] > 0 && dist[i] == distr) {
                dist[i] = 2000000000;
            } else {
                dist[i] = min(dist[i], distr);
            }
            distr += 1;
        }
        rep(i, n) {
            char out = dist[i] <= m ? '1' : '0';
            cout << out;
        }
        cout << '\n';
    }
}
