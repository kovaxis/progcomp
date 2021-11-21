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

string s;

const char* singles = "0100101011";

int reduce() {
    int j = 0;
    int counts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    rep(i, s.size()) {
        counts[s[i] - '0'] += 1;
        if (singles[s[i] - '0'] == '1') {
            s[0] = s[i];
            return 1;
        } else {
            s[j++] = s[i];
        }
    }
    s.resize(j);
    rep(i, 1, 10) {
        if (counts[i] >= 2) {
            s[0] = '0' + i;
            s[1] = '0' + i;
            return 2;
        }
    }
    if (counts[2] != 0 && s[0] != '2') {
        s[1] = '2';
        return 2;
    }
    if (counts[5] != 0 && s[0] != '5') {
        s[1] = '5';
        return 2;
    }
    if (counts[7] != 0 && (s[0] == '2' || s[0] == '5')) {
        s[1] = '7';
        return 2;
    }
    assert(false);
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N;
        cin >> N >> s;
        int num = reduce();
        s.resize(num);
        cout << s.size() << '\n' << s << '\n';
    }
}
