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

vector<int> nodes;
vector<set<int>> adj;
vector<int> subxor;
set<int> countxor;
int x;

void makeroot(int i) {
    for (int child : adj[i]) {
        adj[child].erase(i);
        makeroot(child);
    }
}

int getsubxor(int i) {
    int res = nodes[i];
    for (int child : adj[i]) res ^= getsubxor(child);
    return subxor[i] = res;
}

// 0 => no x
// 1 => found x
// 2 => found x, then 0. done!
int check3(int i) {
    int status = 0;
    for (int child : adj[i]) {
        int sub = check3(child);
        if (sub == 2) return 2;
        if (sub == 1 && status == 1) return 2;
        if (sub == 1) status = 1;
    }
    if (subxor[i] == 0 && status == 1) return 2;
    if (subxor[i] == x) status = 1;
    return status;
}

bool testcase() {
    int N, K;
    cin >> N >> K;
    nodes.resize(N);
    rep(i, N) cin >> nodes[i];
    adj.clear();
    adj.resize(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].insert(v - 1);
        adj[v - 1].insert(u - 1);
    }
    makeroot(0);

    subxor.resize(N);
    x = getsubxor(0);

    // divide into 2 components
    if (x == 0) return true;

    // if only division into 2 components is possible, that already failed
    if (K == 2) return false;

    // divide into 3 components
    return check3(0) == 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        if (testcase()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
