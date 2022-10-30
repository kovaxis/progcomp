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
pair<int, int> dsu[10001];
int frats[10001];

void init(pair<int, int> dsu[], int n) { rep(i, n) dsu[i] = {i, 0}; }

// find the leader node corresponding to node `i`
int find(pair<int, int> dsu[], int i) {
    if (dsu[i].first != i) dsu[i].first = find(dsu, dsu[i].first);
    return dsu[i].first;
}

// perform union on the two disjoint sets with leaders `i` and `j`
// note: `i` and `j` must be LEADERS OF TWO SEPARATE SETS
bool unite(pair<int, int> dsu[], int i, int j) {
    if (dsu[i].second > dsu[j].second) {
        dsu[j].first = i;
        return j;
    } else {
        if (dsu[i].second == dsu[j].second) dsu[j].second += 1;
        dsu[i].first = j;
        return i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int H;
    cin >> N >> H;
    init(dsu, N);
    rep(h, H) {
        int i, j;
        cin >> i >> j;
        i = find(dsu, i - 1);
        j = find(dsu, j - 1);
        if (i != j) unite(dsu, i, j);
    }
    rep(i, N) frats[find(dsu, i)] += 1;
    ll count = 0, alone = 0;
    rep(i, N) if (frats[i] == 1) { alone += 1; }
    else if (frats[i] > 1) {
        count += 1;
    }
    cout << count << " " << alone << endl;
}
