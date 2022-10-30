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

uint8_t tab3[64];

int ask(const char* op, int i, int j) {
    int x;
    cout << op << " " << i + 1 << " " << j + 1 << endl;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, k;
    cin >> N >> k;

    tab3[0b000000] = 0b000;
    tab3[0b000011] = 0b100;
    tab3[0b000101] = 0b010;
    tab3[0b001111] = 0b110;
    tab3[0b000110] = 0b001;
    tab3[0b010111] = 0b101;
    tab3[0b100111] = 0b011;
    tab3[0b111111] = 0b111;

    int init[6];
    init[0] = ask("or", 1, 2);
    init[1] = ask("or", 0, 2);
    init[2] = ask("or", 0, 1);
    init[3] = ask("and", 1, 2);
    init[4] = ask("and", 0, 2);
    init[5] = ask("and", 0, 1);

    vector<int> ans(N, 0);
    rep(i, 31) {
        int x = 0;
        rep(j, 6) x |= ((init[j] >> i) & 1) << j;
        int y = tab3[x];
        rep(j, 3) ans[j] |= ((y >> j) & 1) << i;
    }

    int base = ans[0];
    rep(i, 3, N) {
        int yand = ask("and", 0, i);
        int yor = ask("or", 0, i);
        ans[i] = base ^ yand ^ yor;
    }

    sort(ans.begin(), ans.end());
    cout << "finish " << ans[k - 1] << endl;
}
