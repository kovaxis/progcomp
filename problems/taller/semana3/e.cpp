#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n;
    cin >> t;

    vector<double> dists;
    vector<double> reads;
    dists.reserve(n);
    reads.reserve(n);
    double min_reading = INFINITY;
    double max_dist = 0.;
    for (int i = 0; i < n; i++) {
        double d, s;
        cin >> d;
        cin >> s;
        dists.push_back(d);
        reads.push_back(s);
        min_reading = min(min_reading, s);
        max_dist = max(max_dist, d);
    }

    double begin = -min_reading;
    double end = n * max_dist / t - min_reading;
    for (int iter = 0; iter < 50; iter++) {
        double c = (begin + end) / 2;
        double total_time = 0.;
        for (int i = 0; i < n; i++) {
            total_time += dists[i] / (reads[i] + c);
        }
        if (total_time > t) {
            begin = c;
        } else {
            end = c;
        }
    }
    cout << fixed << setw(9) << setprecision(9) << ((begin + end) / 2) << endl;
}
