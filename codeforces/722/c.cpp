#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

int n;
pair<int, int> nums[200001];
vector<int> nodes[200001];

pair<ll, ll> beauties(int node, int parent) {
    int l = nums[node].first;
    int r = nums[node].second;
    ll lb = 0;
    ll rb = 0;
    for (int child : nodes[node]) {
        if (child == parent) {
            continue;
        }
        pair<ll, ll> cbs = beauties(child, node);
        lb += max(cbs.first + (ll)abs(l - nums[child].first),
                  cbs.second + (ll)abs(l - nums[child].second));
        rb += max(cbs.first + (ll)abs(r - nums[child].first),
                  cbs.second + (ll)abs(r - nums[child].second));
    }
    return {lb, rb};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        cin >> n;
        rep(i, n) {
            cin >> nums[i].first >> nums[i].second;
            nodes[i].clear();
        }
        rep(i, n - 1) {
            int u, v;
            cin >> u >> v;
            u -= 1;
            v -= 1;
            nodes[u].push_back(v);
            nodes[v].push_back(u);
        }
        pair<ll, ll> rb = beauties(0, -1);
        cout << max(rb.first, rb.second) << '\n';
    }
}
