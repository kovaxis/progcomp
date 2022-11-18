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

    string s;

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;

        cout << (N + 1) / 2 << "\n";
        rep(k, (N + 1) / 2) {
            int i = k * 3;
            int j = (N - k) * 3 - 1;
            cout << i + 1 << " " << j + 1 << "\n";
        }
    }
}
