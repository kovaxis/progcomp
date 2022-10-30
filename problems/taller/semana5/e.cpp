#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

static int solcount = 0;
bool force_off[1005];

void check(vector<int>& nums, vector<bool>& choose, int k, int idx) {
    if (k == 0) {
        bool first = true;
        rep(i, idx) {
            if (choose[i]) {
                if (first) {
                    first = false;
                } else {
                    cout << "+";
                }
                cout << nums[i];
            }
        }
        cout << endl;
        solcount += 1;
    }
    if (k <= 0 || idx >= nums.size()) {
        return;
    }
    bool force = force_off[nums[idx]];
    if (!force) {
        choose[idx] = true;
        check(nums, choose, k - nums[idx], idx + 1);
    }
    force_off[nums[idx]] = true;
    choose[idx] = false;
    check(nums, choose, k, idx + 1);
    force_off[nums[idx]] = force;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    vector<int> nums;
    vector<bool> choose;
    while (cin >> k) {
        int n;
        cin >> n;
        nums.clear();
        choose.clear();
        rep(i, n) {
            int x;
            cin >> x;
            nums.push_back(x);
            choose.push_back(false);
        }
        rep(i, 1005) { force_off[i] = false; }
        cout << "Sums of " << k << ":" << endl;
        solcount = 0;
        check(nums, choose, k, 0);
        if (solcount == 0) {
            cout << "NONE" << endl;
        }
    }
}
