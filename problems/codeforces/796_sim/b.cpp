#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M, cur;
string s;
vector<pair<int, int>> len;

int ask(const string& s) {
    cout << "? " << s << endl;
    int x;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    len.resize(M);
    s.assign(M, '0');

    rep(i, M) {
        s[i] = '1';
        len[i] = {ask(s), i};
        s[i] = '0';
    }

    sort(len.begin(), len.end());
    int y = 0;
    for (auto [l, i] : len) {
        s[i] = '1';
        int x = ask(s);
        if (x - y == l) {
            // in minimum spanning forest
            y = x;
        } else {
            // not in spanning forest
            s[i] = '0';
        }
    }

    cout << "! " << y << endl;
}
