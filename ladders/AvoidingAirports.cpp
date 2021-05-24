#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const long long UNKNOWN = -2;
const long long INF = -1;

struct Flight {
    long long cost;
    int from;
    int to;
    int start;
    int end;
};

struct Country {
    vector<int> dep;

    // flight_idx, rightmost_active_pos
    deque<pair<int, int>> active;
};

int n, m;
Country countries[200001];
Flight flights[200001];

inline long long floordiv(long long a, long long b) {
    int d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0));
}

inline long long intersect_parabolas(const Flight& dep1, const Flight& dep2) {
    // must round down!
    return floordiv((dep2.start + dep1.start +
                     floordiv(dep2.cost - dep1.cost, dep2.start - dep1.start)),
                    2ll);
}

inline long long flight_cost(int arr_time, const Flight& dep) {
    long long wait = dep.start - arr_time;
    return wait * wait + dep.cost;
}

inline void compute_arrival(int f_idx) {
    Flight& arr_f = flights[f_idx];
    if (arr_f.to == n - 1) {
        arr_f.cost = 0;
        return;
    }
    Country& c = countries[arr_f.to];
    int arr_time = arr_f.end;

    while (c.dep.size() > 0) {
        // take departure only if it's after arrival
        int dep_idx = c.dep.back();
        Flight& next_dep = flights[dep_idx];
        if (next_dep.start < arr_time) {
            break;
        }
        assert(next_dep.cost != UNKNOWN);
        c.dep.pop_back();

        // remove active cruft after arrival line
        while (c.active.size() > 1) {
            if (c.active[1].second >= arr_time) {
                c.active.pop_front();
            } else {
                break;
            }
        }
        if (c.active.size() > 0) {
            c.active.front().second = arr_time;
        }

        if (next_dep.cost != INF) {
            // search where on the active stack this departure parabola lands
            int begin = 0;
            int end = c.active.size();
            while (end > begin) {
                int mid = begin + (end - begin) / 2;
                long long contact_pos =
                    intersect_parabolas(flights[c.active[mid].first], next_dep);
                if (contact_pos >= c.active[mid].second) {
                    end = mid;
                } else {
                    begin = mid + 1;
                }
            }

            // truncate stack and place this departure on top
            int valid_upto = arr_time;
            if (begin > 0) {
                valid_upto = intersect_parabolas(
                    flights[c.active[begin - 1].first], next_dep);
            }
            c.active.resize(begin);
            c.active.push_back({dep_idx, valid_upto});
        }
    }

    // use first departure on the stack (intersecting arrival line) to determine
    // cost
    if (c.active.size() > 0) {
        arr_f.cost = flight_cost(arr_time, flights[c.active[0].first]);
    } else {
        arr_f.cost = INF;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    rep(i, m) {
        Flight& f = flights[i];
        f.cost = UNKNOWN;
        cin >> f.from >> f.to >> f.start >> f.end;
        f.from -= 1;
        f.to -= 1;
    }
    flights[m] = {UNKNOWN, 0, 0, -1, 0};

    sort(flights, flights + m + 1, [](const Flight& a, const Flight& b) {
        if (a.end == b.end) {
            return a.start < b.start;
        } else {
            return a.end < b.end;
        }
    });

    rep(i, m + 1) {
        Flight& f = flights[i];
        countries[f.from].dep.push_back(i);
    }

    rep(i, n) {
        auto& c = countries[i];
        sort(c.dep.begin(), c.dep.end(),
             [](int a, int b) { return flights[a].start < flights[b].start; });
    }

    invrep(i, m + 1) { compute_arrival(i); }
    cout << flights[0].cost << endl;
}
