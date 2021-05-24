#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
T binsearch(T begin, T end, int precision, U predicate(T)) {
    for (int iter = 0; iter < precision; iter++) {
        T mid = (begin + end) / 2;
        U heur = predicate(mid);
        if (heur > 0) {
            end = mid;
        } else if (heur < 0) {
            begin = mid;
        } else {
            return mid;
        }
    }
    return (begin + end) / 2;
}

vector<pair<double, double>> cheetahs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cheetahs.reserve(100000);
    while (true) {
        int n;
        cin >> n;
        if (n <= 0) {
            break;
        }
        cheetahs.clear();
        double min_time = 0;
        double fastest_vel = 0;
        double slowest_vel = INFINITY;
        for (int i = 0; i < n; i++) {
            int t, k;
            cin >> t;
            cin >> k;
            min_time = max(min_time, (double)t);
            fastest_vel = max(fastest_vel, (double)k);
            slowest_vel = min(slowest_vel, (double)k);
            cheetahs.push_back({t, k});
        }
        double max_time =
            min_time + min_time * slowest_vel / (fastest_vel - slowest_vel);
        if (fastest_vel == slowest_vel) {
            max_time = min_time;
        }
        double time =
            binsearch<double, double>(min_time, max_time, 30, [](double time) {
                double min_pos = INFINITY;
                double min_vel = 0.;
                double max_pos = -INFINITY;
                double max_vel = 0.;
                for (auto& c : cheetahs) {
                    double pos = (time - c.first) * c.second;
                    if (pos < min_pos) {
                        min_pos = pos;
                        min_vel = c.second;
                    }
                    if (pos > max_pos) {
                        max_pos = pos;
                        max_vel = c.second;
                    }
                }
                return max_vel - min_vel;
            });
        double min_pos = INFINITY;
        double max_pos = -INFINITY;
        for (auto& c : cheetahs) {
            double pos = (time - c.first) * c.second;
            if (pos < min_pos) {
                min_pos = pos;
            }
            if (pos > max_pos) {
                max_pos = pos;
            }
        }
        cout << fixed << setw(3) << setprecision(3) << (max_pos - min_pos)
             << endl;
    }
}
