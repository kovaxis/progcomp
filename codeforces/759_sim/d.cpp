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

int N;
vector<int> a, cnt, pos;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N), cnt.assign(N, 0), pos.resize(N);
        rep(i, N) cin >> a[i];
        rep(i, N) a[i] -= 1;
        rep(i, N) cnt[a[i]] += 1;
        rep(i, N) pos[a[i]] = i;

        bool mult = false;
        rep(i, N) mult |= cnt[i] >= 2;
        if (mult) {
            cout << "YES\n";
            continue;
        }

        bool wrong = false;
        rep(i, N) {
            int j = pos[i];
            if (i == j) continue;
            int k = i;
            while (k == i || k == j) k++;
            if (k >= N) {
                wrong = true;
                break;
            }
            // a[i] = a[j]
            // a[j] = a[k]
            // a[k] = a[i]
            int iv = a[i], jv = a[j], kv = a[k];
            a[i] = jv, a[j] = kv, a[k] = iv;
            pos[jv] = i, pos[kv] = j, pos[iv] = k;
        }

        if (wrong)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
}
