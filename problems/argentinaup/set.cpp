#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

typedef int K;
typedef int V;

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {
    struct Node {
        K k;
        V v;
        int p, l, r;

        Node(K k, V v) : k(k), v(v), p(rng()), l(0), r(0) {}
    };

    vector<Node> a;
    int root = -1;

    // cannot already be in treap!
    void insert(int v, int &u) {
        if (u == -1) u = v;
        else if (a[v].p > a[u].p) {
            swap(u, v);
            return insert(v, u);
        } else if (a[v].k < a[u].k) insert(v, a[u].l);
        else insert(v, a[u].r);
    }
    void erase(K k, int &u) {
        if (a[u].k == k) {
            // r == -1  l == -1
            // r == -1  l != -1
            // r != -1  l == -1
            // r != -1  l != -1
            if (a[u].r != -1 && (a[u].l == -1 || a[a[u].l].p < a[a[u].r].p)) {
                // promote the right node
                int v = u;
                u = a[v].r;
                if (a[v].l != -1) insert()
            } else if (a[u].l != -1) {
                // promote the left node
            } else {
                // dont promote
            }
        }
    }

    void set(K k, V v) { a.push_back({k, v}), insert(a.size() - 1, root); }
};

int main() {
}
