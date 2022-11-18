#include "../../graph/two_sat.cpp"
#include "gtest.h"

bool satisfies(int N, ll x, vector<pair<int, int>> &eqs) {
    for (auto [u, v] : eqs) {
        int ux = (x >> (u % N)) & 1;
        int vx = (x >> (v % N)) & 1;
        if (u >= N) ux = !ux;
        if (v >= N) vx = !vx;
        if (!(ux || vx)) return false;
    }
    return true;
}

string var_str(int u, int N) {
    string x;
    x.push_back((char)('a' + u % N));
    if (u >= N) x = '!' + x;
    return x;
}

void test(int N, int M) {
    cout << "running test with " << N << " variables and " << M << " equations" << endl;

    vector<pair<int, int>> eqs;
    rep(j, M) eqs.push_back({random_int(0, 2 * N), random_int(0, 2 * N)});

    vector<ll> sols;
    for (ll x = 0; x < (1 << N); x++) {
        if (satisfies(N, x, eqs)) sols.push_back(x);
    }

    TwoSat sat(N);
    for (auto [u, v] : eqs) sat.any(u, v);
    bool solved = sat.solve();

    // cout << "2-sat:" << endl;
    // rep(u, 2 * N) for (int v : sat.G[u]) {
    //     cout << "  " << var_str(u, N) << " -> " << var_str(v, N) << endl;
    // }

    // cout << "equations:" << endl;
    // for (auto [u, v] : eqs) cout << "  " << var_str(u, N) << " or " << var_str(v, N) << endl;
    cout << "  2-sat solvable: " << solved << endl;
    // if (solved) {
    //     cout << "2-sat solution:" << endl;
    //     cout << " ";
    //     rep(u, N) cout << " " << sat.sol[u];
    //     cout << endl;
    // }

    if (solved != !sols.empty()) {
        cout << "2-sat says solvable = " << solved << ", but brute-force says #solutions = " << sols.size() << endl;
        if (!sols.empty()) {
            cout << "  ie. one solution is " << sols[0] << endl;
        }
        throw "error";
    }
    if (solved) {
        bool found = false;
        ll sx = 0;
        rep(u, N) sx |= ((ll)sat.sol[u] << u);
        for (ll x : sols)
            if (sx == x) found = true;
        if (!found) {
            cout << "2-sat says there is solution " << sx << ", but such solution can't be found" << endl;
            cout << "brute-force solutions:" << endl;
            for (ll x : sols) cout << "  " << x << endl;
            throw "error";
        }
    }

    cout << "  all ok" << endl;
}

int main() {
    test(20, 20);
    test(20, 30);
    test(20, 50);
    test(20, 100);
}
