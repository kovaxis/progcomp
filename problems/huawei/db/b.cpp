#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#ifdef ONLINE_JUDGE
#define cerr \
    if (0) cerr
#endif

int N, Q, M;
ll T;
vector<int> L, D, Qmin, Qbase, Qmax;

vector<priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>>> q_queue;
vector<pair<int, int>> q_to_u_i;
vector<vector<int>> u_i_to_q;
vector<int> count_by_u;
int next_universal_free = 0, next_reserved_free = 0;
int faults = 0;

int solve(int u, int i) {
    if (u_i_to_q[u][i] != -1) {
        cerr << "page hit at " << u_i_to_q[u][i] + 1 << endl;
        return u_i_to_q[u][i];
    }
    faults += 1;

    int ans_q = -1;
    if (count_by_u[u] < Qmin[u]) {
        ans_q = next_reserved_free++;
        cerr << "using reserved free page at " << ans_q + 1 << endl;
    } else if (next_universal_free < Q) {
        ans_q = next_universal_free++;
        cerr << "using universal free page at " << ans_q + 1 << endl;
    } else {
        cerr << "finding someone to evict" << endl;
        ll mn_score = 1e18;
        int mn_u = 0, mn_q = -1;
        rep(v, N) {
            cerr << "  checking user " << v + 1 << endl;
            if (count_by_u[u] >= Qmax[u] && v != u) {
                cerr << "    skipping, user " << u + 1 << " cannot evict other users" << endl;
                continue;
            }
            if (count_by_u[v] <= Qmin[v] && u != v) {
                cerr << "    skipping, user " << v + 1 << " has too little pages to be evicted" << endl;
                continue;
            }
            while (!q_queue[v].empty()) {
                auto [s, q] = q_queue[v].top();
                if (q_to_u_i[q].first != v) {
                    q_queue[v].pop();
                    cerr << "    skipping stale spot " << q + 1 << ", it now belongs to " << q_to_u_i[q].first + 1 << endl;
                    continue;
                }
                s *= L[u];
                cerr << "    checking out page at " << q + 1 << " with score " << s << endl;
                if (s < mn_score) mn_score = s, mn_u = v, mn_q = q;
                break;
            }
        }
        cerr << "evicting page from user " << mn_u + 1 << " at " << mn_q + 1 << endl;

        q_queue[mn_u].pop();
        u_i_to_q[mn_u][q_to_u_i[mn_q].second] = -1;
        count_by_u[mn_u] -= 1;
        ans_q = mn_q;
    }
    assert(ans_q >= 0);

    q_to_u_i[ans_q] = {u, i};

    q_queue[u].push({T, ans_q});
    u_i_to_q[u][i] = ans_q;
    count_by_u[u] += 1;
    return ans_q;
}

void show() {
    rep(q, Q) {
        cerr << q_to_u_i[q].first;
    }
    cerr << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> M;
    L.resize(N), D.resize(N), Qmin.resize(N), Qbase.resize(N), Qmax.resize(N);
    rep(i, N) cin >> L[i];
    rep(i, N) cin >> D[i];
    rep(i, N) cin >> Qmin[i] >> Qbase[i] >> Qmax[i];

    q_queue.resize(N);
    q_to_u_i.assign(Q, {N, 0});
    u_i_to_q.resize(N + 1);
    rep(u, N) u_i_to_q[u].assign(D[u], -1);
    count_by_u.assign(N, 0);
    rep(u, N) next_universal_free += Qmin[u];

    show();
    rep(j, M) {
        int u, i;
        cin >> u >> i;
        u--, i--;
        int q = solve(u, i);
        cout << 1 + q << endl;
        T++;

        show();
    }

    cerr << "faults: " << faults << "/" << M << endl;
}