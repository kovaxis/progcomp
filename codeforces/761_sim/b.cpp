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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> primes = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,
                          31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
                          73,  79,  83,  89,  97,  101, 103, 107, 109, 113,
                          127, 131, 137, 139, 149, 151, 157, 163, 167, 173};

    int T;
    cin >> T;
    rep(t, T) {
        int N;
        cin >> N;
        int a, b, c = 0;
        for (int p : primes) {
            if (N - p - 1 <= 0) break;
            if (N % p != 1) {
                a = p, b = N - p - 1, c = 1;
                break;
            }
        }
        assert(c);
        cout << a << " " << b << " " << c << "\n";
    }
}
