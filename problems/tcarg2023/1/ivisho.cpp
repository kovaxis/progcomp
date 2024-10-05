#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    ll n, m;
    cin >> n >> m;

    vector<ll> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    ll res = min(m, A[n - 1]);
    ll ahora = min(m, A[n - 1]);
    for (ll i = n - 2; i >= 0; i--) {
        res = res + min(ahora - 1, A[i]);
        ahora = min(ahora - 1, A[i]);
        if (ahora <= 0) {
            res = 0;
            break;
        }
    }

    for (ll k = 2; k <= m / n; k++) {
        // for(ll k = 3; k<=3; k++){
        vector<ll> B(n, 0);
        ll now = k * m - n * k * (k - 1LL) / 2LL + k;
        ll sum = 0;
        ll where = 0;
        for (ll i = n - 1; i >= 0; i--) {
            if (A[i] < now - k) {
                B[i] = now - k - A[i];
            }
            now = min(A[i], now - k);
            sum = sum + B[i];
        }
        if (now < k + n * k * (k - 1LL) / 2LL) {
            continue;
        }
        // A[n-1] = min(A[n-1], m);
        // for(int i = n-2; i>=0; i--){
        //     A[i] = min(A[i], A[i+1] - k);
        // }
        // for(auto u: B){
        //     cout<<u<<" ";
        // }
        // cout<<endl;
        ll cero = max(1LL, m - n + 1 - (k - 1) * n - sum);
        ll diff = m - cero - (k - 1) - k * (n - 1);
        ll resx = now;
        // cout<<diff<<endl;
        ll aux = B[0];
        for (int i = 1; i < n; i++) {
            now = now + k;
            ll delta = min(A[i] - now, min(aux, diff));
            // cout<<i<<" "<<delta<<endl;
            now = now + delta;
            diff = diff - delta;
            aux = aux - delta;
            resx = resx + now;
            aux = aux + B[i];
        }
        res = max(res, resx);
    }

    cout << res << endl;

    return 0;
}