#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

int K, N, M, L1, R1, L2, R2;
vector<ll> A, Ao;
umap<ll, int> B;
ll C;
int del;

void correct(int &x) {
    if (del == -1) return;
    if (x >= del) x += 1;
}

// 2^(k+1)-1 * 2^(k+1) / 2
// 2^(2k+2) / 2 - 2^(k+1) / 2
// 2^(2k+1) - 2^k
// 2^k * 2^(k+1) - 2^k
// 2^k * (2^(k+1) - 1)
//
// 2^k * (2^(k+1) - 1) - 2^2k
// 2^k * (2^(k+1) - 2^k - 1)

bool solve2() {
    ll X = 0;
    repx(i, L1, R1) X ^= A[i];

    B.clear();
    C = 0;
    rep(i, N) {
        if (i != L1 || !B.count(C)) B[C] = i;
        C ^= A[i];

        if (B.count(C ^ X) && (B[C ^ X] != L1 || i + 1 != R1)) {
            L2 = B[C ^ X];
            R2 = i + 1;
            return true;
        }
    }

    return false;
}

void solve() {
    Ao = A;
    int zcnt = 0;
    rep(i, N) if (A[i] == 0) zcnt += 1;
    del = -1;
    if (zcnt > 1) {
        invrep(i, N) {
            if (A[i] == 0) L1 = i, R1 = i + 1;
        }
        rep(i, N) {
            if (A[i] == 0) L2 = i, R2 = i + 1;
        }
        return;
    } else {
        rep(i, N) if (A[i] == 0) {
            A.erase(A.begin() + i);
            N -= 1;
            del = i;
            break;
        }
    }

    rep(_, 24) {
        L1 = rng() % N;
        R1 = rng() % N;
        if (L1 > R1) swap(L1, R1);
        R1 += 1;
        if (solve2()) {
            if (L1 > L2 || (L1 == L2 && R1 > R2)) swap(L1, L2), swap(R1, R2);
            int l1 = L1, r1 = R1;
            int l2 = L2, r2 = R2;
            if (R1 >= R2) {
                // 1 contains 2
                if (L1 < L2) {
                    if (R1 > R2) {
                        l1 = L1, r1 = L2;
                        l2 = R2, r2 = R1;
                    } else {
                        l1 = L1, r1 = L1 + 1;
                        l2 = L1 + 1, r2 = L2;
                    }
                } else {
                    l1 = R2, r1 = R2 + 1;
                    l2 = R2 + 1, r2 = R1;
                }
            } else if (R1 > L2) {
                // overlap
                l1 = L1, r1 = L2;
                l2 = R1, r2 = R2;
            }
            L1 = l1, R1 = r1;
            L2 = l2, R2 = r2;
            correct(L1);
            correct(R1);
            correct(L2);
            correct(R2);
            ll x1 = 0, x2 = 0;
            repx(i, L1, R1) x1 ^= Ao[i];
            repx(i, L2, R2) x2 ^= Ao[i];
            if (x1 != x2) {
                cerr << "invalid answer: " << L1 + 1 << " " << R1 << " " << L2 + 1 << " " << R2 << endl;
                throw "a";
            }
            return;
        }
    }
    assert(false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> K;
        N = 1 << (K + 1);
        A.resize(N);
        rep(i, N) cin >> A[i];

        solve();
        cout << L1 + 1 << " " << R1 << " " << L2 + 1 << " " << R2 << "\n";
    }
}
