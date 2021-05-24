#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef struct {
    int h;
    int b;
} Building;

int main() {
    vector<Building> bs;
    int n;
    cin >> n;
    bs.reserve(n);
    int shortest_positive = 99999999;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        bs.push_back(Building{
            h,
            0,
        });
    }
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        bs[i].b = b;
        if (b >= 0) {
            if (bs[i].h < shortest_positive) {
                shortest_positive = bs[i].h;
            }
        }
    }
    int beauty = 0;
    int shortest_negative_h = 99999999;
    int shortest_negative_b = 0;
    for (int i = 0; i < n; i++) {
        if (bs[i].b >= 0) {
            beauty += bs[i].b;
        } else {
            if (bs[i].h > shortest_positive) {
                // Can be neutralized
            } else {
                // Group with other negatives
                if (bs[i].h < shortest_negative_h) {
                    shortest_negative_h = bs[i].h;
                    shortest_negative_b = bs[i].b;
                }
            }
        }
    }
    beauty += shortest_negative_b;
    cout << beauty << endl;
}
