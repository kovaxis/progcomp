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

vector<int> a;
vector<pair<int, int>> ops;
vector<int> t;

void ins(int i, int x) {
    a.insert(a.begin() + i, x);
    a.insert(a.begin() + i, x);
    ops.push_back({i, x});
}

bool solve() {
    int i = 0;
    while (i < a.size()) {
        int x = a[i];
        int j = -1;
        rep(k, i + 1, a.size()) if (a[k] == x) j = k;
        if (j == -1) return false;
        rep(k, 1, j - i) ins(j + k, a[i + k]);
        t.push_back(2 * (j - i));

        i = j + (j - i);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        ops.clear();
        t.clear();
        if (solve()) {
            cout << ops.size() << "\n";
            for (auto op : ops) cout << op.first << " " << op.second << "\n";
            cout << t.size() << "\n";
            rep(i, t.size()) cout << t[i] << " \n"[i == t.size() - 1];
        } else {
            cout << "-1\n";
        }
    }
}
