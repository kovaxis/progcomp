#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef uint32_t u32;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

int N, Qn;
vector<u32> Z[3], A, Af[3], B, Cm, Ct, Csanity;
vector<pair<int, int>> Q;
vector<u32> ans;
vector<int> evs;

u32 get_c(int r, int i) {
    return Cm[i] + (Ct[i] - r) * B[i];
}

u32 valueof(int L, int R) {
    assert(L <= R);
    u32 a = Z[0][L], b = Z[1][L], c = Z[2][L];
    repx(i, L, R + 1) a = a & Z[0][i];
    repx(i, L, R + 1) b = b | Z[1][i];
    repx(i, L, R + 1) c = __gcd(c, Z[2][i]);
    return a * b * c;
}

int evpos(int i) {
    return i >= 0 ? Q[i].second + 1 : Q[-i - 1].first;
}

void sanity(int R) {
    repx(l, 1, R + 1) {
        assert(A[l] == valueof(l, R));
    }
    u32 acc = 0;
    repx(i, 1, R + 1) {
        acc += A[i];
        assert(B[i] == acc);
    }
    repx(i, 1, R + 1) {
        Csanity[i] += B[i];
        assert(get_c(R, i) == Csanity[i]);
    }
}

void recompute(int R) {
    rep(z, 3) Af[z][R] = Z[z][R];
    A[R] = Af[0][R] * Af[1][R] * Af[2][R];
    int L = R;
    while (L > 1) {
        int l = L - 1;
        u32 z0 = Z[0][l] & Af[0][L];
        u32 z1 = Z[1][l] | Af[1][L];
        u32 z2 = __gcd(Z[2][l], Af[2][L]);
        if (z0 == Af[0][l] && z1 == Af[1][l] && z2 == Af[2][l]) break;
        Af[0][l] = z0, Af[1][l] = z1, Af[2][l] = z2;
        A[l] = Af[0][l] * Af[1][l] * Af[2][l];
        L = l;
    }
    repx(i, L, R + 1) {
        Cm[i] = get_c(R + 1, i);
        Ct[i] = R + 1;
    }
    repx(i, L, R + 1) {
        B[i] = B[i - 1] + A[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Qn;
    rep(z, 3) {
        Z[z].resize(N + 3);
        repx(i, 1, N + 1) cin >> Z[z][i];
    }
    Q.resize(Qn);
    rep(qi, Qn) cin >> Q[qi].first >> Q[qi].second;

    A.resize(N + 3);
    rep(z, 3) Af[z].resize(N + 3);
    B.resize(N + 3);
    Cm.resize(N + 3);
    Ct.resize(N + 3);
    Csanity.resize(N + 3);

    ans.resize(Qn);
    vector<int> poscnt(N + 3);
    repx(j, -Qn, Qn) poscnt[evpos(j)] += 1;
    repx(i, 1, N + 3) poscnt[i] = poscnt[i - 1] + poscnt[i];
    evs.resize(2 * Qn);
    repx(j, -Qn, Qn) evs[--poscnt[evpos(j)]] = j;

    int ii = 2 * Qn - 1;
    while (ii >= 0 && evpos(evs[ii]) == N + 1) ii -= 1;
    invrepx(R, 1, N + 1) {
        recompute(R);
        // sanity(R);
        while (ii >= 0 && evpos(evs[ii]) == R) {
            int qi2 = evs[ii];
            int qi = (qi2 >= 0 ? qi2 : -qi2 - 1);
            u32 mult = (qi2 >= 0 ? 1 : -1);
            ans[qi] += mult * get_c(R, Q[qi].first - 1);
            ii -= 1;
        }
    }
    repx(i, 1, N + 1) B[i] = B[i - 1] + B[i];
    rep(qi, Qn) {
        ans[qi] += B[Q[qi].second] - B[Q[qi].first - 1];
    }

    rep(qi, Qn) cout << ans[qi] << "\n";
}
