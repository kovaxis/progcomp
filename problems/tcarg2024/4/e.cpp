#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct P {
    ll x, y;

    friend istream &operator>>(istream &s, P &p) {
        return s >> p.x >> p.y;
    }
};

int N;
P d1, d2;

bool solve() {
    ll area = abs(d1.x * d2.y - d1.y * d2.x);
    if (area != N) return false;
    ll X = __gcd(abs(d1.x), abs(d2.x));
    ll Y = area / X;
    cout << "YES\n";
    rep(x, X) rep(y, Y) cout << x << " " << y << "\n";
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> d1 >> d2;
    if (!solve()) {
        cout << "NO\n";
    }
}
