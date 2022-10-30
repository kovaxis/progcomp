// floor(log2(n)) without precision loss
inline int floor_log2(int n) { return n <= 1 ? 0 : 31 - __builtin_clz(n); }
// ceil(log2(n)) without precision loss
inline int ceil_log2(int n) { return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }

inline ll floordiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0));
}

inline ll ceildiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0)) + 1;
}

// binary exponentiation
ll binexp(ll a, ll m) {
    ll res = 1;  // neutral element
    while (m) {
        if (m & 1) res = res * a;  // multiplication
        a = a * a;                 // multiplication
        m >>= 1;
    }
    return res;
}

// counts the divisors of a positive integer in O(sqrt(n))
ll count_divisors(ll x) {
    ll divs = 1;
    ll i = 2;
    while (x > 1) {
        if (i * i > x) {
            divs *= 2;
            break;
        }
        int n = 1;
        while (x % i == 0) {
            x /= i;
            n += 1;
        }
        divs *= n;
        i += 1;
    }
    return divs;
}

// gets the prime factorization of a number in O(sqrt(n))
void factorize(vector<pair<ll, int>>& facts, ll x) {
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            facts.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) facts.push_back({k, n});
        k += 1;
    }
}

// iterate over all divisors of a number.
//
// divisor count upper bound: n^(1.07 / ln ln n)
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