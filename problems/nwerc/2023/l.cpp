#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;

bool hit(int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= N) return false;
    cout << i+1 << " " << j+1 << endl;
    string status;
    cin >> status;
    if (status == "sunk") {
        K -= 1;
        if (K == 0) exit(0);
    }
    return status != "miss";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    rep(i, N) rep(j, N) {
        if (((i - j) % 5 + 5) % 5 == 0) {
            if (hit(i, j)) {
                repx(k, 1, 5) {
                    hit(i+k, j);
                    hit(i-k, j);
                    hit(i, j+k);
                    hit(i, j-k);
                }
            }
        }
    }
}
