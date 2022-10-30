
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

vector<ll> fib;
vector<ll> resp;
ll N;
unordered_set<ll> memo;
bool f(ll n) {
    if (n == 1) return true;
    if (memo.count(n)) return false;
    for (int i = fib.size() - 1; i >= 0; i--) {
        if (n % fib[i] == 0) {
            if (f(n / fib[i])) {
                resp.push_back(fib[i]);
                return true;
            }
        }
    }
    memo.insert(n);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    if (N == 1) {
        cout << "B" << endl;
        return 0;
    }
    ll f1 = 1, f2 = 1;
    unordered_map<ll, ll> m;
    int i = 0;
    while (true) {
        ll x = f1 + f2;
        f2 = f1, f1 = x;

        if (x > N) break;
        m[x] = i;
        i++;
        if (N % x == 0) fib.push_back(x);
    }

    if (f(N)) {
        for (int j = resp.size() - 1; j >= 0; j--) {
            for (ll i = 0; i <= m[resp[j]]; i++) {
                cout << "A";
            }
            cout << "B";
        }
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}