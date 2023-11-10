#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 2e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N, M;
        cin >> N >> M;
        vector<int> A(N), B(M);
        rep(i, N) cin >> A[i];
        rep(j, M) cin >> B[j];

        sort(B.begin(), B.end());
        int j = M - 1;
        vector<int> Z;
        rep(i, N) {
            while (j >= 0 && B[j] >= A[i]) Z.push_back(B[j]), j--;
            Z.push_back(A[i]);
        }
        while (j >= 0) Z.push_back(B[j]), j--;

        for (int x : Z) cout << x << " ";
        cout << "\n";
    }
}
