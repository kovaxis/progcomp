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

int win[2];
set<int> possible_k;

void check_ks(int start) {
    int space[2];
    space[0] = (win[0] + win[1] + 1) / 2;
    space[1] = win[0] + win[1] - space[0];
    if (start) swap(space[0], space[1]);
    int sidx = 0;
    if (win[1] < win[0]) sidx = 1;
    // cerr << "placing " << win[sidx] << " into a slot of size " << space[sidx]
    //     << ", vs a slot of size " << space[!sidx] << '\n';
    rep(i, win[sidx] + 1) {
        int k = i + space[!sidx] - (win[sidx] - i);
        possible_k.insert(k);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        possible_k.clear();
        cin >> win[0] >> win[1];
        rep(i, 2) check_ks(i);
        int n = possible_k.size();
        cout << n << '\n';
        for (int k : possible_k) cout << k << "\n "[--n != 0];
    }
}
