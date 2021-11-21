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

ll min_e[900000];

int nums[7];
int final[7];

int p_id(int n[]) {
    int id = 0;
    rep(i, 7) id = id * 7 + n[i];
    return id;
}

ll cost(int n[]);

void check(ll& c, int n[], int i, int j) {
    ll base = n[i] + n[j];
    swap(n[i], n[j]);
    c = min(c, base + cost(n));
    swap(n[i], n[j]);
}

ll cost(int n[]) {
    int id = p_id(n);
    if (min_e[id] == -2) return INT32_MAX;
    if (min_e[id] != -1) return min_e[id];
    min_e[id] = -2;
    ll c = INT32_MAX;
    check(c, n, 0, 3);
    check(c, n, 1, 4);
    check(c, n, 2, 5);
    check(c, n, 3, 6);
    check(c, n, 0, 1);
    check(c, n, 2, 3);
    check(c, n, 3, 4);
    check(c, n, 5, 6);
    min_e[id] = c;
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    rep(i, 900000) min_e[i] = -1;

    rep(i, 7) cin >> nums[i];
    rep(i, 7) {
        int x;
        cin >> x;
        rep(j, 7) if (x == nums[j]) final[i] = j;
    }
    min_e[p_id(final)] = 0;
    int init[7] = {0, 1, 2, 3, 4, 5, 6};
    cout << cost(init) << endl;
}
