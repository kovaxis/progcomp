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

bool check(string& s) {
    bool seen[30];
    rep(i, 30) { seen[i] = false; }
    int last_idx = -1;
    for (char c : s) {
        int idx = c - 'A';
        if (idx != last_idx) {
            seen[last_idx] = true;
            last_idx = idx;
            if (seen[idx]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    string s;
    rep(t, ts) {
        int n;
        cin >> n >> s;
        if (check(s)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
