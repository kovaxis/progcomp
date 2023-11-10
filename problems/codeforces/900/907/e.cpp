#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// center 1s
// center ns
// border 1s
// border ns

int N, K;
vector<int> A;

int getbad() {
    int bad = 0;
    rep(i, N - 1) {
        if (__gcd(A[i], A[i + 1]) == 1) bad += 1;
    }
    return bad;
}

int solve() {
    repx(i, 1, N - 1) {
        if (A[i] == 1 && A[i - 1] != 1 && A[i + 1] != 1) {
            A[i] = 0;
            K -= 1;
            if (K == 0) return getbad();
        }
    }

    repx(i, 1, N - 1) {
        if (__gcd(A[i], A[i - 1]) == 1 && __gcd(A[i], A[i + 1]) == 1 && A[i - 1] != 1 && A[i + 1] != 1) {
            A[i] = 0;
            K -= 1;
            if (K == 0) return getbad();
        }
    }

    vector<pair<int, int>> G;
    for (int i = 0; i < N;) {
        if (A[i] != 1) {
            i++;
            continue;
        }
        int l = i;
        while (i < N && A[i] == 1) i++;
        if (l > 0 && i < N) G.push_back({i - l, l});
    }
    sort(G.begin(), G.end());

    for (auto [sz, l] : G) {
        repx(i, l, l + sz) {
            A[i] = 0;
            K -= 1;
            if (K == 0) return getbad();
        }
    }

    rep(i, N) {
        if ((i > 0 && __gcd(A[i], A[i - 1]) == 1) || (i < N - 1 && __gcd(A[i], A[i + 1]) == 1)) {
            A[i] = 0;
            K -= 1;
            if (K == 0) return getbad();
        }
    }

    return getbad();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        A.resize(N);
        rep(i, N) cin >> A[i];
        cout << solve() << "\n";
    }
}
