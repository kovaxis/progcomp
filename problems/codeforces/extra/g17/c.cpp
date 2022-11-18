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
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<pair<T, int>, T>> node;

    Stl() {}

    void build(int v, int vl, int vr) {
        node[v] = {{1e9, -vr}, 0};
        if (vl != vr) {
            int vm = (vl + vr) / 2;
            build(2 * v, vl, vm);
            build(2 * v + 1, vm + 1, vr);
        }
    }

    void assign(int N) {
        node.resize(4 * N);  // query-zero, update-zero
        build(1, 0, N - 1);
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first.first += lazy;      // update-op & query-op mix
        node[2 * v].second += lazy;           // update-op
        node[2 * v + 1].first.first += lazy;  // update-op & query-op mix
        node[2 * v + 1].second += lazy;       // update-op
        lazy = 0;                             // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first.first += val;  // update-op & query-op mix
            node[v].second += val;       // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l > r) return;
        if (l <= vm) update(l, min(r, vm), val, 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
        node[v].first =
            min(node[2 * v].first, node[2 * v + 1].first);  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    pair<T, int> query_find2(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        pair<T, int> val = {1e9, -l};  // query-zero
        if (l > r) return val;
        if (l <= vm)
            val = min(val,
                      query_find2(l, min(r, vm), 2 * v, vl, vm));  // query-op
        if (r >= vm + 1)
            val = min(val, query_find2(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                                       vr));  // query-op
        return val;
    }

    pair<T, int> query_find(int l, int r) {
        auto x = query_find2(l, r);
        x.second = -x.second;
        return x;
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    T query(int l, int r) { return query_find(l, r).first; }
};

int N, ppl;
vector<ll> poorlimits, richlimits;
Stl<ll> rl;

void getlimits(ll& limit, int& limiter, ll& secondlimit) {
    auto x = rl.query_find(0, N - 1);
    limit = x.first;
    limiter = x.second;
    secondlimit =
        min(rl.query(0, limiter - 1) + 1, rl.query(limiter + 1, N - 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        richlimits.resize(N), poorlimits.resize(N), rl.assign(N), ppl = 0;
        rep(i, N) {
            cin >> richlimits[i];
            cin >> poorlimits[i];
        }

        rep(i, N) {
            /*cerr << "RL:";
            rep(j, i) {
                ll x = rl.query(j, j);
                cerr << " " << (x >= 1e8 ? -1 : x);
            }
            cerr << " X" << endl;*/
            auto x = rl.query_find(0, i - 1);
            ll limit = x.first;
            int limiter = x.second;
            if (poorlimits[i] < ppl - 1) continue;
            if (limit <= 0 || poorlimits[i] == ppl - 1) {
                // raise limit
                rl.update(limiter, limiter, 1e9 - limit);
                rl.update(limiter + 1, i - 1, -1);
                rl.update(i, i, richlimits[i] - 1e9);
                if (rl.query(0, i) < limit) {
                    // abort if limit didn't raise
                    rl.update(limiter, limiter, limit - 1e9);
                    rl.update(limiter + 1, i - 1, 1);
                    rl.update(i, i, 1e9 - richlimits[i]);
                }
            } else {
                // increase amount of people
                rl.update(0, i - 1, -1);
                rl.update(i, i, richlimits[i] - 1e9);
                ppl += 1;
            }
        }
        /*cerr << "RL:";
        rep(j, N) {
            ll x = rl.query(j, j);
            cerr << " " << (x >= 1e8 ? -1 : x);
        }
        cerr << endl;*/

        /*cerr << "RL:";
        rep(j, i) {
            ll x = rl.query(j, j);
            cerr << " " << (x >= 1e8 ? -1 : x);
        }
        cerr << " X" << endl;*/
        // cerr << "checking person " << i << " with a = " << richlimits[i]
        //     << " and b = " << poorlimits[i] << endl;
        /*
        int limiter;
        ll limit, secondlimit;
        getlimits(limit, limiter, secondlimit);
        secondlimit = min(secondlimit - 1, richlimits[i]);
        // cerr << " limit = " << limit << ", limiter = " << limiter
        //     << ", secondlimit = " << secondlimit << endl;
        if (poorlimits[i] < ppl - 1)
            continue;  // would have to remove 2 poors
        if (limit <= 0 || poorlimits[i] == ppl - 1) {
            // cerr << " removing limiter" << endl;
            if (secondlimit <= limit) {
                // cerr << "  RL would not raise, aborting" << endl;
                continue;
            }
            rl.update(limiter, limiter, 1e9 - limit);
            rl.update(0, limiter - 1, 1);
            ppl--;
        }
        /*
        if (limit <= 0) {
            // must remove the limiter
            // only convenient if it would raise the rich limit
            if (secondlimit <= limit) continue;
             cerr << "removing limiter at " << limiter << endl;
            rl.update(limiter, limiter, 1e9 - limit);
            ppl--;
        } else if (poorlimits[i] == ppl - 1) {
            // must remove 1 poor
            // only convenient if it would raise the rich limit
            if (secondlimit <= limit) continue;
             cerr << "removing poor at " << limiter << endl;
            rl.update(limiter, limiter, 1e9 - limit);
            ppl--;
        }
        */
        /*
        // add this person
        // cerr << " adding person" << endl;
        rl.update(i, i, richlimits[i] - 1e9);
        ppl++;
        // lower the rich limit of previous people by 1
        rl.update(0, i - 1, -1);
        */

        cout << ppl << '\n';
    }
}
