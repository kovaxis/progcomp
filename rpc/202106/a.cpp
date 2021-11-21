#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep_(i, k, n) for (int i = k; i < n; ++i)
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(ios::fixed);
    cout.precision(10);

    string s;
    int n;

    priority_queue<int> cube, cylinder;
    vector<pair<bool, int>> sol;

    cin >> n;
    rep(i, n) {
        cin >> s;
        int aux;
        cin >> aux;
        if (s == "cube")
            cube.push(aux);
        else
            cylinder.push(aux);
    }
    while (!cube.empty() || !cylinder.empty()) {
        int scube = 0;
        if (!cube.empty()) {
            scube = cube.top();
        }
        int rcyl = 0;
        if (!cylinder.empty()) {
            rcyl = cylinder.top();
        }

        if (scube * scube <= 2 * rcyl * rcyl) {
            // cube fits in cyl
            sol.push_back({true, rcyl});
            cylinder.pop();
        } else if (2 * rcyl <= scube) {
            // cyl fits in cube
            sol.push_back({false, scube});
            cube.pop();
        } else {
            cout << "impossible\n";
            return 0;
        }
    }
    /*while (!cube.empty() && !cylinder.empty()) {
        int Lcubo = cube.top();
        int Rcilindro = cylinder.top();
        bool cancb = true, cancyl = true;

        if (ladomin < Lcubo) {
            cancb = false;
        }
        if (radmin < Rcilindro) {
            cancyl = false;
        }
        if (!cancb && !cancyl) {
            cout << "impossible\n";
            return 0;
        }

        if (!cancyl || Lcubo > 2 * Rcilindro) {
            sol.push_back({"cube", Lcubo});
            cube.pop();
            radmin = Lcubo / 2;
            ladomin = Lcubo;
            continue;
        }

        else {
            sol.push_back({"cylinder", Rcilindro});
            cylinder.pop();
            radmin = Rcilindro;
            ladomin = Rcilindro * sqrt(2);
            continue;
        }
    }*/

    for (int i = n - 1; i >= 0; i--) {
        if (sol[i].first) {
            cout << "cylinder ";
        } else {
            cout << "cube ";
        }
        cout << sol[i].second << '\n';
    }
    return 0;
}