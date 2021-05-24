#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

void normalize_delta(Point& delta) {
    if (delta.x < 0) {
        delta.x *= -1;
        delta.y *= -1;
    } else if (delta.x == 0) {
        if (delta.y < 0) {
            delta.y *= -1;
        }
    }
}

long long delta_key(Point& a) {
    return (((unsigned long long)((unsigned int)a.x)) << 32) |
           ((unsigned long long)((unsigned int)a.y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Point> points;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        points.push_back({x, y});
    }

    unordered_map<long long, int> segments;
    segments.reserve(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point delta = {points[j].x - points[i].x,
                           points[j].y - points[i].y};
            normalize_delta(delta);
            segments[delta_key(delta)] += 1;
        }
    }
    int total = 0;
    for (auto& it : segments) {
        int count = it.second;
        total += count * (count - 1) / 2;
    }
    cout << (total / 2) << endl;
}
