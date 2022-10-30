#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cout << "Case #" << t + 1 << ":" << endl;
        int R, C;
        cin >> R >> C;
        cout << ".";
        rep(j, C) {
            cout << (j == 0 ? "." : "-");
            cout << "+";
        }
        cout << "\n";
        rep(i, R) {
            cout << (i == 0 ? "." : "|");
            rep(j, C) { cout << ".|"; }
            cout << "\n"
                 << "+";
            rep(j, C) cout << "-+";
            cout << "\n";
        }
    }
}
