#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> D, R, O, P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    D.resize(N), R.resize(N), O.resize(N);
    rep(i, N) {
        string s;
        cin >> s;
        for (char c : s) {
            D[i] += (c == '(' ? 1 : -1);
            R[i] = min(R[i], D[i]);
        }
        R[i] *= -1;
        if (D[i] < 0) {
            int x = 0;
            invrep(j, (int)s.size()) {
                x += (s[j] == ')' ? 1 : -1);
                O[i] = min(O[i], x);
            }
        } else {
            O[i] = R[i];
        }
    }

    P.resize(N);
    rep(i, N) P[i] = i;
    sort(P.begin(), P.end(), [](int i, int j) {
        if ((D[i] < 0) != (D[j] < 0)) return D[i] >= 0;
        return O[i] < O[j];
    });

    int s = 0;
    for (int i : P) {
        if (s < R[i]) {
            cout << "impossible" << endl;
            return 0;
        }
        s += D[i];
    }
    if (s != 0) {
        cout << "impossible" << endl;
        return 0;
    }

    for (int i : P) {
        cout << i + 1 << "\n";
    }
}
