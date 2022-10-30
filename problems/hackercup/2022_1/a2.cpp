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
    vector<int> v, p;
    v.insert(v.end(), a.begin(), a.end());
    v.push_back(-1);
    v.insert(v.end(), b.begin(), b.end());
    v.insert(v.end(), b.begin(), b.end());

    int n = v.size(), j;
    p.resize(n), p[0] = 0;
    repx(i, 1, n)
    {
        for (j = p[i - 1]; j > 0 && v[j] != v[i];)
            j = p[j - 1];
        p[i] = j + (v[j] == v[i]);
    }

    vector<bool> sols(N);
    bool any = false;
    repx(i, N + 1, v.size())
    {
        if (p[i] == N)
            sols[((i + 1) - (N + 1)) % N] = true, any = true;
    }
    if (!any)
        return false;

    if (N == 2)
        K %= 2;
    if (K == 0)
        if (!sols[0])
            return false;
    if (K == 1)
    {
        bool anydif = false;
        repx(i, 1, N) anydif |= sols[i];
        if (!anydif)
            return false;
    }
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
