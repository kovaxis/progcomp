#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const int INF = 1e9;

template <class T>
struct Sparse {
    vector<vector<T>> st;

    Sparse() {}

    void reset(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }

    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return max(st[i][l], st[i][r - (1 << i)]); // query op
    }
};

int M, N, T;
vector<vector<int>> A;

Sparse<pair<int, int>> maxrect;
Sparse<int> maxedge, minrect;
vector<int> maxcol;

int solverows(int j0, int j1) {
    // precompute tables
    maxcol.resize(N);
    rep(i, N) {
        maxcol[i] = 0;
        repx(j, j0, j1 + 1) maxcol[i] = max(maxcol[i], A[j][i]);
    }

    maxedge.reset(N);
    rep(i, N) maxedge.set(i, max(A[j0][i], A[j1][i]));
    maxedge.init();

    maxrect.reset(N);
    rep(i, N) maxrect.set(i, {maxcol[i], i});
    maxrect.init();

    minrect.reset(N);
    rep(i, N) {
        int minval = INF;
        repx(j, j0, j1 + 1) minval = min(minval, A[j][i]);
        minrect.set(i, -minval);
    }
    minrect.init();

    // iterate over left edges
    int ans = 0;
    rep(i0, N) {
        // find largest right edge taking only threshold into account
        int i1;
        {
            int l = i0, r = N - 1;
            while (l != r) {
                int m = (l + r + 1) / 2;
                int diff = maxrect.query(i0, m + 1).first - (-minrect.query(i0, m + 1));
                cerr << "  max in range from " << i0 + 1 << " to " << m + 1 << " is " << maxrect.query(i0, m + 1).first << endl;
                cerr << "  min in range from " << i0 + 1 << " to " << m + 1 << " is " << -minrect.query(i0, m + 1) << endl;
                cerr << "  difference from " << i0 + 1 << " to " << m + 1 << " is " << diff << endl;
                if (diff <= T) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            i1 = l;
        }

        // if maximum is in one of the edges, dont adjust
        auto [mx, mx_pos] = maxrect.query(i0, i1 + 1);
        cerr << "  max edge: " << maxedge.query(i0, i1 + 1) << endl;
        if (mx != max(maxcol[i0], maxedge.query(i0, i1 + 1))) {
            // adjust right edge to maximum pos
            cerr << "  adjusting position to " << mx_pos + 1 << endl;
            i1 = mx_pos;
        }

        // use right edge
        int area = (j1 - j0 + 1) * (i1 - i0 + 1);
        cerr << "area for (" << j0 + 1 << ", " << i0 + 1 << ") to (" << j1 + 1 << ", " << i1 + 1 << ") is " << area << endl;
        ans = max(ans, area);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N >> T;
    A.resize(M, vector<int>(N));
    rep(j, M) rep(i, N) cin >> A[j][i];

    int ans = 0;
    rep(j0, M) repx(j1, j0, M) {
        ans = max(ans, solverows(j0, j1));
    }
    cout << ans << "\n";
}
