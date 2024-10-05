#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
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

ll digithash(ll x) {
    int cnt[10];
    rep(k, 10) cnt[k] = 0;
    while (x) {
        cnt[x % 10] += 1;
        x /= 10;
    }
    ll h = 0, m = 1;
    rep(k, 10) {
        h += cnt[k] * m;
        m *= 100;
    }
    return h;
}

int numlen(ll x) {
    int len = 0;
    while (x) {
        x /= 10;
        len += 1;
    }
    return len;
}

umap<ll, vector<ll>> bylen[16];
ll bestbylen[16];

void solve(int N) {
    // find N numbers
    repx(k, 1, 16) {
        if (k % 2 != N % 2) continue;
        if (k > N) continue;
        if (bestbylen[k] == 0) continue;
        vector<ll> &nums = bylen[k][bestbylen[k]];
        if (nums.size() < N) continue;

        int c = 0;
        for (ll x : nums) {
            c += 1;
            if (c > N) break;
            cout << x;
            rep(l, N - k) cout << "0";
            cout << "\n";
        }
        return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // find squares with the same hash
    repx(k, 1, 500001) {
        ll kk = (ll)k * k;
        bylen[numlen(kk)][digithash(kk)].push_back(kk);
    }
    rep(l, 16) {
        for (auto &[h, ns] : bylen[l]) {
            if (bestbylen[l] == 0 || bylen[l][bestbylen[l]].size() < ns.size()) {
                bestbylen[l] = h;
            }
        }
    }

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        solve(N);
    }
}
