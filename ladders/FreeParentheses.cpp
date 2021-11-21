// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3679

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

int N;
vector<pair<int, int>> ops;

const int BZERO = 3000;
typedef bitset<6001> bits;

// [from, to)
// reachable numbers
bits dp[32][32];

bits reverse(const bits& b) {
    bits tmp;
    rep(i, 6001) tmp[i] = b[6000 - i];
    return tmp;
}

bits distr(const bits& a, const bits& b) {
    bits tmp;
    rep(i, 6001) {
        int off = i - BZERO;
        if (b[i])
            if (off < 0) {
                tmp |= a >> -off;
            } else {
                tmp |= a << off;
            }
    }
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (getline(cin, s)) {
        {
            ops.clear();
            stringstream ss;
            ss << s;
            int i = 0;
            char op;
            int x;
            while (true) {
                op = '+';
                if (!ops.empty())
                    if (!(ss >> op)) break;
                if (!(ss >> x)) break;
                ops.push_back({op == '+' ? 1 : -1, x});
            }
            N = ops.size();
        }

        invrep(i, N + 1) invrep(j, i, N + 1) {
            if (i == j) {
                bits b;
                b.set(BZERO, 1);
                dp[i][j] = b;
                continue;
            }
            if (ops[i].first > 0) {
                dp[i][j] = dp[i + 1][j] << ops[i].second;
                continue;
            }
            bits reach;
            rep(k, i + 1, j + 1) reach |=
                distr(reverse(dp[i + 1][k]) >> ops[i].second, dp[k][j]);
            dp[i][j] = reach;
        }

        /*rep(i, N + 1) rep(j, i, N + 1) {
            cerr << "reach[" << i << ", " << j << ") = {";
            bool first = true;
            rep(k, 6001) if (dp[i][j][k]) {
                if (!first) cerr << ", ";
                cerr << k - BZERO;
                first = false;
            }
            cerr << "}" << endl;
        }*/

        cout << dp[0][N].count() << '\n';
    }
}
