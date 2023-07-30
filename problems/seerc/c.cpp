#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> A(m);
    vector<vector<int>> donde(n);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        A[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> A[i][j];
            A[i][j]--;
            donde[A[i][j]].push_back(i);
        }
    }

    vector<int> inter((1 << m));
    vector<int> signo((1 << m));
    for (int i = 0; i < (1 << m); i++) {
        int contarsigno = 0;
        vector<bool> existe(n, false);
        for (int j = 0; j < m; j++) {
            if ((i & (1 << j)) == 0) continue;
            for (auto u : A[j]) {
                existe[u] = true;
            }
            contarsigno++;
        }
        int contar = 0;
        for (int j = 0; j < n; j++) {
            if (existe[j] == false) {
                contar++;
            }
        }
        inter[i] = contar;
        if (contarsigno % 2 == 1) {
            signo[i] = 1;
        } else {
            signo[i] = -1;
        }
    }

    vector<vector<int>> bits(n, vector<int>(n + 5, 0));
    for (int i = 0; i < n; i++) {
        bits[i][n + 4] = -1 * i;
        int bitmask = (1 << m) - 1;
        for (auto u : donde[i]) {
            bitmask = bitmask - (1 << u);
        }
        // cout << i << " " << bitmask << endl;
        for (int j = 1; j < (1 << m); j++) {
            if ((j & bitmask) == j) {
                bits[i][inter[j] - 1] = bits[i][inter[j] - 1] + signo[j];
            }
        }

        for (int j = 0; j < n + 4; j++) {
            if (bits[i][j] < 0) {
                int cuantos = (abs(bits[i][j]) + 1) / 2;
                bits[i][j] = bits[i][j] + 2 * cuantos;
                bits[i][j + 1] = bits[i][j + 1] - cuantos;
            } else {
                bits[i][j + 1] = bits[i][j + 1] + bits[i][j] / 2;
                bits[i][j] = bits[i][j] % 2;
            }
        }
        reverse(bits[i].begin(), bits[i].end() - 1);
    }
    // return 0;
    // for (int i = 0; i <= n; i++) {
    //    cout << i << ": ";
    //     for (int j = 0; j < n; j++) {
    //         cout << bits[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // return 0;

    sort(bits.begin(), bits.end(), greater<vector<int>>());

    for (int i = 0; i < n; i++) {
        cout << -1 * bits[i][n + 4] + 1 << " ";
    }
    cout << endl;

    return 0;
}