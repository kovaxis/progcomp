#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int L = 2;
const ll MOD[L] = {1000001329, 1000002499};

struct Hash {
    int h[L];

    Hash() {
        rep(l, L) h[l] = 0;
    }

    void shift() {
        static const ll P =
            chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
        rep(l, L) h[l] = (ll)h[l] * P % MOD[l];
    }

    void add(int x) {
        rep(l, L) h[l] = (h[l] + x) % (int)MOD[l];
    }

    void push(int x) {
        shift();
        add(x);
    }
};

// hackproof unordered map hash
struct Hasher {
    size_t operator()(const Hash &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = RAND + 0x9e3779b97f4a7c15;
        rep(l, L) {
            z += x.h[l];
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            z = z ^ (z >> 31);
        }
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hasher>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hasher>;

int N;
vector<uset<Hash>> sets;
vector<vector<vector<pair<char, int>>>> tries;
umap<Hash, vector<int>> hash2trie;
int duplicate[128][128];

void dfs(int i, int u, Hash h) {
    for (auto [c, v] : tries[i][u]) {
        Hash sh = h;
        sh.push(c);
        sets[i].insert(sh);
        dfs(i, v, sh);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        tries.assign(N, {});
        sets.assign(N, {});
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

        rep(i, N) dfs(i, 0, Hash());

        hash2trie.clear();
        rep(i, N) for (Hash h : sets[i]) hash2trie[h].push_back(i);

        rep(i, N) rep(j, N) duplicate[i][j] = 0;

        rep(i, N) {
            for (Hash h : sets[i]) {
                for (int j : hash2trie[h]) duplicate[i][j] += 1;
            }
        }

        ll total_ans = 0;
        rep(i, N) repx(j, i + 1, N) repx(k, j + 1, N) {
            int ans = 0;
        }

        cout << "Case #" << tc + 1 << ": "
             << "\n";
    }
}
