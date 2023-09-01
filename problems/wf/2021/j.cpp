#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Node {
    bool split;
    int x, y, z;
};

ll M;
int N, Q;
vector<Node> A;
vector<int> B;
vector<ll> L;

ll getlen(int x) {
    if (L[x] != -1) return L[x];
    if (x == 1) return L[x] = M;
    int i = B[x];
    if (A[i].split) {
        ll srclen = getlen(A[i].x);
        if (x == A[i].y) {
            return L[x] = (srclen + 1) / 2;
        } else {
            return L[x] = srclen / 2;
        }
    } else {
        ll l = getlen(A[i].x), r = getlen(A[i].y);
        return L[x] = l + r;
    }
}

ll getnum(int x, ll k) {
    if (x == 1) return k < 1 || k > M ? -1 : k;
    int i = B[x];
    if (A[i].split) {
        if (x == A[i].y) {
            // left
            return getnum(A[i].x, 2 * k - 1);
        } else {
            // right
            return getnum(A[i].x, 2 * k);
        }
    } else {
        ll l = getlen(A[i].x), r = getlen(A[i].y);
        ll normal = min(l, r) * 2;
        if (k <= normal) {
            if (k % 2) {
                // left
                return getnum(A[i].x, (k + 1) / 2);
            } else {
                // right
                return getnum(A[i].y, k / 2);
            }
        } else {
            if (l > r) {
                // only left
                return getnum(A[i].x, k - normal / 2);
            } else {
                // ony right
                return getnum(A[i].y, k - normal / 2);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N >> Q;
    A.resize(N), B.resize(3 * N + 1), L.resize(3 * N + 1, -1);
    rep(i, N) {
        char ty;
        int x, y, z;
        cin >> ty >> x >> y >> z;
        if (ty == 'S') {
            A[i] = {true, x, y, z};
            B[y] = i;
            B[z] = i;
        } else if (ty == 'M') {
            A[i] = {false, x, y, z};
            B[z] = i;
        }
    }
    rep(q, Q) {
        int x;
        ll k;
        cin >> x >> k;
        ll y = getnum(x, k);
        if (y == -1) cout << "none\n";
        else cout << y << "\n";
    }
}
