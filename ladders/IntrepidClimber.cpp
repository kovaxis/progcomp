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

int n, f;
vector<pair<int, int>> nodes[100001];
bool friends[100001];

// nodeid
// e_to_roundtrip, oneway_discount
pair<int, int> visit(int parent, int i, int upcost) {
    int cost_rt = 0;
    int discount = 0;
    for (auto& link : nodes[i]) {
        int child = link.first;
        int downcost = link.second;
        if (child == parent) continue;
        auto subcost = visit(i, child, downcost);
        cost_rt += subcost.first;
        discount = max(discount, subcost.second);
    }
    if (cost_rt <= 0 && !friends[i]) return {0, 0};
    return {cost_rt + upcost, discount + upcost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        if (!(cin >> n)) break;
        cin >> f;
        rep(i, n) nodes[i].clear();
        rep(i, n - 1) {
            int a, b, c;
            cin >> a >> b >> c;
            a -= 1;
            b -= 1;
            nodes[a].push_back({b, c});
            nodes[b].push_back({a, c});
        }
        rep(i, n) friends[i] = false;
        rep(i, f) {
            int idx;
            cin >> idx;
            friends[idx - 1] = true;
        }
        auto cost = visit(-1, 0, 0);
        cout << cost.first - cost.second << '\n';
    }
}
