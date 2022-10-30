#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll N, K;
        cin >> N >> K;
        string s;
        cin >> s;

        if (s[N - 1] == '0') {
            invrep(i, N) if (s[i] == '1' && K >= N - i - 1) {
                repx(j, i, N - 1) {
                    swap(s[j], s[j + 1]);
                    K -= 1;
                }
                break;
            }
        }
        if (s[0] == '0') {
            rep(i, N - 1) if (s[i] == '1' && K >= i) {
                invrep(j, i) {
                    swap(s[j], s[j + 1]);
                    K -= 1;
                }
                break;
            }
        }

        ll f = 0;
        rep(i, N - 1) f += (s[i] - '0') * 10 + (s[i + 1] - '0') * 1;

        // cerr << '"' << s << '"' << " = " << f << endl;
        cout << f << "\n";
    }
}
