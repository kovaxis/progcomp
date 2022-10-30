#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 2e9;

int N;
vector<int> a;
vector<vector<int>> b;
string ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];

    rep(i, N) {
        int l = 0, r = b.size();
        while (l != r) {
            int m = (l + r) / 2;
            if (a[i] > a[b[m].back()]) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        if (l >= b.size()) b.push_back(vector<int>());
        b[l].push_back(i);
    }

    if (false) {
        cerr << "LIS: " << b.size() << endl;
        rep(i, b.size()) {
            cerr << "  b[" << i << "] =";
            for (int j : b[i]) cerr << " " << j;
            cerr << endl;
        }
    }

    ans.assign(N, '1');
    invrep(i, b.size() - 1) {
        vector<bool> rem(b[i].size());
        rep(j, b[i].size()) {
            int r = b[i + 1].size();
            {
                int l = 0;
                while (l != r) {
                    int m = (l + r) / 2;
                    if (a[b[i + 1][m]] > a[b[i][j]]) {
                        l = m + 1;
                    } else {
                        r = m;
                    }
                }
                // cerr << "r for index " << b[i][j] << " = " << r << endl;
            }

            int l = 0;
            {
                int r = b[i + 1].size();
                while (l != r) {
                    int m = (l + r) / 2;
                    if (b[i + 1][m] < b[i][j]) {
                        l = m + 1;
                    } else {
                        r = m;
                    }
                }
                // cerr << "l for index " << b[i][j] << " = " << l << endl;
            }

            rem[j] = (l >= r);
            // if (rem[j]) cerr << "  removing index " << b[i][j] << endl;
        }
        auto rm = remove_if(b[i].begin(), b[i].end(), [&](const int& idx) {
            return rem[&idx - &*b[i].begin()];
        });
        b[i].erase(rm, b[i].end());
    }

    if (false) {
        cerr << "Corrected LIS: " << b.size() << endl;
        rep(i, b.size()) {
            cerr << "  b[" << i << "] =";
            for (int j : b[i]) cerr << " " << j;
            cerr << endl;
        }
    }

    for (auto& bb : b) {
        for (int idx : bb) {
            ans[idx] = (bb.size() == 1 ? '3' : '2');
        }
    }

    cout << ans << endl;
}
