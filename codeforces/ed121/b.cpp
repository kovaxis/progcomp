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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        for (char& c : s) c -= '0';
        int idx = 1;
        invrep(i, 1, s.size()) {
            int sum = s[i] + s[i - 1];
            if (sum >= 10) {
                idx = i;
                break;
            }
        }
        int sum = s[idx] + s[idx - 1];
        if (sum >= 10) {
            s[idx - 1] = sum / 10;
            s[idx] = sum % 10;
        } else {
            s.erase(s.begin() + idx);
            s[idx - 1] = sum;
        }
        for (char& c : s) c += '0';
        cout << s << "\n";
    }
}
