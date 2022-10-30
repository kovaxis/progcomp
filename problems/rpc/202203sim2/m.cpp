#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

vector<int> path;
vector<int> prio;
vector<vector<int>> tree;

void dfs(int i) {
    path.push_back(i);
    for (int v : tree[i]) dfs(v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int q;
    cin >> q;
    vector<int> t(q);
    vector<int> x(q);
    tree.resize(1);
    int n = 1;
    for (int i = 0; i < q; i++) {
        cin >> t[i] >> x[i];
        x[i]--;
        if (t[i] == 1) {
            tree.push_back(vector<int>(0));
            tree[x[i]].push_back(n);
            n++;
        }
    }
    path.reserve(n + 5);
    dfs(0);
    prio.resize(path.size());

    for (int i = 0; i < path.size(); i++) {
        prio[path[i]] = i;
    }
    // for (int i : path) cout << i + 1 << endl;
    set<int> s;
    s.insert(prio[0]);
    n = 1;
    for (int i = 0; i < q; i++) {
        if (t[i] == 1) {
            s.insert(prio[n]);
            n++;
        } else {
            s.erase(prio[x[i]]);
            cout << path[*(s.begin())] + 1 << endl;
        }
    }

    return 0;
}
