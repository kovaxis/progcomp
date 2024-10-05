#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<ll> A;
vector<int> B;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    A.resize(4);
    rep(i, 4) {
        cin >> A[i];
    }

    B.resize(4);
    rep(i, 4) B[i] = i;
    do {
        ll s = A[B[0]] + A[B[1]] - A[B[2]] - A[B[3]];
        if (s == 0) {
            cout << "YES" << endl;
            return 0;
        }
    } while (next_permutation(B.begin(), B.end()));
    cout << "NO" << endl;
}
