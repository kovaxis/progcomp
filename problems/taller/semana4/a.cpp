#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        int n;
        cin >> n;
        vector<pair<int, int>> bs;
        bs.reserve(n);
        for (int i = 0; i < n; i++) {
            int h;
            cin >> h;
            bs.push_back({h, 0});
        }
        long long cur_dc = 0;
        for (int i = 0; i < n; i++) {
            int c;
            cin >> c;
            bs[i].second = c;
            cur_dc -= c;
        }
        sort(bs.begin(), bs.end());
        int h = 0;
        for (int i = 0; i < n; i++) {
            cur_dc += 2 * bs[i].second;
            if (cur_dc >= 0) {
                h = bs[i].first;
                break;
            }
        }
        long long c = 0;
        for (int i = 0; i < n; i++) {
            c += ((long long)abs(bs[i].first - h)) * bs[i].second;
        }
        cout << c << endl;
    }
}
