#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

int n;
int pref[500001];
int out[500001];
int ancestor[500001];
int min_navail[500001];

int anc_stack[500001];
int get_ancestor(int i) {
    int sn = 0;
    while (ancestor[i] != i) {
        anc_stack[sn++] = i;
        i = ancestor[i];
    }
    rep(j, sn) { ancestor[anc_stack[j]] = i; }
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) {
        cin >> pref[i];
        pref[i] -= 1;
    }
    rep(i, n) { ancestor[i] = i; }

    vector<bool> avail(n, true);
    rep(i, n) {
        int nxt = 0;
        int anc = get_ancestor(i);
        if (avail[pref[i]]) {
            nxt = pref[i];
        } else {
            while (min_navail < n) {
                min_navail += 1;
                if (avail[min_navail - 1]) {
                    nxt = min_navail - 1;
                    break;
                }
            }
        }
        out[i] = nxt;
        avail[nxt] = false;
    }
    rep(i, n) { src[out[i]] = i; }

    rep(i, n) { cout << (out[i] + 1) << (" \n"[i == n - 1]); }
}
