#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int Nr, Nb;

vector<int> parents;

string tmps;
int readname() {
    cin >> tmps;
    if (tmps[0] == 'R') {
        return stoi(tmps.substr(1)) - 1;
    } else {
        return stoi(tmps.substr(1)) - 1 + Nr;
    }
}

set<int> seen;
pair<int, int> check(int i) {
    seen.clear();
    int time = 0;
    while (parents[i] != i) {
        if (seen.count(i)) return {0, INT32_MAX};
        seen.insert(i);
        i = parents[i];
        time += 1;
    }
    return {i != 0, time};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int E;
        cin >> Nr >> Nb >> E;
        parents.resize(Nr + Nb);
        parents[0] = 0;
        rep(i, 1, Nr) parents[i] = readname();
        parents[Nr] = Nr;
        rep(i, 1, Nb) parents[Nr + i] = readname();

        rep(e, E) {
            char op;
            cin >> op;
            if (op == 'c') {
                // crossover
                int x = readname(), y = readname();
                parents[x] = y;
            } else if (op == 'w') {
                // check winner
                int timeto[2] = {INT32_MAX, INT32_MAX};
                int x[2] = {readname(), readname()};
                rep(i, 2) {
                    auto y = check(x[i]);
                    timeto[y.first] = min(timeto[y.first], y.second);
                }
                if (timeto[0] == INT32_MAX && timeto[1] == INT32_MAX) {
                    cout << "NONE\n";
                } else if (timeto[0] < timeto[1]) {
                    cout << "RED " << timeto[0] << "\n";
                } else if (timeto[0] > timeto[1]) {
                    cout << "BLUE " << timeto[1] << "\n";
                } else {
                    cout << "TIE " << timeto[0] << "\n";
                }
            }
        }
    }
}
