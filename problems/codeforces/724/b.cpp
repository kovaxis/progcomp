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

typedef long long ll;

int n;
string s;
string mex;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        cin >> n;
        cin >> s;

        mex.clear();
        bool found = false;
        while (!found) {
            mex.push_back('a');
            while (true) {
                if (s.find(mex) == string::npos) {
                    found = true;
                    break;
                }
                int pos = mex.size() - 1;
                while (pos >= 0) {
                    mex[pos] += 1;
                    if (mex[pos] > 'z') {
                        mex[pos] = 'a';
                        pos -= 1;
                    } else {
                        break;
                    }
                }
                if (pos < 0) break;
            }
        }
        cout << mex << '\n';
    }
}
