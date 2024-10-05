#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> A;

ll solve(int I, int P, ll S) {
    int ac = I / 3;
    I -= ac * 3;
    P += ac;
    S -= ac;

    if (I == 2) {
        I -= 2;
        P += 1;
    }
    if (I == 0) {
        // just join pairs
    } else {
        // I == 1
        if (P >= 1) S -= 1;
    }
    return S;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        ll S = 0;
        int I = 0, P = 0;
        rep(i, N) {
            S += A[i];
            if (A[i] % 2) I += 1;
            else P += 1;
            cout << solve(I, P, S) << " ";
        }
        cout << "\n";
    }
}
