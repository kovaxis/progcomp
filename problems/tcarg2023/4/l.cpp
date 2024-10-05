#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int N, M;
ll K, R;
vector<ll> B;
vector<ll> pre, suf;
map<ll, vector<int>> premod, sufmod;
int ans_l, ans_r;

ll mod(ll x) { return (x % R + R) % R; }

void answer(int l, int r) {
    if (l >= r) return;
    cerr << "possible answer: " << l + 1 << " " << r << endl;
    if (r - l < ans_r - ans_l || (r - l == ans_r - ans_l && l < ans_l)) ans_l = l, ans_r = r;
}

void testcase() {
    cerr << "running " << endl;
    cin >> M >> N >> K;
    B.resize(M);
    rep(j, M) cin >> B[j];

    {
        ll sum = 0;
        rep(j, M) sum += B[j];
        if (sum < 0) {
            rep(j, M) B[j] *= -1;
            K *= -1;
        } else if (sum == 0) {
            rep(j, M) B.push_back(B[j]);
            M = min(N, 2 * M);
            B.resize(M);
        }
    }

    pre.resize(M + 1);
    rep(j, M) pre[j + 1] = pre[j] + B[j];

    suf.resize(M + 1);
    rep(j, M) suf[M - j - 1] = suf[M - j] + B[M - j - 1];

    // easy problem
    {
        map<ll, vector<int>> seen;
        rep(j, M + 1) {
            cerr << "a " << j << endl;
            if (seen.count(pre[j] - K)) {
                cerr << "counterpart: " << seen[pre[j] - K].back() << endl;
                answer(seen[pre[j] - K].back(), j);
            }
            seen[pre[j]].push_back(j);
        }
    }

    R = pre[M];
    cerr << "modulo " << R << endl;

    if (R > 0) {
        cerr << "checking wraparounds" << endl;
        rep(j, M + 1) {
            premod[mod(pre[j])].push_back(j);
            sufmod[mod(suf[j])].push_back(j);
        }
        for (auto [k, list] : premod) {
            sort(premod[k].begin(), premod[k].end(), [](int i, int j) {
                pair<ll, int> a = {-pre[i], i};
                pair<ll, int> b = {-pre[j], j};
                return a < b;
            });
        }

        // pre
        rep(i, M) {
            cerr << "checking prefixes corresponding to suffix " << i + 1 << endl;
            cerr << "suffix has sum " << suf[i] << ", equivalent to " << mod(suf[i]) << endl;
            cerr << "searching for prefix equivalent to " << mod(K - suf[i]) << endl;
            if (premod.count(mod(K - suf[i])) == 0) continue;
            vector<int> &list = premod[mod(K - suf[i])];

            cerr << "found " << list.size() << " prefixes equivalent to " << mod(K - suf[i]) << ":" << endl;
            for (int j : list) {
                cerr << "  prefix at " << j << ", with sum " << pre[j] << endl;
            }
            int idx;
            {
                int l = 0, r = list.size();
                while (l != r) {
                    int m = (l + r) / 2;
                    if (K - pre[list[m]] - suf[i] >= 0) r = m;
                    else l = m + 1;
                }
                if (r == (int)list.size()) continue;
                idx = l;
            }

            cerr << "suffix " << i + 1 << " matches prefix " << list[idx] << endl;

            ll x = (K - pre[list[idx]] - suf[i]) / R;
            ll left = i, right = M + M * x + list[idx];

            if (right > N) continue;
            answer(left, right);
        }
    }

    if (ans_l == -1) cout << "-1\n";
    else cout << ans_l << " " << ans_r - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC;
    cin >> TC;
    while (TC--) {
        pre.clear(), suf.clear();
        premod.clear(), sufmod.clear();
        ans_l = -1, ans_r = 1e9;
        testcase();
    }
}
