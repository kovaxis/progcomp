#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<double> P;
vector<chrono::sys_days> D;
map<string, int> months = {
    {"Jan", 1},
    {"Feb", 2},
    {"Mar", 3},
    {"Apr", 4},
    {"May", 5},
    {"Jun", 6},
    {"Jul", 7},
    {"Aug", 8},
    {"Sep", 9},
    {"Oct", 10},
    {"Nov", 11},
    {"Dec", 12},
};

double func(double r) {
    return 0.;
}

chrono::sys_days readdate() {
    int d;
    cin >> d;

    char c;
    cin >> c; // -

    string ms;
    cin >> c;
    ms.push_back(c);
    cin >> c;
    ms.push_back(c);
    cin >> c;
    ms.push_back(c);
    int m = months[ms];

    cin >> c; // -

    int y;
    cin >> y;

    auto x = chrono::year{y} / m / d;
    return chrono::sys_days{x};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) {
        cin >> P[i];
        D[i] = readdate();
    }
}
