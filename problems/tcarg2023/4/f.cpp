#include <bits/stdc++.h>
using namespace std;
int K;
vector<int> A;
vector<vector<int>> d;
vector<vector<int>> u;
vector<vector<int>> edges;
vector<int> padre;

void dfs(int v, int p) {
    padre[v] = p;
    for (auto u : edges[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    return;
}

int D(int v, int p, int k) {
    if (d[v][k] != -1) {
        return d[v][k];
    }
    if (k == 0) {
        d[v][k] = A[v];
    } else {
        d[v][k] = 0;
    }
    for (auto u : edges[v]) {
        if (u == p) continue;
        d[v][k] = (d[v][k] ^ D(u, v, (k - 1 + K) % K));
    }

    return d[v][k];
}

int U(int v, int k) {
    if (u[v][k] != -1) {
        return u[v][k];
    }

    if (padre[v] == -1) {
        u[v][k] = 0;
        return u[v][k];
    }

    u[v][k] = U(padre[v], (k - 1 + K) % K);                              // meto el up de mi padre
    u[v][k] = (u[v][k] ^ D(padre[v], padre[padre[v]], (k - 1 + K) % K)); // meto el down de mi padre
    u[v][k] = (u[v][k] ^ D(v, padre[v], (k - 2 + K) % K));               // quito lo que aporté yo al down de mi padre

    return u[v][k];
}

int main() {

    int n, k;
    cin >> n >> k;

    K = 2 * k;

    d.resize(n, vector<int>(2 * k, -1));
    u.resize(n, vector<int>(2 * k, -1));
    edges.resize(n);
    A.resize(n);
    padre.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    dfs(0, -1);

    /*for(int i = 0; i<n; i++){
        for(int j = 0; j<K; j++){
            cout<<i<<" "<<j<<": "<<U(i, j)<<endl;
        }
    }
    cout<<endl;
    */
    for (int i = 0; i < n; i++) {
        int chor = 0;
        for (int j = 0; j < k; j++) {
            chor = (chor ^ U(i, k + j));
            chor = (chor ^ D(i, padre[i], k + j));
        }
        if (chor != 0) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }
    cout << "\n";

    return 0;
}