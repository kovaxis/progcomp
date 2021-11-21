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
vector<int> adj[200];
int reach[200];
vector<int> parents[200];
vector<int> children[200];
ll pathsup[200];
ll pathsdn[200];
ll pathw[200][200];
bool marked[200];

ll visit(vector<int> parents[], ll pathcounts[], int i) {
    if (pathcounts[i] != 0) return pathcounts[i];
    ll pc = 0;
    for (int parent : parents[i]) {
        pc += visit(parents, pathcounts, parent);
    }
    pathcounts[i] = pc;
    // cerr << "city " << i << ": " << pc << " paths" << endl;
    return pc;
}

void markw(int i) {
    if (marked[i]) return;
    marked[i] = true;
    for (int child : children[i]) {
        ll w = pathsup[i] * pathsdn[child];
        pathw[i][child] = w;
        pathw[child][i] = w;
        markw(child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M;
    cin >> N >> M;
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> cur;
    set<int> nxt;
    int gen = 0;
    cur.insert(0);
    rep(i, N) reach[i] = INT32_MAX;
    reach[0] = 0;
    while (!cur.empty()) {
        gen += 1;
        for (int i : cur) {
            for (int j : adj[i]) {
                if (reach[j] < gen) continue;
                if (parents[j].empty()) nxt.insert(j);
                reach[j] = gen;
                parents[j].push_back(i);
                children[i].push_back(j);
            }
        }
        swap(cur, nxt);
        nxt.clear();
    }

    // cerr << "checking paths up:" << endl;
    pathsup[0] = 1;
    visit(parents, pathsup, N - 1);
    // cerr << "checking paths down:" << endl;
    pathsdn[N - 1] = 1;
    visit(children, pathsdn, 0);
    markw(0);

    ll maxw = 0;
    rep(i, N) {
        ll w = 0;
        for (int j : adj[i]) w += pathw[i][j];
        maxw = max(maxw, w);
    }

    double avg = (double)maxw / (double)pathsdn[0];
    cout << fixed << setw(12) << setprecision(12) << avg << '\n';
}
