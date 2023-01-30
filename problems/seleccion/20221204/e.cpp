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

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

int N, M, K;
uset<int> active_workers[7];
vector<vector<int>> worker_days;
vector<int> holidays;
vector<priority_queue<int>> worker_queue;
vector<vector<int>> projects;
vector<int> next_part;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;

    map<string, int> day2idx;
    string s;
    day2idx["Monday"] = 0;
    day2idx["Tuesday"] = 1;
    day2idx["Wednesday"] = 2;
    day2idx["Thursday"] = 3;
    day2idx["Friday"] = 4;
    day2idx["Saturday"] = 5;
    day2idx["Sunday"] = 6;
    worker_days.resize(N);
    rep(i, N) {
        int t;
        cin >> t;
        worker_days[i].resize(t);
        rep(j, t) {
            cin >> s;
            int x = day2idx[s];
            worker_days[i][j] = x;
            cerr << "worker " << i << " works on weekday " << x << endl;
        }
    }

    holidays.resize(M);
    rep(m, M) {
        int h;
        cin >> h;
        holidays[m] = h - 1;
    }

    projects.resize(K);
    next_part.resize(K, 0);
    rep(k, K) {
        int P;
        cin >> P;
        projects[k].resize(P);
        rep(p, P) {
            int w;
            cin >> w;
            w--;
            projects[k][p] = w;
        }
    }

    worker_queue.resize(N);
    rep(k, K) {
        int i = projects[k][next_part[k]];
        worker_queue[i].push(-k);
        for (int wd : worker_days[i]) active_workers[wd].insert(i);
    }

    ans.resize(K);
    int m = 0, pending = K;
    vector<pair<int, int>> to_insert;
    vector<int> to_deactivate;
    for (int d = 0; pending > 0; d++) {
        // skip holidays
        if (m < M && holidays[m] == d) {
            m += 1;
            continue;
        }

        cerr << "day " << d + 1 << endl;

        // iterate over workers available this day
        to_insert.clear();
        to_deactivate.clear();
        for (int i : active_workers[d % 7]) {
            if (worker_queue[i].empty()) throw "nani?";

            // work on their next project
            int k = -worker_queue[i].top();
            worker_queue[i].pop();
            next_part[k] += 1;
            cerr << "  worker " << i + 1 << " works on project " << k + 1 << endl;

            if (worker_queue[i].empty()) to_deactivate.push_back(i);

            if (next_part[k] == projects[k].size()) {
                ans[k] = d;
                pending--;
            } else {
                int other_worker = projects[k][next_part[k]];
                to_insert.push_back({other_worker, k});
            }
        }

        // deactivate workers
        for (int i : to_deactivate)
            for (int wd : worker_days[i]) active_workers[wd].erase(i);

        // add completed projects to queue
        for (auto [i, k] : to_insert) {
            worker_queue[i].push(-k);
            for (int wd : worker_days[i]) active_workers[wd].insert(i);
        }
    }

    rep(k, K) cout << ans[k] + 1 << " \n"[k == K - 1];
}
