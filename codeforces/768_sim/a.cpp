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

int N, K;
vector<int> match;

void connect(int i, int j) {
    int i2 = match[i], j2 = match[j];
    match[i] = j, match[j] = i;
    match[i2] = j2, match[j2] = i2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> K;
        match.resize(N);
        rep(i, N) match[i] = N - i - 1;
        if (N == 4 && K == 3) {
            cout << "-1\n";
            continue;
        }
        if (K == N - 1) {
            connect(N - 1, N - 2);
            connect(1, N - 3);
        } else {
            connect(N - 1, K);
        }
        rep(i, N) {
            if (match[i] == -1) continue;
            cout << i << " " << match[i] << "\n";
            match[match[i]] = -1;
        }
    }
}
