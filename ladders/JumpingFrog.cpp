#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

// gets the prime factorization of a number in O(sqrt(n))
void factorize(vector<pair<ll, int>>& facts, ll x) {
    ll i = 2;
    while (x > 1) {
        if (i * i > x) {
            facts.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % i == 0) x /= i, n++;
        if (n > 0) facts.push_back({i, n});
        i += 1;
    }
}

// iterate over all divisors of a number.
template <class OP>
void divisors(ll x, OP op) {
    vector<pair<ll, int>> facts;
    factorize(facts, x);
    vector<int> f(facts.size());
    while (true) {
        ll y = 1;
        rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
        op(y);

        int i = 0;
        while (i < f.size()) {
            f[i] += 1;
            if (f[i] > facts[i].second)
                f[i++] = 0;
            else
                break;
        }
        if (i == f.size()) break;
    }
}

string ring;
int N;
map<int, bool> safedivs;

void checkdiv(ll d) {
    static vector<bool> dponds;
    dponds.assign(d, false);
    rep(i, N) dponds[i % d] = dponds[i % d] || ring[i] == 'P';
    bool anysafe = false;
    for (bool pond : dponds) anysafe = anysafe || !pond;
    safedivs[d] = anysafe;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> ring) {
        N = ring.size();
        safedivs.clear();
        divisors(N, checkdiv);
        int safe = 0;
        rep(k, 1, N) safe += safedivs[__gcd(k, N)];
        cout << safe << "\n";
    }
}
