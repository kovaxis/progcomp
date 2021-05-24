#include <bits/stdc++.h>
using namespace std;

bool by_pos(const tuple<int, long long>& b, const long long& a) {
    return get<0>(b) < a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    cin >> m;

    vector<tuple<int, int, int, int>> evst;
    evst.reserve(n * 2);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l;
        cin >> r;
        evst.push_back({l, 1, -r, i});
        evst.push_back({r, -1, -l, i});
    }
    sort(evst.begin(), evst.end());

    vector<pair<int, int>> evs;
    evs.reserve(2 * n);
    deque<int> open;
    unordered_set<int> dead_ids;
    for (auto& ev : evst) {
        int pos, mode, r_, id;
        tie(pos, mode, r_, id) = ev;
        if (mode > 0) {
            open.push_back(id);
        } else {
            if (open.size() > 0 && id == open.front()) {
                // Proper closing
                evs.push_back({pos, 1});
                evs.push_back({pos, -1});
                open.pop_front();
                while (open.size() > 0 && dead_ids.count(open.front()) != 0) {
                    open.pop_front();
                }
            } else {
                // Improper closing
                dead_ids.insert(id);
            }
        }
    }
    sort(evs.begin(), evs.end());

    vector<pair<int, long long>> open_list(1, {-100, -n - 1});
    vector<pair<int, long long>> close_list;
    int active = 0;
    long long acc_open = 0;
    long long acc_close = 0;
    for (auto& ev : evs) {
        int pos = ev.first;
        int add = ev.second;
        int oactive = active;
        active += add;
        if (add > 0) {
            // Open
            acc_open += 1;
            open_list.push_back({pos, acc_open});
        } else {
            // Close
            acc_close += 1;
            close_list.push_back({pos, acc_close});
        }
    }
    close_list.push_back({10000000, acc_close + n + 1});

    cout << "checking" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x;
        cin >> y;

        int j = lower_bound(open_list.begin(), open_list.end(), x + 1, by_pos) -
                open_list.begin() - 1;
        int k = lower_bound(open_list.begin(), open_list.end(), y + 1, by_pos) -
                open_list.begin() - 1;
        long long opened = open_list[k].second - open_list[j].second;

        j = lower_bound(close_list.begin(), close_list.end(), x - 1, by_pos) -
            close_list.begin();
        k = lower_bound(close_list.begin(), close_list.end(), y - 1, by_pos) -
            close_list.begin();
        long long closed = close_list[k].second - close_list[j].second;

        cout << min(opened, closed) << endl;
    }
}
