#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

vector<pair<int, int>> minbuild;

vector<int> nums;
vector<pair<int, int>> build;

int target;

void explore(int n) {
    if (!minbuild.empty() && build.size() >= minbuild.size()) return;
    if (n == target) minbuild = build;
    if (n >= target) return;
    nums.push_back(n);
    rep(i, nums.size()) {
        int j = nums[i];
        build.push_back({j, n});
        explore(j + n);
        build.pop_back();
    }
    nums.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin >> m >> target;
    if (m != 1) {
        cout << "*\n";
        return 0;
    }

    explore(1);
    for (auto add : minbuild)
        cout << "1 " << add.first << "\n1 " << add.second << "\n";
}
