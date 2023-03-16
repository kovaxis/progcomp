#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    double a;
    cin >> a;
    // 2*pi*r = ans
    // pi * r^2 = a
    double r = sqrt(a / M_PI);
    cout << fixed << setprecision(9) << 2 * M_PI * r << endl;
}