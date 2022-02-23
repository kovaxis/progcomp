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

int N, K, M, L;
vector<int> a;
set<int> seen;

int idx = 0;
int getfirst(int pat) {
    while (idx < N && a[idx] >> L == pat) idx += 1;
    return idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    a.resize(N);
    rep(i, N) cin >> a[i];

    if (K == 0) {
        cout << N << endl;
        return 0;
    }
    L = 31 - __builtin_clz(K);
    M = (-1) << L;

    sort(a.begin(), a.end());

    rep(i, N) seen.insert(a[i] >> L);

    int ans = seen.size();
    for (int pat : seen)
        if ((pat & 1) == 0 && seen.count(pat + 1)) {
            // maybe discount 1
            int x = getfirst(pat), y = getfirst(pat + 1), z = getfirst(pat + 2);
            bool ok = true;
            invrep(b, L) {
                bool sn[2];
                sn[0] = false, sn[1] = false;
                rep(i, x, z) sn[(a[i] >> b) & 1] = true;
                bool both = sn[0] && sn[1];
                bool kone = (K >> b) & 1;
                if (!both && kone) {
                    ok = false;
                    break;
                }
                if (both && !kone) {
                    ok = true;
                    break;
                }
            }
            if (!ok) ans -= 1;
        }
}
