#include "../common.h"

const double EPS = 1e-9;

// complexity: O(min(N, M) * N * M)
// `a` is a list of rows
// the last value in each row is the result of the equation
// return values:
//  0 -> no solutions
//  1 -> unique solution, stored in `ans`
// -1 -> infinitely many solutions, one of which is stored in `ans`
int gauss(vector<vector<double>> a, vector<double>& ans) {
    int N = a.size(), M = a[0].size() - 1;

    vector<int> where(M, -1);
    for (int col = 0, row = 0; col < M && row < N; col++, row++) {
        int sel = row;
        repx(i, row, N) if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
        if (abs(a[sel][col]) < EPS) continue;
        repx(i, col, M + 1) swap(a[sel][i], a[row][i]);
        where[col] = row;

        rep(i, N) if (i != row) {
            double c = a[i][col] / a[row][col];
            repx(j, col, M + 1) a[i][j] -= a[row][j] * c;
        }
    }

    ans.assign(M, 0);
    rep(i, M) if (where[i] != -1) ans[i] = a[where[i]][M] / a[where[i]][i];
    rep(i, N) {
        double sum = 0;
        rep(j, M) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][M]) > EPS) return 0;
    }

    rep(i, M) if (where[i] == -1) return -1;
    return 1;
}

#ifndef NOMAIN_GAUSS

int main() {}

#endif