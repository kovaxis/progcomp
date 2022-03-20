#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int N;
string s;
vector<int> free_a, free_b;
vector<pair<int, int>> link_ab, link_ac, link_bc;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> s;
    N = s.size() / 2;

    bool cannot = false;
    rep(i, 2 * N) {
        if (s[i] == 'A') {
            free_a.push_back(i);
        } else if (s[i] == 'B') {
            if (free_a.empty())
                free_b.push_back(i);
            else {
                int j = free_a.back();
                free_a.pop_back();
                link_ab.push_back({j, i});
            }
        } else if (s[i] == 'C') {
            if (!free_b.empty()) {
                int j = free_b.back();
                free_b.pop_back();
                link_bc.push_back({j, i});
            } else if (!free_a.empty()) {
                int j = free_a.back();
                free_a.pop_back();
                link_ac.push_back({j, i});
            } else if (!link_ab.empty()) {
                auto p = link_ab.back();
                int j = p.first, k = p.second;
                link_ab.pop_back();
                link_bc.push_back({k, i});
                free_a.push_back(j);
            } else {
                cannot = true;
            }
        }
    }
    if (!free_a.empty() || !free_b.empty()) cannot = true;
    if (cannot) {
        cout << "NO\n";
    } else {
        assert(link_ab.size() + link_ac.size() + link_bc.size() == N);
        cout << "YES\n";
        for (auto p : link_ab) {
            cout << p.first + 1 << " " << p.second + 1 << "\n";
        }
        for (auto p : link_ac) {
            cout << p.first + 1 << " " << p.second + 1 << "\n";
        }
        for (auto p : link_bc) {
            cout << p.first + 1 << " " << p.second + 1 << "\n";
        }
    }
}