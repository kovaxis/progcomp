#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;
};

double dot(Point& a, Point& b) { return a.x * b.x + a.y * b.y; }

Point add(Point& a, Point& b) { return {a.x + b.x, a.y + b.y}; }

bool lt_polar(pair<float, Point>& a, pair<float, Point>& b) {
    return a.first < b.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Point> points;
    unordered_set<long long> points_set;
    int n;
    cin >> n;
    vector<pair<float, Point>> points_polar(n - 1, {0., {0., 0.}});
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        points.push_back({(double)x, (double)y});
        long long key = (((long long)x) << 32) | ((long long)y);
        points_set.insert(key);
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        Point& a = points[i];
        cout << "checking around point [" << i << "] " << a.x << ", " << a.y
             << endl;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            Point& b = points[j];
            float angle = atan2(b.y - a.y, b.x - a.x);
            int store_idx = j;
            if (j > i) {
                store_idx -= 1;
            }
            points_polar[store_idx] = {angle, {b.x - a.x, b.y - a.y}};
        }
        sort(points_polar.begin(), points_polar.end(), lt_polar);
        int end = 0;
        for (int j = 0; j < n - 1; j++) {
            float this_angle = points_polar[j].first;
            Point& this_point = points_polar[j].second;
            cout << "  checking orbit point [" << j << "]  " << this_point.x
                 << ", " << this_point.y << endl;
            double last_dot = 0.;
            int limit = j - 1;
            if (limit < 0) {
                limit = n - 2;
            }
            while (end != limit) {
                cout << "    checking limit point [" << end << "] "
                     << points_polar[end].second.x << ", "
                     << points_polar[end].second.y << endl;
                last_dot = dot(points_polar[end].second, this_point) > 0.;
                if (last_dot <= 0.) {
                    break;
                }
                end += 1;
                if (end >= n - 1) {
                    end = 0;
                }
            }
            cout << "    limit point is [" << end << "] "
                 << points_polar[end].second.x << ", "
                 << points_polar[end].second.y << endl;
            if (last_dot == 0.) {
                // Found three right-angle points at i, j and end
                // Check whether the fourth exists
                cout << "    limit is orthogonal" << endl;
                Point sum =
                    add(points_polar[j].second, points_polar[end].second);
                cout << "    checking for sum at " << sum.x << ", " << sum.y
                     << endl;
                long long key = (((long long)sum.x) << 32) | ((long long)sum.y);
                if (points_set.count(key) != 0) {
                    cout << "    sum exists" << endl;
                    total += 1;
                }
            }
        }
    }
    cout << (total / 4) << endl;
}
