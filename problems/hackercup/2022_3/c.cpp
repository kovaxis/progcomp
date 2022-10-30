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
const ll P =
    chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
ll Ppow[HC][30001];

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

int N, Q, L;

vector<string> As, Bs;
vector<Hash> A, B;

umap<Hash, int> center;

int mp_char[256];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(hc, HC) Ppow[hc][0] = 1;
    rep(hc, HC) rep(i, 30000) Ppow[hc][i + 1] = Ppow[hc][i] * P % MOD[hc];

    mp_char['m'] = 1;
    mp_char['e'] = 2;
    mp_char['t'] = 3;
    mp_char['a'] = 4;

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        As.resize(N);
        A.assign(N, {});
        rep(i, N) {
            cin >> As[i];
            L = As[i].size();
            rep(l, L) As[i][l] = mp_char[As[i][l]];
            rep(l, L) A[i].add(As[i][l], l);
        }
        cin >> Q;
        Bs.resize(Q);
        B.assign(Q, {});
        rep(j, Q) {
            cin >> Bs[j];
            L = Bs[j].size();
            rep(l, L) Bs[j][l] = mp_char[Bs[j][l]];
            rep(l, L) B[j].add(Bs[j][l], l);
        }

        ll ans = 0;

        // go adding all modifications to A words
        rep(l, L) {
            // all modifications to B words at character l
            rep(j, Q) repx(c, 1, 5) {
                int var = c - (int)Bs[j][l];
                if (var == 0) continue;
                Hash h = B[j];
                h.add(var, l);
                ans += center[h];

                cerr << "word B[" << j + 1 << "] modified at character " << l + 1 << " to c[" << c << "] has " << center[h] << " matches" << endl;
                // cerr << "  h = {" << h.h[0] << ", " << h.h[1] << "}" << endl;
            }

            // all modifications of A words at character l
            rep(i, N) repx(c, 1, 5) {
                int var = c - (int)As[i][l];
                if (var == 0) continue;
                Hash h = A[i];
                h.add(var, l);
                center[h] += 1;

                cerr << "modifying word A[" << i + 1 << "] at character " << l + 1 << " to c[" << c << "]" << endl;
                // cerr << "  h = {" << h.h[0] << ", " << h.h[1] << "}" << endl;
            }
        }

        // go removing all modifications to A words
        rep(l, L) {
            // all modifications of A words at character l
            rep(i, N) repx(c, 1, 5) {
                int var = c - (int)As[i][l];
                if (var == 0) continue;
                Hash h = A[i];
                h.add(var, l);
                center[h] -= 1;

                cerr << "modifying word A[" << i + 1 << "] at character " << l + 1 << " to c[" << c << "]" << endl;
                // cerr << "  h = {" << h.h[0] << ", " << h.h[1] << "}" << endl;
            }

            // all modifications to B words at character l
            rep(j, Q) repx(c, 1, 5) {
                int var = c - (int)Bs[j][l];
                if (var == 0) continue;
                Hash h = B[j];
                h.add(var, l);
                ans += center[h];

                cerr << "word B[" << j + 1 << "] modified at character " << l + 1 << " to c[" << c << "] has " << center[h] << " matches" << endl;
                // cerr << "  h = {" << h.h[0] << ", " << h.h[1] << "}" << endl;
            }
        }

        cout << "Case #" << tc + 1 << ": " << ans / 2
             << "\n";
    }
}
