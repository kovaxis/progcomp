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

int N;
vector<bool> status;

// 0 -> impostor
// 1 -> crewmate
int ask(int i, int j, int k) {
    cout << "? " << i + 1 << " " << j + 1 << " " << k + 1 << endl;
    int x;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        status.resize(N);
        int grp[2];
        for (int i = 0; i < N; i += 3) grp[ask(i, i + 1, i + 2)] = i;

        int repr[2];
        rep(i, 3) {
            bool done = false;
            rep(j, 3) {
                int other[2], n = 0;
                rep(m, 3) {
                    if (m == j) continue;
                    other[n++] = m;
                }
                int a = ask(grp[0] + i, grp[1] + other[0], grp[1] + other[1]);
                if (!a) repr[0] = grp[0] + i, done = true;
                if (a) repr[1] = grp[1] + other[0];
            }
            if (done) break;
        }

        status[repr[0]] = 0;
        status[repr[1]] = 1;
        rep(i, N) {
            if (i == repr[0]) continue;
            if (i == repr[1]) continue;
            status[i] = ask(repr[0], repr[1], i);
        }

        int k = 0;
        rep(i, N) k += !status[i];
        cout << "! " << k;
        rep(i, N) if (!status[i]) cout << " " << i + 1;
        cout << endl;
    }
}
