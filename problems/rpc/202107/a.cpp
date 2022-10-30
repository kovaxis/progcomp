#include <bits/stdc++.h>
using namespace std;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define ff first
#define ss second
#define pb push_back

struct LCA {
    vector<vi> G;
    int N, LOG;
    vi A, D;
    int &anc(int u, int l) { return A[l * N + u]; }
    LCA(vector<vi> &G, int N, int root) : G(G), N(N) {
        D.assign(N, -1);
        A.resize(N * (LOG + 1));
        dfs(root, -1, 0), LOG = 31 - __builtin_clz(N);
        rep(l, LOG + 1) if (l) rep(u, N) {
            int a = anc(u, l - 1);
            anc(u, l) = (a == -1 ? -1 : anc(a, l - 1));
        }
    }
    void dfs(int u, int p, int depth) {
        anc(u, 0) = p, D[u] = depth;
        for (int v : G[u])
            if (D[v] == -1) dfs(v, u, depth + 1);
    }
    int raise(int u, int k) {
        for (int l = 0; k; l++, k >>= 1)
            if (k & 1) u = anc(u, l);
        return u;
    }
    int lca(int u, int v) {
        if (D[u] < D[v]) swap(u, v);
        u = raise(u, D[u] - D[v]);
        if (u == v) return u;
        for (int l = LOG; l >= 0; l--)
            if (anc(u, l) != anc(v, l)) u = anc(u, l), v = anc(v, l);
        return anc(u, 0);
    }

    ii lca_adj(int u, int v) {  // dif de profundidad de u, profundidad de v
        int aux1 = u, aux2 = v;
        if (D[u] < D[v]) {
            swap(u, v);
        }
        u = raise(u, D[u] - D[v]);
        if (u == v) return {D[aux1] - D[u], D[aux2] - D[u]};
        for (int l = LOG; l >= 0; l--)
            if (anc(u, l) != anc(v, l)) u = anc(u, l), v = anc(v, l);
        return {D[aux1] - D[anc(u, 0)], D[aux2] - D[anc(u, 0)]};
    }

    int dist(int u, int v) { return D[u] + D[v] - 2 * D[lca(u, v)]; }
    int raise_in_path(int u, int v, int k) {
        if (D[u] - D[lca(u, v)] >= k) return raise(u, k);
        return raise(v, dist(u, v) - k);
    }
};

string str(int i) {
    if (i % 10 == 1 and i != 11) return "st";
    if (i % 10 == 2 and i != 12) return "nd";
    if (i % 10 == 3 and i != 13) return "rd";
    return "th";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, q;
    cin >> t >> q;
    map<string, int> nodo;
    map<int, string> nombre;
    string a, b;
    vector<vi> G(100, vi());
    vector<int> parent(100, -1);
    int contador = 0;
    rep(i, t) {
        cin >> a;
        int x;
        cin >> x;
        if (!nodo.count(a)) {
            nodo[a] = contador;
            nombre[contador++] = a;
        }
        rep(j, x) {
            cin >> b;
            if (!nodo.count(b)) {
                nodo[b] = contador;
                nombre[contador++] = b;
            }
            G[nodo[a]].push_back(nodo[b]);
            parent[nodo[b]] = nodo[a];
        }
    }
    int u = 0;
    while (parent[u] != -1) u = parent[u];
    G.resize(contador);
    LCA lca = LCA(G, contador, u);
    while (q--) {
        cin >> a >> b;
        int n, m;
        tie(m, n) = lca.lca_adj(nodo[a], nodo[b]);
        if (m == 0 or n == 0) {
            if (n == 0) swap(a, b);
            if (m == 1 or n == 1)
                cout << b << " is the child of " << a << "\n";
            else {
                cout << b << " is the ";
                rep(i, max(n - 2, m - 2)) cout << "great ";
                cout << "grandchild of " << a << '\n';
            }
        } else if (m == n) {
            if (n == 1)
                cout << a << " and " << b << " are siblings\n";
            else
                cout << a << " and " << b << " are " << n - 1 << str(n - 1)
                     << " cousins\n";
        } else {
            if (n < m) swap(m, n);
            cout << a << " and " << b << " are " << m - 1 << str(m - 1)
                 << " cousins, " << abs(n - m);
            cout << (abs(n - m) == 1 ? " time " : " times ") << "removed"
                 << '\n';
        }
    }

    return 0;
}