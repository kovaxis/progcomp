#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<string> A;
vector<vector<bool>> use;
vector<int> dn, rt;
vector<int> Pdn, Prt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];
    dn.resize(N), rt.resize(N);
    rep(i, N) cin >> rt[i];
    rep(j, N) cin >> dn[j];

    use.assign(N, vector<bool>(N));
    rep(i, N) rep(j, N) {
        if (A[i][j] == '-') dn[j] += 1, rt[i] += 1, use[i][j] = !use[i][j];
    }

    // cerr << "rt:";
    // rep(i, N) cerr << " " << rt[i];
    // cerr << endl;
    // cerr << "dn:";
    // rep(i, N) cerr << " " << dn[i];
    // cerr << endl;

    Pdn.resize(N);
    rep(i, N) Pdn[i] = i;
    sort(Pdn.begin(), Pdn.end(), [&](int i, int j) {
        return dn[i] > dn[j];
    });
    Prt.resize(N);
    rep(i, N) Prt[i] = i;
    sort(Prt.begin(), Prt.end(), [&](int i, int j) {
        return rt[i] > rt[j];
    });

    for (int i : Prt) {
        if (rt[i] <= 0) continue;
        int n = min(rt[i], N);
        int l = n - 1, r = n;
        while (l > 0 && dn[Pdn[l - 1]] == dn[Pdn[l]]) l -= 1;
        while (r < N && dn[Pdn[r]] == dn[Pdn[l]]) r += 1;
        rep(jj, l) {
            int j = Pdn[jj];
            dn[j] -= 1;
            rt[i] -= 1;
            use[i][j] = !use[i][j];
            n -= 1;
        }
        repx(jj, max(r - n, l), r) {
            int j = Pdn[jj];
            dn[j] -= 1;
            rt[i] -= 1;
            use[i][j] = !use[i][j];
            n -= 1;
        }
    }

    bool ok = true;
    rep(i, N) if (rt[i] != 0) ok = false;
    rep(j, N) if (dn[j] != 0) ok = false;
    if (ok) {
        cout << "Yes\n";
        rep(i, N) {
            rep(j, N) cout << int(use[i][j]);
            cout << "\n";
        }
    } else {
        cout << "No\n";
    }
}
