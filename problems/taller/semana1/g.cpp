#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> Point;
typedef struct {
    Point p0;
    Point p1;
} Segment;

void read_seg(Segment &seg) {
    cin >> seg.p0.first;
    cin >> seg.p0.second;
    cin >> seg.p1.first;
    cin >> seg.p1.second;
}

bool is_horizontal(const Segment &seg) {
    return seg.p0.second == seg.p1.second && seg.p0.first != seg.p1.first;
}
bool is_vertical(const Segment &seg) {
    return seg.p0.first == seg.p1.first && seg.p0.second != seg.p1.second;
}

bool is_rect() {
    Segment segs[4];
    bool found_base = false;
    for (int i = 0; i < 4; i++) {
        read_seg(segs[i]);
        if (!found_base && is_horizontal(segs[i])) {
            swap(segs[0], segs[i]);
            found_base = true;
        }
    }
    if (!found_base) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        Point point = segs[i].p1;
        bool found = false;
        for (int j = i + 1; j < 4; j++) {
            if (segs[j].p1 == point) {
                swap(segs[j].p0, segs[j].p1);
            }
            if (segs[j].p0 == point) {
                swap(segs[i + 1], segs[j]);
                found = true;
                break;
            }
        }
        if (i == 3) {
            found = segs[0].p0 == point;
        }
        if (!found) {
            return false;
        }
    }

    if (!is_vertical(segs[1])) {
        return false;
    }
    if (!is_horizontal(segs[2])) {
        return false;
    }
    if (!is_vertical(segs[3])) {
        return false;
    }

    return true;
}

int main() {
    if (is_rect()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
