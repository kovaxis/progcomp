#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const int MOD = 1e9 + 7;

int N;
vector<int> cnt, pos;

void initcnt(string S) {
    cnt.assign(N + 1, 0);
    rep(i, N) cnt[i + 1] = cnt[i] + (S[i] == '1');

    pos.clear();
    rep(i, N) if (S[i] == '1') pos.push_back(i);
}

int ones(int l, int r) {
    return cnt[r] - cnt[l];
}
int pos_of(int k) {
    if (k >= (int)pos.size()) return N;
    return pos[k];
}

int eval(string S) {
    int val = 0, p2 = 1;
    rep(i, N) {
        char c = S[N - 1 - i];
        if (c == '1') val = (val + p2) % MOD;
        p2 = (p2 + p2) % MOD;
    }
    return val;
}

string norev(string S, int k) {
    cerr << "forcing string " << S << " with K = " << k << endl;
    int r = N - 1;
    rep(i, N) {
        while (r >= 0 && S[r] == '1') r -= 1;
        if (r <= i) break;
        if (S[i] == '1') {
            if (k == 0) break;
            swap(S[i], S[r]);
            k -= 1;
        }
    }
    cerr << "  resulted in " << S << endl;
    return S;
}

string minimize(string S, int K) {
    if (K < 0) {
        rep(i, N) S[i] = '1';
        return S;
    }
    initcnt(S);

    cerr << "minimizing " << S << " with K = " << K << endl;

    pair<int, int> mn = {N, N};
    int mn_i;
    rep(i, N) if (ones(i, N) > 0) {
        // fix this as LSB
        int k = K;
        k -= ones(i + 1, N);
        if (k < 0) continue;
        int best = i - ones(0, N) + 1;
        if (best < 0) continue;
        int leftmost = min(best, pos_of(k));
        int nxtleftmost = min(best + 1, pos_of(k + 1));
        pair<int, int> res = {i - leftmost, i - nxtleftmost};
        if (res <= mn) mn = res, mn_i = i;
        cerr << "  lsb " << i << ": " << res.first << " " << res.second << endl;
    }

    // fix lsb as mn_i
    if (mn_i != N - 1)
        rotate(S.begin(), S.begin() + mn_i + 1, S.end());
    return norev(S, K);
}

string rev1(string S, int K) {
    reverse(S.begin(), S.end());
    return minimize(S, K - 1);
}

string rev2(string S, int K) {
    return minimize(S, K - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    string S;
    cin >> N >> K >> S;
    N = S.size();

    string T = norev(S, K);
    T = min(T, rev1(S, K));
    T = min(T, rev2(S, K));
    cout << eval(T) << endl;
}
