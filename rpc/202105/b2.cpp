#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; i++)
#define repx(i, a, b) for (int i = a; i < b; i++)
typedef long long ll;

int ans = 0;

vector<int> A;
void backtracking(vector<int>& B, int inicio) {
    int mini = abs(B.back() - B[0]);
    int maxi = B[0] + B[1];

    repx(i, inicio + 1, A.size()) {
        if (mini < A[i] && A[i] < maxi) {
            ans++;
            B.push_back(A[i]);
            backtracking(B, i);
            B.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    A.resize(n);
    rep(i, n) cin >> A[i];
    sort(A.begin(), A.end());

    rep(i, n) repx(j, i + 1, n) {
        vector<int> B = {A[i], A[j]};
        backtracking(B, j);
    }
    cout << ans << "\n";
    return 0;
}