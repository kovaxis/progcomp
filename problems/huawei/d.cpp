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

struct SolState {
    vector<set<pair<ll, int>>> q_set;
    vector<ll> q_to_score;
    vector<pair<int, int>> q_to_u_i;
    vector<vector<int>> u_i_to_q;
    vector<int> count_by_u;
    vector<vector<int>> u_i_to_freq;
    int next_free = 0;
    int time = 0;

    int ghost_faults = 0;

    // algo config
    string name;
    bool reset_freq = false;
    function<ll(const SolState &, int, int, ll)> getscore;
    function<ll(const SolState &, int, int, ll)> adjscore = [](auto &s, int u, int v, ll p) { return p; };

    SolState() {
        q_set.resize(N);
        q_to_u_i.assign(Q, {N, 0});
        u_i_to_q.resize(N);
        rep(u, N) u_i_to_q[u].assign(D[u], -1);
        count_by_u.assign(N, 0);
        q_to_score.assign(Q, 1e18);
        u_i_to_freq.resize(N);
        rep(u, N) u_i_to_freq[u].assign(D[u], 0);
    }

    // simulate a `u, i` query, and what would the answer be
    int where(int u, int i) {
        cerr << "choosing where to place page " << i + 1 << " for user " << u + 1 << endl;
        int ans_q = -1;
        if (u_i_to_q[u][i] != -1) {
            ans_q = u_i_to_q[u][i];
            cerr << "page hit at " << ans_q + 1 << endl;
        } else if (count_by_u[u] < Qmax[u] && next_free < Q) {
            ans_q = next_free;
            cerr << "using free page at " << ans_q + 1 << endl;
        } else {
            cerr << "finding someone to evict" << endl;
            ll mn_score = 1e18;
            int mn_u = 0, mn_q = -1;
            rep(v, N) {
                cerr << "  checking user " << v + 1 << endl;
                if (count_by_u[u] < Qmin[u] && u == v) {
                    cerr << "    skipping, cannot self-replace page if under Qmin" << endl;
                    continue;
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
                auto pair = *q_set[v].begin();
                ll s = adjscore(*this, u, v, pair.first);
                int q = pair.second;
                cerr << "    checking out page at " << q + 1 << " with score " << s << endl;
                if (s < mn_score) mn_score = s, mn_u = v, mn_q = q;
            }
            cerr << "evicting page " << q_to_u_i[mn_q].second + 1 << " from user " << mn_u + 1 << " at frame " << mn_q + 1 << endl;
            assert(mn_q >= 0);
            ans_q = mn_q;
        }
        assert(ans_q >= 0);
        return ans_q;
    }

    // apply a page lookup
    // return the q
    int apply(int ans_q, int u, int i) {
        bool existed = q_to_u_i[ans_q].first != N;
        bool was_fault = q_to_u_i[ans_q] != make_pair(u, i);

        if (u_i_to_q[u][i] != -1) assert(!was_fault);

        if (was_fault && count_by_u[u] < Qmax[u] && next_free < Q) {
            assert(ans_q == next_free && !existed);
            next_free++;
        }

        ll old_score = INF;
        if (existed) {
            auto [ans_u, ans_i] = q_to_u_i[ans_q];
            ll ans_score = q_to_score[ans_q];
            if (!was_fault) old_score = ans_score;
            int rm = q_set[ans_u].erase({ans_score, ans_q});
            assert(rm);
            u_i_to_q[ans_u][ans_i] = -1;
            count_by_u[ans_u] -= 1;
            q_to_score[ans_q] = 1e18;
            if (was_fault && reset_freq) u_i_to_freq[ans_u][ans_i] = 0;
        }

        q_to_u_i[ans_q] = {u, i};

        u_i_to_freq[u][i] += 1;
        ll score = getscore(*this, u, i, old_score);

        q_set[u].insert({score, ans_q});
        u_i_to_q[u][i] = ans_q;
        count_by_u[u] += 1;
        q_to_score[ans_q] = score;

        ghost_faults += was_fault;
        time += 1;
        return ans_q;
    }

    void show() {
        rep(q, Q) {
            cerr << q_to_u_i[q].first;
        }
        cerr << endl;
    }

    friend ostream &operator<<(ostream &s, const SolState &self) {
        rep(q, Q) {
            s << self.q_to_u_i[q].first;
        }
        s << "  (" << self.ghost_faults << " faults)";
        return s;
    }
};

int active = 0;
const int SOLN = 7;
SolState sols[SOLN];
SolState bkup[SOLN];

void reset() {
    rep(k, SOLN) sols[k] = {};
    SolState *s;
    int k = 0;
    // LRU (p)
    s = &sols[k++];
    s->name = "lru_p";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return p == INF ? s.time + 32 * L[u] : p; };
    // LRU
    s = &sols[k++];
    s->name = "lru";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return s.time + 32 * L[u]; };
    // MRU
    s = &sols[k++];
    s->name = "mru";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return -s.time + 32 * L[u]; };
    // LFU
    s = &sols[k++];
    s->name = "lfu";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return s.u_i_to_freq[u][i] + 32 * L[u]; };
    // LFRU
    s = &sols[k++];
    s->name = "lfru";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return s.u_i_to_freq[u][i] * 64 + s.time + 32 * L[u]; };
    // LFRU (prefer hot)
    s = &sols[k++];
    s->name = "lfru hot";
    s->reset_freq = true;
    s->getscore = [](const SolState &s, int u, int i, ll p) { return s.u_i_to_freq[u][i] * 64 + s.time + 32 * L[u]; };
    // MFU
    s = &sols[k++];
    s->name = "mfu";
    s->getscore = [](const SolState &s, int u, int i, ll p) { return -s.u_i_to_freq[u][i] + 32 * L[u]; };

    assert(k == SOLN);
}

