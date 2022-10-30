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

int N;
vector<int> owner;
vector<vector<int>> adj;

struct bigint {
    vector<uint32_t> digits;

    bigint() {}
    bigint(ll x) : digits{lo(x), hi(x)} { this->trim(); }
    bigint(vector<uint32_t> d) : digits(d) {}

    static uint32_t lo(uint64_t dw) { return (uint32_t)dw; }
    static uint32_t hi(uint64_t dw) { return (uint32_t)(dw >> 32); }

    void trim() {
        while (this->digits.size() && this->digits.back() == 0)
            this->digits.pop_back();
    }

    void operator+=(const bigint& rhs) {
        uint32_t c = 0;
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) this->digits.push_back(0);
            uint64_t r =
                (uint64_t)this->digits[i] + (i < rs ? rhs.digits[i] : 0) + c;
            this->digits[i] = lo(r), c = hi(r);
        }
        if (c != 0) this->digits.push_back(c);
    }

    void operator-=(const bigint& rhs) {
        uint32_t c = 1;
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) this->digits.push_back(0);
            uint64_t r =
                (uint64_t)this->digits[i] + ~(i < rs ? rhs.digits[i] : 0) + c;
            this->digits[i] = lo(r), c = hi(r);
        }
        if (c != 1) this->digits.push_back(c);
    }

    void operator*=(const bigint& rhs) {
        bigint out;
        rep(j, this->digits.size()) {
            uint64_t c = 0;
            int ls = out.digits.size();
            int rs = rhs.digits.size();
            rep(i, j, max(ls, rs + j)) {
                if (i >= ls) out.digits.push_back(0);
                uint64_t r = (uint64_t)out.digits[i] +
                             (uint64_t)(i - j < rs ? rhs.digits[i - j] : 0) *
                                 this->digits[j] +
                             c;
                out.digits[i] = lo(r), c = hi(r);
            }
            if (c != 0) out.digits.push_back(c);
        }
        *this = out;
    }

    int cmp(const bigint& rhs) {
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        invrep(i, max(ls, rs)) {
            uint32_t l = i < ls ? this->digits[i] : 0;
            uint32_t r = i < rs ? rhs.digits[i] : 0;
            if (l < r)
                return -1;
            else if (l > r)
                return 1;
        }
        return 0;
    }

    bool operator==(const bigint& rhs) { return cmp(rhs) == 0; }
    bool operator!=(const bigint& rhs) { return cmp(rhs) != 0; }
    bool operator<(const bigint& rhs) { return cmp(rhs) == -1; }
    bool operator>=(const bigint& rhs) { return cmp(rhs) != -1; }
    bool operator>(const bigint& rhs) { return cmp(rhs) == 1; }
    bool operator<=(const bigint& rhs) { return cmp(rhs) != 1; }
};

bool find(int i, int p, int obj) {
    if (i == obj) return true;
    for (int child : adj[i]) {
        if (child == p) continue;
        if (find(child, i, obj)) return true;
    }
    return false;
}

int finddir(int i, int obj) {
    int c = -1;
    for (int child : adj[i]) {
        if (find(child, i, obj)) {
            assert(c == -1);
            c = child;
        }
    }
    assert(c != -1);
    return c;
}

// total dist, count
void query(int i, int p, int d, pair<ll, ll>* out) {
    out[owner[i]].first += d;
    out[owner[i]].second += 1;
    for (int child : adj[i]) {
        if (child == p) continue;
        query(child, i, d + 1, out);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    owner.resize(N);
    adj.resize(N);
    rep(i, N) cin >> owner[i];
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int Q;
    cin >> Q;
    rep(q, Q) {
        int op;
        cin >> op;
        if (op == 1) {
            // transaction
            int u;
            cin >> u;
            owner[u - 1] = !owner[u - 1];
        } else if (op == 2) {
            // comparison
            int u, v;
            cin >> u >> v;
            u--, v--;
            int uchild = finddir(u, v);
            int vchild = finddir(v, u);
            pair<ll, ll> pdists[2][2];
            rep(l, 2) rep(k, 2) pdists[k][l] = {0, 0};
            query(u, uchild, 0, pdists[0]);
            query(v, vchild, 0, pdists[1]);
            pair<ll, ll> dists[2];
            rep(l, 2) {
                // a/b + c/d
                // = (a*d + c*b) / (b*d)
                dists[l] = {pdists[0][l].first * pdists[1][l].second +
                                pdists[1][l].first * pdists[0][l].second,
                            pdists[0][l].second * pdists[1][l].second};
                if (dists[l].second == 0) dists[l].first = 1;
            }
            // a/b < c/d
            // <-> a*d < c*b
            bigint a = dists[0].first;
            a *= dists[1].second;
            bigint b = dists[1].first;
            b *= dists[0].second;
            if (a < b)
                cout << "A\n";
            else if (a > b)
                cout << "B\n";
            else
                cout << "TIE\n";
        }
    }
}
