#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int N;
int a[100005];

int lpeak[100005];
int rpeak[100005];

void findpeaks(int peakarr[], int start, int dir) {
    int i = start;
    int lastsolid = start - dir;
    int lastpeak;
    while (i >= 0 && i < N) {
        if (lastsolid < 0 || lastsolid >= N || a[lastsolid] < a[i])
            lastpeak = lastsolid + dir;
        peakarr[i] = lastpeak;
        if (a[i] != -1) lastsolid = i;
        i += dir;
    }
}

bool ismountain(int l, int r) {
    int lk = rpeak[l], rk = lpeak[r];
    return lk >= rk && lk > l && rk < r;
}

bool check_k(int k) {
    for (int i = 0; i < N; i += k) {
        if (!ismountain(i, min(i + k, N) - 1)) return false;
    }
    return true;
}

bool check_all() {
    rep(k, 3, N + 1) if (check_k(k)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) cin >> a[i];

    findpeaks(lpeak, 0, 1);
    findpeaks(rpeak, N - 1, -1);

    // rep(i, N) cerr << lpeak[i] << " \n"[i == N - 1];
    // rep(i, N) cerr << rpeak[i] << " \n"[i == N - 1];

    cout << "NY"[check_all()] << "\n";
}
