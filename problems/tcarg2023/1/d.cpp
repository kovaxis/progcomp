#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> juntar(vector<int> &A, vector<int> &B, int n) {

    vector<int> C(n);
    int i = 0;
    int j = 0;
    int k = 0;
    while (k < n) {
        if (i == A.size()) {
            C[k] = B[j];
            j++;
            k++;
            continue;
        }
        if (j == B.size()) {
            C[k] = A[i];
            i++;
            k++;
            continue;
        }
        if (A[i] <= B[j]) {
            C[k] = A[i];
            i++;
            k++;
        } else {
            C[k] = B[j];
            j++;
            k++;
        }
    }

    return C;
}

ll solve(int n, int m, int k, vector<string> &grilla) {

    if (n == 0 || m == 0) {
        return 0;
    }

    int r = n / 2;

    ll res = 0;
    vector<vector<int>> U(m, vector<int>(k + 1, r + 1));
    vector<vector<int>> D(m, vector<int>(k + 1, n - r));
    vector<int> M(m, 0);

    for (int i = 0; i < m; i++) {
        int l = 0;
        for (int j = r - 1; j >= 0; j--) {
            if (grilla[j][i] == '1' && l < k + 1) {
                U[i][l] = r - j;
                l++;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int l = 0;
        for (int j = r + 1; j < n; j++) {
            if (grilla[j][i] == '1' && l < k + 1) {
                D[i][l] = j - r;
                l++;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (grilla[r][i] == '1') {
            M[i] = 1;
        }
    }

    vector<int> UX;
    vector<int> DX;
    int MX = 0;

    for (int i = 0; i < m; i++) {
        UX.clear();
        DX.clear();
        MX = 0;
        UX.push_back(0);
        DX.push_back(0);
        for (int j = i; j < m; j++) {
            // cout<<i<<" "<<j<<" "<<MX<<endl;
            MX = MX + M[j];
            UX = juntar(UX, U[j], k + 2);
            DX = juntar(DX, D[j], k + 2);
            for (int l = 0; l <= k; l++) {
                if (k - l - MX >= 0) {
                    res = res + (UX[l + 1] - UX[l]) * (DX[k - l - MX + 1] - DX[k - l - MX]);
                }
            }
        }
    }
    vector<string> grilla1;
    vector<string> grilla2;

    for (int j = 0; j < m; j++) {
        string aux = "";
        aux.reserve(r);
        for (int i = 0; i < r; i++) {
            aux.push_back(grilla[i][j]);
        }
        grilla1.push_back(aux);
        aux = "";
        aux.reserve(n - r - 1);
        for (int i = r + 1; i < n; i++) {
            aux.push_back(grilla[i][j]);
        }
        grilla2.push_back(aux);
    }

    res = res + solve(grilla1.size(), r, k, grilla1);
    res = res + solve(grilla2.size(), n - r - 1, k, grilla2);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<string> grilla(n);

    for (int i = 0; i < n; i++) {
        cin >> grilla[i];
    }

    cout << solve(n, m, k, grilla) << endl;

    return 0;
}