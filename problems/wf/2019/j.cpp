#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

struct Vertex {
    ll x, y, m;
};

int N, M;
vector<vector<ll>> H;
vector<vector<Vertex>> A;
vector<ll> interesting;
vector<int> cur_ind, ans;

ll eval_at(int i, ll x) {
    int &ind = cur_ind[i];
    while (ind < (int)A[i].size() - 1 && A[i][ind + 1].x <= x) ind += 1;
    return A[i][ind].y + (x - A[i][ind].x) * A[i][ind].m;
}

vector<int> pos2idx, idx2pos;
map<int, set<int>> groups;

void set_pos(int i, int p) {
    pos2idx[p] = i;
    idx2pos[i] = p;
}

// assumes p is in some group!
void group_remove(int p) {
    auto it = --groups.upper_bound(p);
    it->second.erase(p);
    if (it->second.empty()) groups.erase(it);
}

// assumes p not in any group
void group_add(int p, ll x) {
    // try merge with below
    auto it = groups.upper_bound(p);
    if (it != groups.begin()) {
        --it;

        int p2 = *it->second.begin();
        if (eval_at(pos2idx[p2], x) == eval_at(pos2idx[p], x)) {
            // merge with below
            it->second.insert(p);
            return;
        }
    }
    // try merge with above
    it = groups.upper_bound(p);
    if (it != groups.end()) {
        int p2 = *it->second.begin();
        if (eval_at(pos2idx[p2], x) == eval_at(pos2idx[p], x)) {
            // merge with above
            it->second.insert(p);
            return;
        }
    }
    // could not merge, form new group
    set<int> group;
    group.insert(p);
    groups.insert({p, group});
}

int upper_pos_of(int p) {
    set<int> &group = (--groups.upper_bound(p))->second;
    return *(--group.end());
}

void single_interest(ll x, int i, int j) {
    x *= 512;
    x += i;
    x *= 512;
    x += j;
    interesting.push_back(x);
}

void interest(ll x, int i, int j) {
    single_interest(x, i, j);
    single_interest(x + 1, i, j);
}

ll interest_x(ll x) {
    x /= 512;
    x /= 512;
    return x;
}

pair<int, int> interest_ij(ll x) {
    int j = x % 512;
    x /= 512;
    int i = x % 512;
    return {i, j};
}

int signum(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    H.resize(N, vector<ll>(M));
    rep(i, N) rep(j, M) cin >> H[i][j];

    A.resize(N);
    rep(i, N) {
        sort(H[i].begin(), H[i].end());
        ll x = 0, y = 0, m = M;
        A[i].push_back({x, y, m});
        for (ll x2 : H[i]) {
            y += (x2 - x) * m;
            x += x2 - x;
            m -= 1;
            if (x == A[i].back().x) A[i].pop_back();
            A[i].push_back({x, y, m});
        }
        A[i].push_back({ll(1e15) + 2, A[i].back().y, 0});
    }

    rep(i, N) {
        cerr << "line " << i + 1 << ":";
        for (auto v : A[i]) cerr << " (" << v.x << ", " << v.y << ")";
        cerr << endl;
    }

    rep(i, N) rep(j, N) if (i < j) {
        cerr << "processing intersections between " << i + 1 << " and " << j + 1 << endl;
        int ik = 0, jk = 0;
        while (ik < (int)A[i].size() - 1 && jk < (int)A[j].size() - 1) {
            Vertex i1 = A[i][ik];
            Vertex j1 = A[j][jk];
            Vertex i2 = A[i][ik + 1];
            Vertex j2 = A[j][jk + 1];
            ll x1 = max(i1.x, j1.x);
            ll x2 = min(i2.x, j2.x);

            ll iy1 = i1.y + (x1 - i1.x) * i1.m;
            ll jy1 = j1.y + (x1 - j1.x) * j1.m;
            ll iy2 = i1.y + (x2 - i1.x) * i1.m;
            ll jy2 = j1.y + (x2 - j1.x) * j1.m;

            int l = signum(iy1 - jy1);
            int r = signum(iy2 - jy2);
            cerr << "    type (" << l << ", " << r << ") intersection at vertices " << ik << " and " << jk << endl;

            if (x2 == i2.x) ik++;
            if (x2 == j2.x) jk++;

            if (l * r > 0) continue;
            if (l * r < 0) {
                // intersection
                ll num = iy1 - jy1;
                ll den = j1.m - i1.m;
                assert(den != 0);
                if (den < 0) {
                    num *= -1, den *= -1;
                }
                ll x = x1 + (num + den - 1) / den;
                cerr << "    lines intersect at or before " << x << endl;
                interest(x, i, j);
                continue;
            }
            interest(x1, i, j);
        }
    }

    pos2idx.resize(N), idx2pos.resize(N);
    rep(i, N) pos2idx[i] = i, idx2pos[i] = i;
    rep(i, N) groups[0].insert(i);

    ans.assign(N, N - 1);

    cur_ind.assign(N, 0);
    sort(interesting.begin(), interesting.end());
    for (int iii = 0; iii < (int)interesting.size();) {
        vector<int> J;
        ll x = interest_x(interesting[iii]);
        while (iii < (int)interesting.size() && interest_x(interesting[iii]) == x) {
            auto [i, j] = interest_ij(interesting[iii]);
            J.push_back(i);
            J.push_back(j);
            iii += 1;
        }
        sort(J.begin(), J.end());
        J.erase(unique(J.begin(), J.end()), J.end());

        cerr << "interesting lines at x = " << x << ":" << endl
             << "   ";
        for (int i : J) cerr << " " << i + 1;
        cerr << endl;

        sort(J.begin(), J.end(), [&](int i, int j) {
            return eval_at(i, x) < eval_at(j, x);
        });

        vector<int> positions;
        for (int i : J) positions.push_back(idx2pos[i]);
        sort(positions.begin(), positions.end());

        cerr << "    assigning indices";
        for (int i : J) cerr << " " << i + 1;
        cerr << " positions";
        for (int p : positions) cerr << " " << p;
        cerr << endl;

        rep(ii, (int)J.size()) set_pos(J[ii], positions[ii]);

        for (int p : positions) group_remove(p);
        for (int p : positions) group_add(p, x);

        for (int p : positions) {
            int i = pos2idx[p];
            int lp = upper_pos_of(p);
            cerr << "    pos of " << i + 1 << " is " << p << ", lower pos is " << lp << endl;
            ans[i] = min(ans[i], lp);
        }
    }

    rep(i, N) cout << ans[i] + 1 << "\n";
}
