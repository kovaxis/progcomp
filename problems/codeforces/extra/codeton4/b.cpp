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
        int N;
        cin >> N;

        if (N % 2 == 0) {
            cout << "-1\n";
            continue;
        }
        N >>= 1;

        vector<bool> bits;
        while (N) {
            bits.push_back(N & 1);
            N >>= 1;
        }
        reverse(bits.begin(), bits.end());

        cout << bits.size() << "\n";
        rep(i, bits.size()) cout << bits[i] + 1 << " \n"[i == bits.size() - 1];
    }
}
