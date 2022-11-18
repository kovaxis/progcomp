#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

//#define cerr \
    if (0) cerr

int N;
vector<set<int>> G;
// eq[x][y][z] <-> d(x, z) = d(y, z)
bool eq[128][128][128];

vector<int> member;
vector<vector<int>> comps;
vector<int> halflvl;

void member_dfs(int u, int r, int i) {
    if (member[u] != -1) return;
    member[u] = i;
    comps[i].push_back(u);
    rep(v, N) {
        if (eq[u][v][r]) member_dfs(v, r, i);
    }
}

vector<bool> seen;

bool check_dfs(int u, int p) {
    if (seen[u]) return false;
    seen[u] = true;
    int n = 1;
    for (int v : G[u])
        if (v != p) {
            if (!G[v].count(u)) return false;
            if (!check_dfs(v, u)) return false;
        }
    return true;
}

vector<vector<int>> D;
void dist_dfs(int r, int u, int p, int d) {
    D[r][u] = d;
    for (int v : G[u])
        if (v != p) dist_dfs(r, v, u, d + 1);
}

bool solve() {
    rep(r, N) {
        // determine neighborhood of r
        cerr << "getting neigborhood of r = " << r + 1 << endl;

        // find level components
        member.assign(N, -1);
        comps.clear();
        member[r] = -2;
        rep(v, N) {
            if (member[v] == -1) {
                int i = comps.size();
                comps.push_back({});
                member_dfs(v, r, i);
            }
        }
        cerr << "  components:" << endl;
        rep(i, comps.size()) {
            cerr << "    [" << i << "]:";
            for (int u : comps[i]) cerr << " " << u + 1;
            cerr << endl;
        }

        // find the half-level for each level
        cerr << "  half-levels:" << endl;
        halflvl.assign(comps.size(), -1);
        rep(i, comps.size()) {
            int v = comps[i].front();
            rep(m, N) if (eq[v][r][m]) {
                // found the midpoint node
                halflvl[i] = member[m];
                break;
            }
            cerr << "    [" << i << "]: " << halflvl[i] << endl;
        }

        // determine the node with maximum length path
        int maxlen = -1, maxi = -1;
        rep(i, comps.size()) {
            int j = i, len = 1;
            while (len < 10 && halflvl[j] >= 0) j = halflvl[j], len += 1;
            if (len >= 10) {
                cerr << "  half-path is too long" << endl;
                return false;
            }
            if (len > maxlen) maxlen = len, maxi = j;
        }
        cerr << "  root-level: " << maxi << endl;
        if (maxi < 0) return false;

        // component `maxi` is the neighborhood of r
        for (int v : comps[maxi]) G[r].insert(v);
        cerr << "  neighborhood of " << r + 1 << ":";
        for (int v : G[r]) cerr << " " << v + 1;
        cerr << endl;
    }

    // check that oriented graph is a tree
    seen.assign(N, false);
    if (!check_dfs(0, -1)) {
        cerr << "found loops" << endl;
        return false;
    }
    rep(u, N) if (!seen[u]) {
        cerr << "node " << u + 1 << " is disconnected" << endl;
        return false;
    }

    // check that tree is consistent with `eq`
    D.assign(N, vector<int>(N));
    rep(r, N) dist_dfs(r, r, -1, 0);
    rep(x, N) rep(y, N) rep(z, N) {
        if (eq[x][y][z] != (D[x][z] == D[y][z])) {
            cerr << "inconsistent x = " << x + 1 << ", y = " << y + 1
                 << ", z = " << z + 1 << endl;
            return false;
        }
    }
    return true;
}

void ans_dfs(int u, int p) {
    for (int v : G[u])
        if (v != p) {
            cout << u + 1 << " " << v + 1 << "\n";
            ans_dfs(v, u);
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // maximum allowed complexity: O(N^3)

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        rep(i, N - 1) rep(j, N - i - 1) rep(k, N) {
            char c;
            cin >> c;
            eq[i][i + j + 1][k] = eq[i + j + 1][i][k] = (c == '1');
        }
        rep(i, N) rep(k, N) eq[i][i][k] = true;

        G.assign(N, {});
        if (solve()) {
            cout << "Yes\n";
            ans_dfs(0, -1);
        } else {
            cout << "No\n";
        }
        // cout << endl;
    }
}
