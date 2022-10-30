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

uint64_t splitmix64(uint64_t* x) {
    uint64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}
struct Hash {
    size_t operator()(const int& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

template <class T, class U>
using umap = unordered_map<T, U, Hash>;

int M, X, Y, K;
vector<int> grades;

umap<ll, int> dpmem;

// up_to, selected, max_consecutive
// max_score
int dp(int n, int y, int k) {
    if (y < 0) return INT32_MIN;
    if (k < 0) return INT32_MIN;
    if (n == 0) return y == 0 ? 0 : INT32_MIN;

    ll code = (ll)n * (Y + 1) * (K + 1) + (ll)y * (K + 1) + (ll)k;
    if (dpmem.count(code)) return dpmem[code];

    int suby_donttake = y, suby_take = y - 1;
    if (n % X == 1 && n > 1) suby_donttake = Y, suby_take = Y;
    int score = max(dp(n - 1, suby_donttake, K),
                    dp(n - 1, suby_take, k - 1) + grades[n - 1]);
    cerr << "upto = " << n << ", selecting = " << y << ", consecutive = " << k
         << ": " << score << "\n";
    return dpmem[code] = score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> M >> X >> Y >> K;
        grades.resize(M * X);
        rep(i, M * X) cin >> grades[i];
        dpmem.clear();
        int ans = dp(M * X, Y, K);
        if (ans < 0)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << "\n";
    }
}
