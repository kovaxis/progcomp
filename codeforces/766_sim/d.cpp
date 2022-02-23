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

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

ll HMOD = 1000003931;
vector<ll> p;

void init_p(int N) {
    static const ll P =
        chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
    p.resize(N);
    p[0] = 1;
    rep(i, 1, N) p[i] = p[i - 1] * P % HMOD;
}

// factorize all numbers and find all primes under `N` in O(N)
void factor_sieve(vector<ll>& fc, vector<ll>& pr, int N) {
    fc.assign(N, 0), pr.clear();
    rep(n, 2, N) {
        if (fc[n] == 0) fc[n] = n, pr.push_back(n);
        for (ll p : pr) {
            if (p > fc[n] || n * p >= N) break;
            fc[n * p] = p;
        }
    }
}

vector<ll> fc, pr;
void factorize(vector<pair<ll, int>>& facts, ll x) {
    while (x != 1) {
        if (!facts.empty() && facts.back().first == fc[x])
            facts.back().second += 1;
        else
            facts.push_back({fc[x], 1});
        x /= fc[x];
    }
}

// iterate over all divisors of a number.
//
// divisor count upper bound: n^(1.07 / ln(ln n))
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    init_p(1e6 + 1);
    uset<ll> present;
    umap<ll, ll> divs, highest;
    factor_sieve(fc, pr, 1e6 + 1);
    vector<pair<ll, int>> facts;
    vector<int> f;
    rep(l, N) {
        ll x;
        cin >> x;
        facts.clear();
        factorize(facts, x);

        f.assign(facts.size(), 0);
        highest.clear();
        while (true) {
            ll y = 1;
            rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
            highest[divs[y]] = max(highest[divs[y]], y);

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

        for (auto y : highest) {
            // cerr << "adding " << y.second << endl;
            present.insert(y.second);
        }

        while (true) {
            ll y = 1;
            rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
            divs[y] += p[x];
            divs[y] %= HMOD;

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

    cout << present.size() - N << "\n";
}
