#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

int n;
int tmpb[100000];
int perms[50][100000];

int cyclelen[100000];
bool visited[100000];

ll mcm(ll a, ll b) { return a * b / __gcd(a, b); }

// ABABA|BABABAB
void apply_perm(const int* from, int* to, const int* perm) {
    rep(i, n) { to[i] = perm[from[i]]; }
}
int tmp[2][100000];
bool identity_at(ll x) {
    int* tmpfrom = tmp[0];
    int* tmpto = tmp[1];
    rep(i, n) { tmpfrom[i] = i; }
    int idx = 0;
    while (x) {
        if (x & 1) {
            apply_perm(tmpfrom, tmpto, perms[idx]);
            swap(tmpfrom, tmpto);
        }
        x >>= 1;
        idx += 1;
    }
    rep(i, n) {
        if (tmpfrom[i] != i) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) {
        cin >> perms[0][i];
        perms[0][i] -= 1;
    }
    rep(i, n) {
        cin >> tmpb[i];
        tmpb[i] -= 1;
    }
    apply_perm(perms[0], perms[1], tmpb);
    rep(i, 1, 49) { apply_perm(perms[i], perms[i + 1], perms[i]); }

    ll tcycles = 1;
    rep(i, n) {
        int nxt = i;
        int cyclelen = 0;
        while (!visited[nxt]) {
            visited[nxt] = true;
            cyclelen += 1;
            nxt = perms[1][nxt];
        }
        if (cyclelen > 0) {
            cout << "cycle for " << i << ": " << cyclelen << endl;
            tcycles = mcm(tcycles, cyclelen);
            if (tcycles > 1000000000000ll) {
                cout << "huge\n";
                return 0;
            }
        }
    }

    cerr << "tcycles = " << tcycles << endl;

    if (tcycles % 2 == 0 || !identity_at(tcycles)) {
        if (2 * tcycles > 1000000000000ll) {
            cout << "huge\n";
            return 0;
        }
        cout << 2 * tcycles << endl;
    } else {
        cout << tcycles << endl;
    }
}
