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
string s;
vector<int> swapl, swapr;

int find(char c, int i, int d) {
    while (i >= 0 && i < N && s[i] != c) i += d;
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> s;
        int i = 0, j = N - 1;
        swapl.clear(), swapr.clear();
        while (true) {
            i = find('1', i, 1), j = find('0', j, -1);
            if (i >= j) break;
            swapl.push_back(i), swapr.push_back(j);
            i += 1, j -= 1;
        }
        if (swapl.empty()) {
            cout << "0\n";
        } else {
            cout << "1\n" << swapl.size() * 2 << " ";
            rep(i, swapl.size()) cout << swapl[i] + 1 << " ";
            invrep(i, swapr.size()) cout << swapr[i] + 1 << " \n"[i == 0];
        }
    }
}
