#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> a(N);
    repx(i, 1, N) cin >> a[i];

    int need = 1;
    double ans = 0.;
    rep(i, N) {
        need -= a[i];
        if (need <= 0) break;
        cerr << "i need " << need << " A" << i + 1 << " paper, using "
             << need * pow(2., -3. / 4. - i * 2. / 4.)
             << "m of tape to make them" << endl;
        ans += need * pow(2., -3. / 4. - i * 2. / 4.);

        need *= 2;
    }

    if (need <= 0)
        cout << fixed << setw(11) << setprecision(11) << ans << endl;
    else
        cout << "impossible\n";
}
