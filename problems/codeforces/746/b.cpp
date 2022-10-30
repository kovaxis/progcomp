#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

// edge, center
vector<int> nums[2];

bool testcase() {
    int N, x;
    cin >> N >> x;
    rep(k, 2) nums[k].clear();
    rep(i, N) {
        int a;
        cin >> a;
        nums[i >= N - x && i < x].push_back(a);
    }
    // center
    int last = INT32_MIN;
    for (int num : nums[1]) {
        if (num < last) return false;
        last = num;
    }
    // edge
    if (nums[1].size() == 0 || nums[0].size() == 0) return true;
    sort(nums[0].begin(), nums[0].end());
    int mid = nums[0].size() / 2;
    return nums[0][mid - 1] <= nums[1].front() &&
           nums[0][mid] >= nums[1].back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        if (testcase()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
