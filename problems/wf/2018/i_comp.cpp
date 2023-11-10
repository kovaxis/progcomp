#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct St {
    int neut() { return 0; }
    int merge(int x, int y) { return x + y; }

    int n;
    vector<int> a;
    St(int n = 0) : n(n), a(2 * n, neut()) {}

    int query(int l, int r) {
        if (l >= r) {
            return neut();
        }
        int x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, int x) { // fija
        for (a[i += n] = x; i /= 2;)
            a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

ll solve(int RX, int CX, vector<string> &grilla) {

    vector<vector<ii>> U(RX, vector<ii>(CX, {0, 0}));
    vector<pair<ii, int>> ordered;

    for (int r = 0; r < RX; r++) {
        for (int c = 0; c < CX; c++) {
            if (r % 2 != c % 2) {
                continue;
            }
            int posr = 2 * r;
            int posc;
            if (r % 2 == 0) {
                posc = 4 * (c / 2);
            } else {
                posc = 4 * (c / 2) + 2;
            }

            if (posr - 1 >= 0 && posc - 1 >= 0 && posc - 1 < int(grilla[posr - 1].size()) && grilla[posr - 1][posc - 1] != ' ') {
                U[r][c].second = 1;
            }
            if (posr - 1 >= 0 && posc + 1 < int(grilla[posr - 1].size()) && grilla[posr - 1][posc + 1] != ' ') {
                U[r][c].first = 1;
            }
        }
    }

    ll res = 0;

    vector<int> L(CX, 0);
    vector<int> R(CX, 0);
    St sumL(CX);
    St sumR(CX);

    for (int r = 0; r < RX; r++) {
        int posr = 2 * r;
        int posc;

        vector<int> stopL(CX, CX - 1);
        vector<int> stopR(CX, 0);

        for (int c = 0; c < CX; c++) {
            if (c % 2 != r % 2) {
                continue;
            }
            if (r % 2 == 0) {
                posc = 4 * (c / 2);
            } else {
                posc = 4 * (c / 2) + 2;
            }

            sumL.update(c, 1);
            sumR.update(c, 1);

            if (U[r][c].first == 0 || c == CX - 1) {
                L[c] = 0;
            } else {
                L[c] = L[c + 1] + 1;
            }
            if (U[r][c].second == 0 || c == 0) {
                R[c] = 0;
            } else {
                R[c] = R[c - 1] + 1;
            }

            if (posc == 0 || grilla[posr][posc - 1] == ' ') {
                stopR[c] = c;
            }

            if (posc + 1 == int(grilla[posr].size()) || grilla[posr][posc + 1] == ' ') {
                stopL[c] = c;
            }
        }

        for (int c = 1; c < CX; c++) {
            stopR[c] = max(stopR[c], stopR[c - 1]);
        }
        for (int c = CX - 2; c >= 0; c--) {
            stopL[c] = min(stopL[c], stopL[c + 1]);
        }
        /*cout<<r<<": ";
        cout<<endl;
        for(auto u: stopL){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: stopR){
            cout<<u<<" ";
        }
        cout<<endl;
        */
        ordered.clear();
        for (int c = 0; c < CX; c++) {
            if (r % 2 != c % 2) continue;
            ordered.push_back({{L[c], c}, 0});
            ordered.push_back({{R[c], c}, 1});
        }
        sort(ordered.begin(), ordered.end());

        for (auto A : ordered) {
            auto [xy, z] = A;
            auto [x, y] = xy;

            if (z == 0) {
                res = res + (ll)sumR.query(y + 1, min(stopL[y], y + 2 * x) + 1);
                sumL.update(y, 0);
            } else {
                res = res + (ll)sumL.query(max(stopR[y], y - 2 * x), y);
                sumR.update(y, 0);
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;

    int RX, CX;
    cin >> RX >> CX;

    getline(cin, s);

    vector<string> grilla(2 * RX - 1);

    for (int i = 0; i < 2 * RX - 1; i++) {
        getline(cin, grilla[i]);
        grilla[i].resize(CX * 4 + 10, ' ');
    }
    if (RX % 2 == 0) {
        RX += 1;
        grilla.resize(2 * RX - 1);
        grilla[2 * RX - 3] = string(CX * 4 + 10, ' ');
        grilla[2 * RX - 2] = string(CX * 4 + 10, ' ');
    }

    ll res = 0;

    res = res + solve(RX, CX, grilla);

    reverse(grilla.begin(), grilla.end());

    // cerr << "runinng on grilla:" << endl;
    // for(string l : grilla) cerr << l << endl;

    res = res + solve(RX, CX, grilla);

    cout << res << "\n";

    return 0;
}