#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int N;
string s;
ll cnt[128];
ll ba, bc;

vector<int> open_a, open_b;
vector<pair<int, int>> pairs;

const int INF = 1e9;

bool solve() {
    rep(i, 2 * N) cnt[s[i]] += 1;

    ba = cnt['B'] + cnt['A'] - cnt['C'];
    if (ba % 2) return false;
    ba /= 2;
    bc = cnt['B'] - ba;

    if (ba < 0 || bc < 0) return false;

    ll found_b = 0;
    rep(i, 2 * N) {
        if (s[i] == 'A') {
            open_a.push_back(i);
        } else if (s[i] == 'B') {
            if (found_b < bc) {
                // opening b
                open_b.push_back(i);
            } else {
                // closing b
                if (open_a.empty()) return false;
                int j = open_a.back();
                open_a.pop_back();
                pairs.push_back({j, i});
            }
            found_b += 1;
        } else if (s[i] == 'C') {
            if (!open_b.empty()) {
                int j = open_b.back();
                open_b.pop_back();
                pairs.push_back({j, i});
            } else if (!open_a.empty()) {
                int j = open_a.back();
                open_a.pop_back();
                pairs.push_back({j, i});
            } else {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> s;
    N = s.size() / 2;

    if (solve()) {
        cout << "YES\n";
        for (auto p : pairs) cout << p.first + 1 << " " << p.second + 1 << "\n";
    } else {
        cout << "NO\n";
    }
}