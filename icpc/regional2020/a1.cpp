#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

void addnums(int x, int y) { cout << "1 " << x << "\n1 " << y << "\n"; }

struct Plan {
    bitset<501> req;
    int j;
    int subplans[2];
};

Plan planrepo[1000000];
int repo_n = 0;

vector<int> numplans[501];
bool built[501];

void build(int n, int plan_idx) {
    if (built[n]) return;
    built[n] = true;
    Plan& plan = planrepo[plan_idx];
    build(plan.j, plan.subplans[0]);
    build(n - plan.j, plan.subplans[1]);
    addnums(plan.j, n - plan.j);
}

void nest_needed(int n, int plan_idx, ll* out) {
    if (built[n]) return;
    built[n] = true;
    *out += 1;
    Plan& plan = planrepo[plan_idx];
    nest_needed(plan.j, plan.subplans[0], out);
    nest_needed(n - plan.j, plan.subplans[1], out);
}

ll calc_needed(int n) {
    rep(i, n + 1) built[i] = false;
    built[1] = true;
    ll out = 0;
    nest_needed(n, numplans[n][0], &out);
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    cin >> m >> n;
    if (m != 1) {
        cout << "*\n";
        return 0;
    }

    planrepo[repo_n++] = {0b10, 0, {0, 0}};
    numplans[1] = {0};
    rep(i, 2, n + 1) {
        int mincost = INT32_MAX;
        int planrepo_top = repo_n;
        rep(j, 1, i / 2 + 1) {
            for (int p0_idx : numplans[j]) {
                auto& p0 = planrepo[p0_idx];
                for (int p1_idx : numplans[i - j]) {
                    auto& p1 = planrepo[p1_idx];
                    auto buildset = p0.req | p1.req;
                    buildset.set(i);
                    int cost = buildset.count();
                    if (cost < mincost) {
                        mincost = cost;
                        repo_n = planrepo_top;
                        numplans[i].clear();
                    }
                    if (cost <= mincost) {
                        numplans[i].push_back(repo_n);
                        planrepo[repo_n++] = {buildset, j, {p0_idx, p1_idx}};
                    }
                }
            }
        }
        cerr << "building " << i << " has " << numplans[i].size()
             << " plans of cost " << mincost << endl;
    }

    built[1] = true;
    build(n, numplans[n][0]);

    ll needed = 0;
    rep(i, 1, n + 1) cout << calc_needed(i) << " ";
    // cout << "sum: " << needed << endl;
}