void show() {
    rep(k, SOLN) cerr << sols[k].name << " " << sols[k] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> M;
    L.resize(N), D.resize(N), Qmin.resize(N), Qbase.resize(N), Qmax.resize(N);
    rep(i, N) cin >> L[i];
    rep(i, N) cin >> D[i];
    rep(i, N) cin >> Qmin[i] >> Qbase[i] >> Qmax[i];

    // TODO: Insert some preparation code

    reset();
    rep(k, SOLN) bkup[k] = sols[k];

    vector<pair<pair<int, int>, int>> ops;
    show();
    int acc = 0, recomp = 10;
    rep(j, M) {
        int u, i;
        cin >> u >> i;
        u--, i--;

        if (acc >= recomp) {
            int mn_i = -1;
            ll mn_f = 1e18;
            rep(k, SOLN) if (sols[k].ghost_faults < mn_f) mn_i = k, mn_f = sols[k].ghost_faults;
            assert(mn_i >= 0);
            if (mn_f < sols[active].ghost_faults) {
                // switch algo
                cerr << "switching to algo " << mn_i + 1 << endl;
                int gf[SOLN];
                rep(k, SOLN) gf[k] = sols[k].ghost_faults;
                rep(k, SOLN) sols[k] = bkup[k];
                active = mn_i;
                for (auto [op, q] : ops) {
                    auto [u, i] = op;
                    rep(k, SOLN) {
                        sols[k].apply(q, u, i);
                    }
                }
                rep(k, SOLN) sols[k].ghost_faults = gf[k];

                if (recomp == 10) recomp = 50;
                else if (recomp == 50) recomp = 100;
                else if (recomp == 100) recomp = 500;
                else if (recomp == 500) recomp = 1200;

                rep(k, SOLN) bkup[k] = sols[k];
                ops.clear();

                acc = 0;
            }
        } else {
            acc += 1;
        }

        cerr << "active: " << active + 1 << endl;
        int qs[SOLN];
        rep(k, SOLN) {
            cerr << sols[k].name << ":" << endl;
            qs[k] = sols[k].apply(sols[k].where(u, i), u, i);
        }
        int q = qs[active];
        ops.push_back({{u, i}, q});

        cout << 1 + q << endl;

        show();
    }
}
