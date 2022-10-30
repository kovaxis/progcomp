#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int max_pos[128];
    for (int i = 0; i < 128; i++) {
        max_pos[i] = -1;
    }

    int n;
    cin >> n;
    string flats;
    getline(cin, flats);
    getline(cin, flats);

    int min_visits = 0;
    for (int i = 0; i < flats.size(); i++) {
        char ty = flats[i];
        bool must_replace = max_pos[ty] == -1;
        max_pos[ty] = i;
        int min_pos = flats.size();
        for (int j = 'A'; j <= 'Z'; j++) {
            if (max_pos[j] != -1) {
                min_pos = min(min_pos, max_pos[j]);
            }
        }
        for (int j = 'a'; j <= 'z'; j++) {
            if (max_pos[j] != -1) {
                min_pos = min(min_pos, max_pos[j]);
            }
        }
        int dist = i - min_pos + 1;
        if (must_replace || dist < min_visits) {
            min_visits = dist;
        }
    }

    cout << min_visits;
}
