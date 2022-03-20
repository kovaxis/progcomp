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
int M;

vector<int> p10;
vector<vector<int>> digits;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> s) {
        cin >> M;
        int N = s.size() + 1;

        {
            p10.resize(N);
            p10[0] = 1;
            rep(i, 1, N) p10[i] = p10[i - 1] * 10 % M;
        }

        digits.assign(N, vector<int>(M, -1));

        digits[0][0] = 0;
        rep(i, 1, N) {
            char r = s[N - 1 - i];
            // cerr << "checking digit " << i << " = '" << r << "'" << endl;
            int d0, d1;
            if (r == '?') {
                d0 = 0, d1 = 9;
                if (i == N - 1) d0 = 1;
            } else {
                int d = r - '0';
                d0 = d1 = d;
            }
            rep(j, M) {
                // cerr << "  checking remainder = " << j << endl;
                rep(d, d0, d1 + 1) {
                    int x = p10[i - 1] * d % M;
                    int y = (j - x + M) % M;
                    // cerr << "    checking digit " << d << endl;
                    // cerr << "      corresponds to previous remainder " << y
                    // << endl;
                    if (digits[i - 1][y] != -1) {
                        digits[i][j] = d;
                        // cerr << "      accepted" << endl;
                        break;
                    }
                }
            }
        }

        string ans;
        int j = 0;
        invrep(i, 1, N) {
            int d = digits[i][j];
            // cerr << "visiting digit " << d << " at remainder " << j << endl;
            if (d == -1) {
                ans = "";
                break;
            }
            ans += '0' + d;
            int x = p10[i - 1] * d % M;
            int y = (j - x + M) % M;
            // cerr << "  going to remainder " << j << endl;
            j = y;
        }
        if (digits[0][j] == -1) ans = "";

        if (ans.empty()) {
            cout << "*\n";
        } else {
            cout << ans << "\n";
        }
    }
}
