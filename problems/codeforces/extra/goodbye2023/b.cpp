#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll A, B;
        cin >> A >> B;
        ll X = A / __gcd(A, B) * B;
        if (X == B) {
            ll K;
            repx(k, 2, B + 1) {
                if (B % k == 0) {
                    K = k;
                    break;
                }
                if ((ll)k * k > B) {
                    K = B;
                    break;
                }
            }
            X *= K;
        }
        cout << X << "\n";
    }
}
