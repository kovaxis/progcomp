#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<int> lo, hi;
        repx(i, 1, N / 2 + 1) lo.push_back(i);
        repx(i, N / 2 + 1, N + 1) hi.push_back(i);
        vector<int> ans;
        while (lo.size() || hi.size()) {
            if (lo.size()) {
                ans.push_back(lo.back());
                lo.pop_back();
            }
            if (hi.size()) {
                ans.push_back(hi.back());
                hi.pop_back();
            }
        }
        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
}
