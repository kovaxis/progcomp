#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Edge {
    int v;
    int l, r, n;
};

int N, M, An, start;
string A;
vector<vector<Edge>> G, Ginv;

vector<bool> has_ans;
vector<pair<string, vector<Edge>>> ans;

void visit(int u, string &s, vector<Edge> &path) {
    int og_len = s.size();
    for (Edge e : G[u]) {
        s.append(A.begin() + e.l, A.begin() + e.r);
        path.push_back(e);
        visit(e.v, s, path);
        s.resize(og_len);
        path.pop_back();
    }

    if (has_ans[u] && s >= ans[u].first) return;
    ans[u] = {s, path};
    has_ans[u] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> An >> start >> A;
    start -= 1;
    An = A.size();
    G.resize(N);
    Ginv.resize(N);
    rep(j, M) {
        int u, v, l, n;
        cin >> u >> v >> l >> n;
        u -= 1, v -= 1, l -= 1;
        G[u].push_back({v, l, l + n, n});
        Ginv[v].push_back({u, l, l + n, n});
    }

    has_ans.assign(N, false);
    ans.resize(N);
    string s;
    vector<Edge> p;
    visit(start, s, p);

    rep(u, N) {
        if (has_ans[u]) {
            cout << ans[u].second.size() + 1 << " " << start + 1;
            for (Edge e : ans[u].second) cout << " " << e.v + 1;
            cout << "\n";
        } else {
            cout << "0\n";
        }
    }
}
