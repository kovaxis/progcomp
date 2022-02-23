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

template <class T>
struct St {
    vector<T> node;

    St() {}
    void resize(int N) { node.assign(4 * N, 0); }

    T query_sum(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;  // neutral element
        if (l > r) return val;
        if (l <= vm)
            val += query_sum(l, min(r, vm), 2 * v, vl, vm);  // query op
        if (r >= vm + 1)
            val += query_sum(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                             vr);  // query op
        return val;
    }

    // get the leftmost `i` position where the sum of [0, i] is geq to `val`.
    T query_pos(T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        // cerr << "finding the leftmost index in [" << vl << ", " << vr
        //     << "] such that +[0, i] >= " << val << endl;
        if (vl == vr) return node[v] >= val ? vl : vl + 1;
        int vm = (vl + vr) / 2;
        if (node[2 * v] >= val) return query_pos(val, 2 * v, vl, vm);
        return query_pos(val - node[2 * v], 2 * v + 1, vm + 1, vr);
    }

    void add(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] += val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i <= vm) {
            add(i, val, 2 * v, vl, vm);
        } else {
            add(i, val, 2 * v + 1, vm + 1, vr);
        }
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }
};

int N, Q;
vector<int> P;
vector<vector<int>> G;
vector<int> label;
vector<int> ans;
// vertex -> {idx, {L, K}}
vector<vector<pair<int, pair<int, int>>>> queries;
// num -> freq
vector<int> num2freq;
// freq -> set of numbers with that freq
vector<set<int>> freq2num;
// freq -> amount of nums
St<int> distr;

void __attribute__((noinline)) push(int v) {
    int num = label[v];
    int& freq = num2freq[num];
    if (freq != 0) distr.add(freq, -1), freq2num[freq].erase(num);
    freq += 1;
    distr.add(freq, 1), freq2num[freq].insert(num);
}

void __attribute__((noinline)) process(int v) {
    for (auto& q : queries[v]) {
        int i = q.first, l = q.second.first, k = q.second.second;
        // cerr << "querying node " << v + 1 << " for L = " << l << ", K = " <<
        // k << endl;
        k += distr.query_sum(0, l - 1);
        // cerr << "  K' = " << k << endl;
        int freq = distr.query_pos(k);
        ans[i] = freq == N + 1 ? -1 : *freq2num[freq].begin() + 1;
        // cerr << "  ans = " << ans[i] << endl;
    }
}

void __attribute__((noinline)) pop(int v) {
    int num = label[v];
    int& freq = num2freq[num];
    distr.add(freq, -1), freq2num[freq].erase(num);
    freq -= 1;
    if (freq != 0) distr.add(freq, 1), freq2num[freq].insert(num);
}

void visit(int v) {
    push(v);
    process(v);
    for (int c : G[v]) visit(c);
    pop(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> Q;
        P.resize(N), G.assign(N, {}), label.resize(N), queries.assign(N, {}),
            ans.resize(Q), num2freq.assign(N, 0), freq2num.resize(N + 1),
            distr.resize(N + 1);
        rep(v, N) cin >> label[v];
        rep(v, N) label[v] -= 1;
        rep(v, 1, N) {
            cin >> P[v];
            P[v] -= 1;
        }
        rep(q, Q) {
            int v, l, k;
            cin >> v >> l >> k;
            queries[v - 1].push_back({q, {l, k}});
        }

        rep(v, 1, N) G[P[v]].push_back(v);

        visit(0);

        rep(q, Q) cout << ans[q] << " \n"[q == Q - 1];
    }
}
