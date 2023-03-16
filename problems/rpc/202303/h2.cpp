#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    vector<int> nxtl, nxtr;
    vector<ll> A;
    cin >> N;
    A.resize(2 * N);
    rep(i, N) cin >> A[i];
    rep(i, N) A[i + N] = A[i];

    vector<ll> sum(A);
    repx(i, 1, 2 * N) {
        sum[i] += sum[i - 1];
    }

    int best = 1e18;
    rep(start, N) {
        int l = start + 1, r = start + N - 1;
        int ans = A[start];
        while () {
            if (A[l] < A[r]) {
                ans = max(ans, A[l]);
                int next = nxtr[l];
            }
        }
    }
}