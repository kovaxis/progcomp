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

int N;
vector<vector<bool>> mat;
bool ok;

bool place1(int i, int j) {
    if (i < 0) return false;
    if (i >= N) return false;
    if (j < 0) return false;
    if (j >= N) return false;
    if (mat[i][j]) return false;
    cerr << "  placed square at " << i << " " << j << endl;
    mat[i][j] = true;
    return true;
}

void place(int i, int j) {
    cerr << "placing tile at " << i << " " << j << endl;
    ok &= place1(i, j);
    ok &= place1(i + 1, j);
    ok &= place1(i - 1, j);
    ok &= place1(i, j + 1);
    ok &= place1(i, j - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    mat.assign(N, vector<bool>(N));
    rep(i, N) rep(j, N) {
        char c;
        cin >> c;
        mat[i][j] = (c == '#');
    }

    ok = true;
    rep(i, N) rep(j, N) {
        if (!mat[i][j]) {
            // place tile centered on (i+1, j)
            place(i + 1, j);
        }
    }

    cout << (ok ? "YES" : "NO") << endl;
}
