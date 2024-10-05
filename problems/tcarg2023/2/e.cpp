#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;

bool can1(ll l, int n, vector<ll> &A, ll m) {

    ll now = 0;
    for (int i = 0; i < n; i++) {
        if (now > A[i]) {
            return false;
        }
        now = max(A[i], now + m);
    }

    if (now > l) {
        return false;
    }

    return true;
}

bool can2(ll l, int n, vector<ll> &A, ll L, ll diff) {

    ll inf = 0;
    ll sup = 0;
    for (int i = 0; i < n; i++) {
        if (sup + L + diff < A[i]) {
            return false;
        }
        inf = max(A[i], inf + L);
        if (i == n - 1) {
            sup = min(l, sup + L + diff);
        } else {
            sup = min(A[i + 1], sup + L + diff);
        }
        if (inf > sup) {
            return false;
        }
    }

    if (sup != l) {
        return false;
    }

    return true;
}

int main() {

    ll l, n;
    cin >> l >> n;

    vector<ll> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    ll inf = 0;
    ll sup = 1000000100;

    while (inf != sup) {
        ll m = (inf + sup + 1) / 2;
        if (can1(l, n, A, m) == true) {
            inf = m;
        } else {
            sup = m - 1;
        }
    }

    ll L = inf;

    inf = 0;
    sup = 1000000100;

    while (inf != sup) {
        ll m = (inf + sup) / 2;
        if (can2(l, n, A, L, m) == true) {
            sup = m;
        } else {
            inf = m + 1;
        }
    }

    ll diff = inf;
    vector<ii> res(n);
    vector<ll> cuanto(n, 0);
    for (int i = 1; i < n; i++) {
        cuanto[i - 1] = A[i] - i * L;
    }
    cuanto[n - 1] = l - n * L;

    vector<ll> mini(n, l - n * L);
    for (int i = n - 2; i >= 0; i--) {
        mini[i] = min(mini[i + 1], cuanto[i]);
    }
    ll sum = 0;
    ll before = 0;
    for (int i = 0; i < n; i++) {
        res[i].first = before;
        before = before + L + min(diff, max(0LL, mini[i] - sum));
        res[i].second = before;
        sum = sum + min(diff, max(0LL, mini[i] - sum));
    }

    for (auto u : res) {
        cout << u.first << " " << u.second << "\n";
    }
    // dasdasfsd
    return 0;
}