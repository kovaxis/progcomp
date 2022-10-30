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

int N, A, B;
vector<bool> used;
vector<int> p;

int find(int i, int x) {
    while (i >= 1 && i <= N && used[i]) i += x;
    return i;
}

bool solve() {
    cin >> N >> A >> B;
    used.assign(N + 1, false);
    p.assign(N, 0);
    p[0] = A, used[A] = true;
    p[N / 2] = B, used[B] = true;
    rep(i, 1, N / 2) {
        p[i] = find(N, -1);
        if (p[i] < A) return false;
        used[p[i]] = true;
    }
    rep(i, N / 2 + 1, N) {
        p[i] = find(1, 1);
        if (p[i] > B) return false;
        used[p[i]] = true;
    }
    rep(i, N) cout << p[i] << " \n"[i == N - 1];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        if (!solve()) cout << "-1\n";
    }
}
