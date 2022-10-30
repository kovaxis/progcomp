#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<vector<int>> children;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        children.assign(N, vector<int>());
        repx(i, 1, N) {
            int p;
            cin >> p;
            children[p - 1].push_back(i);
        }

        vector<int> units;
        rep(i, N) if (children[i].size() > 0)
            units.push_back(children[i].size());
        units.push_back(1);
        sort(units.begin(), units.end(), greater<int>());

        // cerr << "units:" << endl;
        // rep(i, units.size()) cerr << " " << units[i];
        // cerr << endl;

        map<int, int> finishes;
        int t = 0;
        rep(i, units.size()) finishes[t + units[i]] += 1, t += 1;
        while ((--finishes.end())->first > t) {
            auto p = *(--finishes.end());
            // cerr << "max finishes is " << p.first << ", t = " << t << endl;
            finishes[p.first] -= 1;
            if (finishes[p.first] == 0) finishes.erase(p.first);
            finishes[p.first - 1] += 1;
            t += 1;
        }

        cout << t << "\n";
    }
}
