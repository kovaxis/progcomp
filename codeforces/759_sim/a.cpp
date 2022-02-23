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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N, h = 1, w = false, dead = false;
        cin >> N;
        rep(i, N) {
            int tw;
            cin >> tw;
            if (tw && w) h += 5;
            if (tw && !w) h += 1;
            if (!tw && w)
                ;
            if (!tw && !w && i != 0) dead = true;
            w = tw;
        }
        if (dead)
            cout << "-1\n";
        else
            cout << h << "\n";
    }
}
