#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const int HC = 2;
const ll MOD[HC] = {1000001329, 1000002499};
vector<ll> Ppow[HC];
void Ppow_init(int N) {
    const ll P =
        chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
    rep(hc, HC) {
        Ppow[hc].resize(N);
        Ppow[hc][0] = 1;
        rep(i, N - 1) Ppow[hc][i + 1] = Ppow[hc][i] * P;
    }
}

struct Hash {
    int h[HC];

    Hash() {
        rep(hc, HC) h[hc] = 0;
    }

    void shl(int by) {
        rep(hc, HC) h[hc] = (ll)h[hc] * Ppow[hc][by] % MOD[hc];
    }

    void add(int x, int at) {
        rep(hc, HC) {
            int M = (int)MOD[hc];
            h[hc] = (h[hc] + (int)((x + M) % M * Ppow[hc][at] % M)) % M;
        }
    }

    bool operator==(const Hash &b) const {
        rep(hc, HC) if (h[hc] != b.h[hc]) return false;
        return true;
    }
};

// hackproof unordered map hash
struct Hasher {
    size_t operator()(const Hash &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = RAND + 0x9e3779b97f4a7c15;
        rep(hc, HC) {
            z += x.h[hc];
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            z = z ^ (z >> 31);
        }
        return z;
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hasher>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hasher>;

int N;
vector<vector<vector<pair<char, int>>>> tries;
umap<Hash, int> counts;

void dfs(int i, int u, Hash h) {
    counts[h] += 1;
    for (auto [c, v] : tries[i][u]) {
        Hash sh = h;
        sh.shl(1);
        sh.add(c, 0);
        dfs(i, v, sh);
    }
}

int choose[128][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Ppow_init(1000009);

    rep(j, 4) choose[0][j] = 0;
    rep(i, 128) choose[i][0] = 1;
    repx(i, 1, 128) repx(j, 1, 4) choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        tries.assign(N, {});
        rep(i, N) {
            int M;
            cin >> M;
            tries[i].resize(M);
            repx(j, 1, M) {
                int p;
                cin >> p;
                p -= 1;
                char c;
                cin >> c;
                tries[i][p].push_back({c, j});
            }
        }

        counts.clear();
        rep(i, N) dfs(i, 0, Hash());

        ll ans = 0;
        for (auto [h, yes] : counts) {
            int no = N - yes;
            cerr << "hash " << h.h[0] << " is in " << yes << "/" << N << " tries" << endl;
            ans += choose[yes][3];
            ans += choose[yes][2] * choose[no][1];
            ans += choose[yes][1] * choose[no][2];
        }

        cout << "Case #" << tc + 1 << ": " << ans
             << "\n";
    }
}
