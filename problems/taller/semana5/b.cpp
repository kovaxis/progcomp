#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

bool find_seq(int* ns, int* as, bool* avail, int k, int idx) {
    rep(i, 10) {
        if (avail[i]) {
            as[idx] = i;
            int subk = k - i * ns[idx];
            if (subk >= 0) {
                int subidx = idx + 1;
                if (subidx >= 10) {
                    return true;
                }
                avail[i] = false;
                if (find_seq(ns, as, avail, subk, subidx)) {
                    return true;
                }
                avail[i] = true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin >> tests;
    rep(test, tests) {
        int ns[10];
        int as[10];
        bool avail[10];
        rep(i, 10) {
            cin >> ns[i];
            avail[i] = true;
        }
        int k;
        cin >> k;
        if (find_seq(ns, as, avail, k, 0)) {
            rep(i, 10) {
                if (i > 0) {
                    cout << " ";
                }
                cout << as[i];
            }
            cout << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
