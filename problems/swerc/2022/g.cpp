#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    string s;
    cin >> s;

    int acc = 0;
    rep(i, N) acc += s[i] == 'W';

    vector<int> moving(N);
    rep(i, N) {
        moving[i] = acc;
        // cerr << "window " << i << " has " << acc << " white wines" << endl;
        acc += s[N + i] == 'W';
        acc -= s[i] == 'W';
    }

    int mx = 0;
    rep(i, N) mx = max(mx, moving[i]);
    cout << mx << endl;
}