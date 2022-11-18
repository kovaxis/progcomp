#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct Node {
    char t;
    ll x, y, z;
};

ll M, N, Q;
vector<Node> nodes;
unordered_map<ll, ll> getfrom;
unordered_map<ll, unordered_map<ll, ll>> valuemem;
unordered_map<ll, ll> lenmem;

ll length(ll x) {
    if (x == 1) return M;
    if (lenmem.count(x)) return lenmem[x];
    Node &n = nodes[getfrom[x]];
    if (n.t == 'S') {
        if (x == n.y) {
            // long stream
            return lenmem[x] = (length(n.x) + 1) / 2;
        } else if (x == n.z) {
            // short stream
            return lenmem[x] = length(n.x) / 2;
        } else {
            throw "unreachable";
        }
    } else if (n.t == 'M') {
        return lenmem[x] = length(n.x) + length(n.y);
    } else {
        throw "unreachable";
    }
}

ll value(ll x, ll k) {
    if (x == 1) return k <= M ? k : -1;
    if (valuemem[x].count(k)) return valuemem[x][k];
    int i = getfrom[x];
    Node &n = nodes[i];
    ll val;
    if (n.t == 'S') {
        if (x == n.y) {
            // first stream
            val = value(n.x, 2 * k - 1);
        } else if (x == n.z) {
            // second stream
            val = value(n.x, 2 * k);
        }
    } else if (n.t == 'M') {
        ll minlen = min(length(n.x), length(n.y));
        if (k <= 2 * minlen) val = (k % 2 == 1 ? value(n.x, (k + 1) / 2) : value(n.y, (k + 1) / 2));
        else {
            ll longin = length(n.x) > length(n.y) ? n.x : n.y;
            val = value(longin, k - minlen);
        }
    } else {
        throw "unreachable";
    }
    return valuemem[x][k] = val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N >> Q;
    nodes.resize(N);
    rep(i, N) {
        Node &n = nodes[i];
        cin >> n.t >> n.x >> n.y >> n.z;
    }

    rep(i, N) {
        Node &n = nodes[i];
        if (n.t == 'S') {
            getfrom[n.y] = i;
            getfrom[n.z] = i;
        } else if (n.t == 'M') {
            getfrom[n.z] = i;
        }
    }

    rep(q, Q) {
        ll x, k;
        cin >> x >> k;
        ll ans = value(x, k);
        if (ans == -1) cout << "none\n";
        else cout << ans << "\n";
    }
}
