#pragma GCC optimize("Ofast")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define LOG2(X) ((unsigned)(8 * sizeof(unsigned long long) - __builtin_clzll((X)) - 1))
#define MOD 1000000007
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

struct Node {
    int next[26];
    int cnt;
};

vector<Node> nodes;

int new_node_from(int node) {
    int u = nodes.size();
    nodes.emplace_back();
    rep(i, 26) nodes[u].next[i] = nodes[node].next[i];
    nodes[u].cnt = nodes[node].cnt + 1;
    return u;
}

vector<int> trie;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    int bucket = 4400;
    trie.resize(n + 1);
    vector<string> dicc(n);
    rep(i, n) cin >> dicc[i];

    vector<int> index(n);
    rep(i, n) index[i] = i;

    map<int, map<int, int>> pending;
    float elapsed = 0;
    rep(t, q) {
        if (t % bucket == 0) {
            pending.clear();
            nodes.clear();
            nodes.emplace_back();
            rep(i, 26) nodes[0].next[i] = -1;
            nodes[0].cnt = 0;

            int last_root = 0;
            trie[0] = 0;
            rep(i, n) {
                int u = last_root = trie[i + 1] = new_node_from(last_root);
                for (char c : dicc[index[i]]) {
                    if (nodes[u].next[c - 'a'] != -1)
                        u = nodes[u].next[c - 'a'] = new_node_from(nodes[u].next[c - 'a']);
                    else
                        u = nodes[u].next[c - 'a'] = new_node_from(0);
                }
            }
        }

        int type;
        cin >> type;
        if (type == 1) {
            int i, j;
            cin >> i >> j;
            i--;
            j--;
            pending[i][index[i]] -= 1;
            pending[i][index[j]] += 1;
            pending[j][index[j]] -= 1;
            pending[j][index[i]] += 1;
            swap(index[i], index[j]);

        } else {
            auto start = chrono::high_resolution_clock::now();
            string s;
            int k, l, r;
            cin >> s >> k >> l >> r;
            l--;
            r--;
            int u = trie[r + 1];
            rep(i, k) {
                if (u != -1) u = nodes[u].next[s[i] - 'a'];
            }
            int v = trie[l];
            rep(i, k) {
                if (v != -1) v = nodes[v].next[s[i] - 'a'];
            }
            int sum = 0;
            if (u != -1) sum += nodes[u].cnt;
            if (v != -1) sum -= nodes[v].cnt;

            for (auto u = pending.lower_bound(l); u != pending.upper_bound(r); u++) {
                for (auto v : u->second) {
                    int id = v.first;
                    if ((int)dicc[id].length() < k) continue;
                    bool equal = true;
                    rep(i, k) if (dicc[id][i] != s[i]) equal = false;
                    if (equal) sum += v.second;
                }
            }
            cout << sum << "\n";
            auto end = chrono::high_resolution_clock::now();
            elapsed += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
    }
    cerr << elapsed / 1e9 << endl;

    return 0;
}