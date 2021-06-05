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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    vector<int> avail;
    avail.reserve(1001);
    rep(t, ts) {
        avail.clear();
        int n;
        cin >> n;
        rep(i, n) {
            int val;
            cin >> val;
            if (val == 1) {
                avail.push_back(1);
            } else {
                while (avail.back() != val - 1) avail.pop_back();
                avail.back() = val;
            }
            bool first = true;
            for (int v : avail) {
                if (first) {
                    first = false;
                } else {
                    cout << '.';
                }
                cout << v;
            }
            cout << '\n';
        }
    }
}
