#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N;
vector<int> a, ainv, p, q;
vector<vector<int>> cycles;
vector<bool> seen;

void swaprem(int i) {
    swap(cycles[i], cycles[cycles.size() - 1]);
    cycles.pop_back();
}

int k(vector<int> &k) {
    if (k.size() == 1) return 1e9;
    return k.size();
}

vector<int> build_huge() {
    vector<vector<int>> target;
    for (auto &cycle : cycles) {
        vector<int> rcycle = cycle;
        reverse(rcycle.begin(), rcycle.end());
        target.push_back(rcycle);
    }

    sort(target.begin(), target.end(), [](auto &a, auto &b) { return k(a) > k(b); });
    vector<int> huge;
    for (auto &cycle : target) {
        if (huge.empty()) {
            huge = cycle;
            continue;
        }
        if (cycle.size() == 2) {
            huge.push_back(cycle[0]);
            huge.push_back(huge[0]);
            huge[0] = cycle[1];
        } else {
            for (int x : cycle) huge.push_back(x);
        }
    }

    return huge;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];
        rep(i, N) a[i] -= 1;

        ainv.resize(N);
        rep(i, N) ainv[a[i]] = i;

        cycles.clear();
        seen.assign(N, false);
        rep(i, N) {
            if (seen[i]) continue;
            vector<int> cycle;
            int j = i;
            while (true) {
                seen[j] = true;
                cycle.push_back(j);
                j = ainv[j];
                if (j == i) break;
            }
            cycles.push_back(cycle);
        }

        cerr << "cycles:" << endl;
        for (auto &cycle : cycles) {
            cerr << " ";
            for (int x : cycle) cerr << " " << x + 1;
            cerr << endl;
        }

        if (N == 1 || (N == 2 && cycles.size() == 1) || (N == 3 && cycles.size() == 2)) {
            cout << "Impossible\n";
            continue;
        }

        vector<int> rcycle = build_huge();

        q.resize(N);
        rep(i, N) q[rcycle[(i + 0) % N]] = rcycle[(i + 1) % N];

        p.resize(N);
        rep(i, N) p[q[i]] = ainv[i];

        cout << "Possible\n";
        rep(i, N) cout << p[i] + 1 << " \n"[i == N - 1];
        rep(i, N) cout << q[i] + 1 << " \n"[i == N - 1];
    }
}
