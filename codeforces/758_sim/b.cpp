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

vector<int> perm;

bool solve() {
    int N, A, B;
    cin >> N >> A >> B;
    if (abs(A - B) > 1) return false;
    if (A + B > max(N - 2, 0)) return false;

    perm.resize(N);
    perm[0] = 0;
    int mn = 0, mx = 0;
    bool up = A > B;
    rep(i, 1, N) {
        bool flip = A > 0 || B > 0;
        if (up)
            perm[i] = ++mx, A--;
        else
            perm[i] = --mn, B--;
        if (flip) up = !up;
    }

    rep(i, N) perm[i] -= mn - 1;
    assert(mx - mn + 1 == N);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        if (!solve()) {
            cout << "-1\n";
            continue;
        }
        rep(i, perm.size()) cout << perm[i] << " \n"[i == perm.size() - 1];
    }
}
