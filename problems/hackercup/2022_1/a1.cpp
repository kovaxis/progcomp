#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<int> a, b;

bool solve()
{
    int s = 0;
    for (; s < N; s++)
        if (b[s] == a[0])
            break;
    rep(i, N) if (a[i] != b[(s + i) % N]) return false;
    if (N == 2 && K % 2 != s)
        return false;
    if (K == 0 && s != 0)
        return false;
    if (K == 1 && s == 0)
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cin >> N >> K;
        a.resize(N), b.resize(N);
        rep(i, N) cin >> a[i];
        rep(i, N) cin >> b[i];
        cout << "Case #" << tc + 1 << ": " << (solve() ? "YES" : "NO") << "\n";
    }
}
