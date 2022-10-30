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
    string s;
    rep(t, T) {
        int N;
        cin >> N >> s;
        int zeropos = -1;
        rep(i, N) if (s[i] == '0') {
            zeropos = i;
            break;
        }
        if (zeropos == -1) {
            cout << "1 " << N - 1 << " 2 " << N << "\n";
        } else if (zeropos < N / 2) {
            cout << zeropos + 1 << " " << N << " " << zeropos + 2 << " " << N
                 << "\n";
        } else {
            cout << "1 " << zeropos + 1 << " 1 " << zeropos << "\n";
        }
    }
}
