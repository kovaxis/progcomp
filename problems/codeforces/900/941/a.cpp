#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<int> A(N);
        rep(i, N) cin >> A[i];

        sort(A.begin(), A.end());
        A.resize(unique(A.begin(), A.end()) - A.begin());
        invrepx(i, 1, N) A[i] = A[i] - A[i - 1];

        int i = 0;
        while (i < N && A[i] == 1) i += 1;

        bool w = (i % 2) ^ (i == (int)A.size());

        cout << (w ? "Bob" : "Alice") << "\n";
    }
}
