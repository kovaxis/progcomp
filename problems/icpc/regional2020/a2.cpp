#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

void addnums(int x, int y) { cout << "1 " << x << "\n1 " << y << "\n"; }
int n;

void usebase(vector<pair<int, int>>& ops) {
    vector<int> base = {1};
    for (auto& op : ops) base.push_back(op.first + op.second);
    int tmp = n;
    int topbase = base.back();
    while (true) {
        topbase <<= 1;
        if (topbase > tmp) break;
        ops.push_back({topbase >> 1, topbase >> 1});
        base.push_back(topbase);
    }
    while (tmp != 0) {
        invrep(i, base.size()) if (base[i] <= tmp) {
            tmp -= base[i];
            if (tmp > 0) ops.push_back({tmp, base[i]});
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin >> m >> n;
    if (m != 1) {
        cout << "*\n";
        return 0;
    }

    const int BASES = 6;
    vector<pair<int, int>> ops[BASES] = {
        {},
        {{1, 1}, {2, 1}},
        {{1, 1}, {2, 1}, {3, 2}},
        {{1, 1}, {2, 2}, {4, 1}},
        {{1, 1}, {2, 1}, {2, 2}, {4, 3}},
        {{1, 1}, {2, 2}, {4, 2}, {6, 1}},
    };
    rep(i, BASES) usebase(ops[i]);
    int mincount = INT32_MAX;
    int mini;
    rep(i, BASES) {
        if (ops[i].size() < mincount) {
            mincount = ops[i].size();
            mini = i;
        }
    }

    for (auto& op : ops[mini]) addnums(op.first, op.second);
}
