#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

struct P {
    ll x, y;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }

    ll operator*(P r) const {
        return x * r.x + y * r.y;
    }
    ll operator/(P r) const {
        return rot() * r;
    }

    P rot() const { return {-y, x}; }

    bool half() const {
        return y < 0 || (y == 0 && x < 0);
    }

    bool operator<(P r) const {
        bool a = half(), b = r.half();
        if (a != b) return a < b;
        return *this / r > 0;
    }

    static P read() {
        double x, y;
        cin >> x >> y;
        ll ix = x * 1e6 + 0.5;
        ll iy = y * 1e6 + 0.5;
        return {ix, iy};
    }
};

int N, M;
vector<P> C, S;

bool lessthan180(P base, P a, P b) {
    P da = a - base, db = b - base;
    ll x = da / db, d = da * db;
    return x > 0 || (x == 0 && d > 0);
}

bool samedir(P base, P a, P b) {
    P da = a - base, db = b - base;
    return da / db == 0 && da * db > 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    C.resize(N), S.resize(M);
    rep(i, N) C[i] = P::read();
    rep(j, M) S[j] = P::read();

    int ans = 0;
    rep(k, M) {
        vector<pair<P, int>> A;
        rep(i, N) A.push_back({C[i], 1});
        rep(j, M) if (j != k) A.push_back({S[j], 2});
        sort(A.begin(), A.end(), [&](auto &a, auto &b) {
            return a.first - S[k] < b.first - S[k];
        });
        int n = A.size();
        rep(i, n) A.push_back(A[i]);

        int l = 0, r = 0, choc = 0, straw = 0;
        while (l < n) {
            while (r < l + n && lessthan180(S[k], A[l].first, A[r].first)) {
                // add A[r] to the set
                choc += (A[r].second == 1);
                straw += (A[r].second == 2);
                r++;
            }
            // check the set
            if (straw == 0) ans = max(ans, choc);
            // remove all that are collinear from the set
            int start = l;
            while (l < n && samedir(S[k], A[start].first, A[l].first)) {
                // remove A[l] from the set
                choc -= (A[l].second == 1);
                straw -= (A[l].second == 2);
                l++;
            }
        }
    }

    cout << ans << endl;
}