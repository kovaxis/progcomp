#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    vector<pair<int, int>> nums;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        int n;
        cin >> n;
        nums.clear();
        nums.reserve(n);
        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;
            nums.push_back({num, i});
        }
        sort(nums.begin(), nums.end());
        int last_num = 0;
        int last_winner = -1;
        int rep = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i].first != last_num) {
                if (rep == 1) {
                    break;
                }
                rep = 0;
            }
            last_num = nums[i].first;
            last_winner = nums[i].second;
            rep += 1;
        }
        if (rep == 1) {
            cout << (last_winner + 1) << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
