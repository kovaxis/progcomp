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

int N, Q;
string s;
int acc[300001];
vector<int> indices[600002];

vector<int>& get_ind(int charge) { return indices[N + (charge - 1) / 2]; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> Q >> s;
        N = s.size();
        rep(i, 2 * N + 1) indices[i].clear();
        rep(i, 1, N + 1) {
            int q = s[i - 1] == '+' ? 1 : -1;
            q *= i % 2 == 0 ? 1 : -1;
            acc[i] = acc[i - 1] + q;
            int adj = -(acc[i - 1] + acc[i]);
            get_ind(adj).push_back(i);
        }
        rep(q, Q) {
            int l, r;
            cin >> l >> r;
            int charge = acc[r] - acc[l - 1];
            if (charge == 0) {
                cout << "0\n";
                continue;
            }
            if (abs(charge) % 2 == 1) {
                vector<int>& ind = get_ind(-charge - 2 * acc[l - 1]);
                int idx = *lower_bound(ind.begin(), ind.end(), l);
                cout << "1\n" << idx << "\n";
                continue;
            }
            vector<int>& ind =
                get_ind(-charge - (acc[l] - acc[l - 1]) - 2 * acc[l - 1]);
            int idx = *lower_bound(ind.begin(), ind.end(), l + 1);
            cout << "2\n" << l << " " << idx << "\n";
        }
    }
}
