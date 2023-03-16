#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, L, k;
    cin >> n >> L >> k;
    vector<double> Pm(n + 1), Px(n + 1);

    rep(i, n + 1) Pm[i] = pow((double)i / (double)n, (double)k);
    for (int i = n; i >= 1; i--) Pm[i] -= Pm[i - 1];

    double acc = 0;
    for (int i = n; i >= L; i--) {
        acc += Pm[i] / (double)i;
        Px[i] = acc;
    }
    for (int i = L - 1; i >= 1; i--)
        Px[i] = Px[i + 1];
    for (int i = L - 1; i >= 1; i--)
        Px[L] += Pm[i];

    double resp = 0;
    repx(i, 1, n + 1) resp += Px[i] * i;
    cout << fixed << setprecision(10) << resp << endl;
}
