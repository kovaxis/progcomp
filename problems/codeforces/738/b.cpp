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

char btoc[2] = {'B', 'R'};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string s;
    rep(t, T) {
        int n;
        cin >> n >> s;
        int left = 0;
        while (left < n && s[left] == '?') left += 1;
        bool last = left < n ? s[left] == 'R' : 0;
        invrep(i, left) {
            last = !last;
            s[i] = btoc[last];
        }
        rep(i, left, n) {
            if (s[i] == '?') {
                last = !last;
                s[i] = btoc[last];
            } else {
                last = s[i] == 'R';
            }
        }
        cout << s << '\n';
    }
}