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

vector<set<int>> adj;
vector<int> parent;
set<int> ask;
vector<int> numbering;
int ans;

void makeroot(int i) {
    numbering.push_back(i);
    for (int child : adj[i]) {
        parent[child] = i;
        adj[child].erase(i);
        makeroot(child);
    }
}

bool isinrange(int l, int r) {
    ask.clear();
    rep(i, l, r + 1) {
        ask.insert(numbering[i]);
        ask.insert(parent[numbering[i]]);
    }
    cout << "? " << ask.size();
    for (int i : ask) cout << " " << i + 1;
    cout << endl;
    int x;
    cin >> x;
    return x == ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    adj.resize(N);
    parent.resize(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].insert(v - 1);
        adj[v - 1].insert(u - 1);
    }
    makeroot(0);

    cout << "? " << N;
    rep(i, N) cout << " " << i + 1;
    cout << endl;
    cin >> ans;

    int l = 1, r = N - 1;
    while (l != r) {
        int m = l + (r - l) / 2;
        if (isinrange(m + 1, r)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    int node = numbering[l];
    cout << "! " << node + 1 << " " << parent[node] + 1 << endl;
}
