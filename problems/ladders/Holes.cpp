#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Node {
    int last, nxt, jumps;
};

int N, Q, B;
vector<int> power;
vector<Node> nxt;

void recalc(int m) {
    int l = m * B, r = min(m * B + B, N);
    invrepx(i, l, r) {
        int k = i + power[i];
        if (k >= r)
            nxt[i] = {i, k, 1};
        else
            nxt[i] = {nxt[k].last, nxt[k].nxt, nxt[k].jumps + 1};
    }
}

pair<int, int> get(int i) {
    int ip = i;
    int j = 0;
    while (i < N) {
        j += nxt[i].jumps;
        ip = nxt[i].last;
        i = nxt[i].nxt;
    }
    return {ip, j};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    B = (int)sqrt(N);
    power.resize(N), nxt.resize(N);
    rep(i, N) cin >> power[i];
    rep(m, (N + B - 1) / B) recalc(m);
    rep(q, Q) {
        int t;
        cin >> t;
        if (t == 0) {
            // set power
            int i, b;
            cin >> i >> b;
            i -= 1;
            power[i] = b;
            recalc(i / B);
        } else if (t == 1) {
            // query
            int i;
            cin >> i;
            auto ans = get(i - 1);
            cout << ans.first + 1 << " " << ans.second << "\n";
        }
    }
}
