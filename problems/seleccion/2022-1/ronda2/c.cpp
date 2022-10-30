#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int ask(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int i;
    cin >> i;
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    int x = ask(1, N), y;
    if (x != 1 && ask(1, x) == x) {
        // in first "half"
        int l = 1, r = x - 1;
        while (l != r) {
            int m = (l + r + 1) / 2;
            if (ask(m, x) == x) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        y = l;
    } else {
        // in second "half"
        int l = x + 1, r = N;
        while (l != r) {
            int m = (l + r) / 2;
            if (ask(x, m) == x) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        y = l;
    }
    cout << "! " << y << endl;
}
