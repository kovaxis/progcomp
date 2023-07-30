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

const ll INF = 1e18;

int N, Q, M;
vector<int> L, D, Qmin, Qbase, Qmax;

struct State {
    vector<set<pair<ll, int>>> q_set;
    vector<ll> q_to_score;
    vector<pair<int, int>> q_to_u_i;
    vector<vector<int>> u_i_to_q;
    vector<int> count_by_u;
    int next_universal_free = 0;
    int faults = 0;
    int time = 0;

    // algo conf
    string name;
    function<ll(const State &, int, int, ll)> getscore;

    State() {
        q_set.resize(N);
        q_to_score.assign(Q, 1e18);
        q_to_u_i.assign(Q, {N, 0});
        u_i_to_q.resize(N);
        rep(u, N) u_i_to_q[u].assign(D[u], -1);
        count_by_u.assign(N, 0);
    }

    int choose(int u, int i) {
        if (u_i_to_q[u][i] != -1) {
            cerr << "page hit at " << u_i_to_q[u][i] + 1 << endl;
            return u_i_to_q[u][i];
        }

        if (count_by_u[u] < Qmax[u] && next_universal_free < Q) {
            cerr << "using universal free page at " << next_universal_free + 1 << endl;
            return next_universal_free;
        }

        cerr << "finding someone to evict" << endl;
        ll mn_score = 1e18;
        int mn_u = 0, mn_q = -1;
        rep(v, N) {
            cerr << "  checking user " << v + 1 << endl;
            if (count_by_u[u] <= Qmin[u] && u == v) {
                        }
            if (count_by_u[u] >= Qmax[u] && v != u) {
                cerr << "    skipping, user " << u + 1 << " cannot evict other users" << endl;
                continue;
            }
            if (count_by_u[v] <= Qmin[v] && u != v) {
                cerr << "    skipping, user " << v + 1 << " has too little pages to be evicted" << endl;
                continue;
            }
            if (q_set[v].empty()) continue;
            auto p = *q_set[v].begin();
            ll s = p.first;
            int q = p.second;
            s *= L[u];
            cerr << "    checking out page at " << q + 1 << " with score " << s << endl;
            if (s < mn_score) mn_score = s, mn_u = v, mn_q = q;
        }
        cerr << "evicting page from user " << mn_u + 1 << " at " << mn_q + 1 << endl;
        assert(mn_q >= 0);
        return mn_q;
    }

    int apply(int q, int u, int i) {
        bool is_hit = u_i_to_q[u][i] != -1;

        if (!is_hit && count_by_u[u] < Qmax[u] && next_universal_free < Q) {
            next_universal_free++;
        }

        ll pscore = INF;

        auto [old_u, old_i] = q_to_u_i[q];
        if (old_u < N) {
            ll old_score = q_to_score[q];
            if (is_hit) pscore = old_score;
            q_set[old_u].erase({old_score, q});
            q_to_score[q] = 1e18;
            u_i_to_q[old_u][old_i] = -1;
            count_by_u[old_u] -= 1;
        }

        q_to_u_i[q] = {u, i};

        ll score = getscore(*this, u, i, pscore);

        q_set[u].insert({score, q});
        q_to_score[q] = score;
        u_i_to_q[u][i] = q;
        count_by_u[u] += 1;

        faults += !is_hit;
        time += 1;
        return q;
    }

    friend ostream &operator<<(ostream &s, const State &self) {
        rep(q, Q) {
            s << self.q_to_u_i[q].first;
        }
        s << "  (" << self.faults << " faults)";
        return s;
    }
};

const int SOLN = 1;
State sols[SOLN];

void show() {
    rep(k, SOLN) cerr << sols[k].name << ": " << sols[k] << endl;
}

void reset() {
    rep(k, SOLN) sols[k] = {};
    int k = 0;
    State *s;

    // LFU
    s = &sols[k++];
    s->name = "lfu";
    s->getscore = [](const State &s, int u, int i, ll p) { return p == INF ? s.time : p; };

    assert(k == SOLN);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> M;
    L.resize(N), D.resize(N), Qmin.resize(N), Qbase.resize(N), Qmax.resize(N);
    rep(i, N) cin >> L[i];
    rep(i, N) cin >> D[i];
    rep(i, N) cin >> Qmin[i] >> Qbase[i] >> Qmax[i];

    reset();

    show();
    rep(j, M) {
        int u, i;
        cin >> u >> i;
        u--, i--;
        int q = sols[0].apply(sols[0].choose(u, i), u, i);
        cout << 1 + q << endl;

        show();
    }

    cerr << "faults: " << sols[0].faults << "/" << M << endl;
}