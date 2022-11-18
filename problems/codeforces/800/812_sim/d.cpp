#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;

int ask(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    int x;
    cin >> x;
    int mp[3] = {0, -1, 1};
    return mp[x];
}

int solve(int i, int n) {
    if (n == 0) return i;
    int l, r;
    if (n % 2 == 0) {
        int sn = n - 2;
        int a = solve(i, sn);
        int b = solve(i + (1 << sn), sn);
        int c = solve(i + (2 << sn), sn);
        int d = solve(i + (3 << sn), sn);
        int x = ask(a, c);
        if (x == 0)
            l = b, r = d;
        else if (x == -1)
            l = a, r = d;
        else if (x == 1)
            l = b, r = c;
    } else {
        l = solve(i, n - 1);
        r = solve(i + (1 << (n - 1)), n - 1);
    }

    int x = ask(l, r);
    return x == -1 ? l : r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        int ans = solve(0, N);
        cout << "! " << ans + 1 << endl;
    }
}
