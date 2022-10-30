#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
string out;

string s[3], u[3];
vector<int> p;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> out;
    N = out.size();
    p.resize(N);

    rep(j, 3) s[j].resize(N);
    rep(i, N) {
        int x = i;
        rep(j, 3) {
            s[j][i] = 'a' + (x % 26);
            x /= 26;
        }
    }

    rep(j, 3) {
        cout << "? " << s[j] << endl;
        cin >> u[j];
    }

    rep(i, N) {
        int x = 0;
        invrep(j, 3) {
            x *= 26;
            x += u[j][i] - 'a';
        }
        // cerr << i << " goes to " << x << endl;
        p[i] = x;
    }

    string og(N, ' ');
    rep(i, N) og[p[i]] = out[i];
    cout << "! " << og << endl;
}
