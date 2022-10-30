#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef struct {
    int idx;
    int choice;
} Frame;

int main() {
    vector<int> available;
    vector<Frame> stack;
    vector<int> counts;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        available.clear();
        stack.clear();
        counts.clear();
        // Read
        int friends, days;
        cin >> friends;
        cin >> days;
        for (int j = 0; j < days; j++) {
            int k;
            cin >> k;
            available.push_back(k);
            for (int l = 0; l < k; l++) {
                int f;
                cin >> f;
                available.push_back(f - 1);
            }
        }
        for (int j = 0; j < friends; j++) {
            counts.push_back(0);
        }

        // Do
        int limit = (days + 1) / 2;
        int next_idx = 0;
        bool adv = true;
        bool ok = false;
        while (true) {
            if (adv) {
                if (next_idx >= available.size()) {
                    ok = true;
                    break;
                }
                // cout << "advancing onto frame " << stack.size() << endl;
                int k = available[next_idx];
                stack.push_back(Frame{
                    next_idx,
                    0,
                });
                next_idx += 1 + k;
                adv = false;
            } else {
                if (stack.size() <= 0) {
                    ok = false;
                    break;
                }
                Frame& frame = stack[stack.size() - 1];
                // cout << "permutating frame " << (stack.size() - 1)
                //     << " (choice " << frame.choice << ")" << endl;
                if (frame.choice > 0) {
                    counts[available[frame.idx + frame.choice]] -= 1;
                }
                if (frame.choice >= available[frame.idx]) {
                    // cout << " ran out of choices" << endl;
                    stack.pop_back();
                    next_idx = frame.idx;
                } else {
                    int friend_idx = available[frame.idx + 1 + frame.choice];
                    // cout << " friend idx for choice " << frame.choice << ": "
                    //     << friend_idx << endl;
                    counts[friend_idx] += 1;
                    frame.choice += 1;
                    if (counts[friend_idx] <= limit) {
                        // cout << " choice within limits" << endl;
                        adv = true;
                    } else {
                        // cout << " ran beyond limit" << endl;
                    }
                }
            }
        }
        if (ok) {
            cout << "YES" << endl;
            bool first = true;
            for (int j = 0; j < stack.size(); j++) {
                Frame& frame = stack[j];
                int f = available[frame.idx + frame.choice] + 1;
                if (first) {
                    first = false;
                } else {
                    cout << " ";
                }
                cout << f;
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
