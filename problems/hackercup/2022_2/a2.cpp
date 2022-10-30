#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1)   \
    cerr

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int M = 4;
const ll MOD[M] = {1000001087, 1000001371, 1000003967, 1000003987};
static vector<ll> P[M];
static map<ll, int> INVP[M];

template <class T>
struct StSum
{
    int m;
    vector<T> node;

    void reset(int N) { node.assign(4 * N, 0); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1)
    {
        node.resize(4 * a.size());
        if (vr == -1)
            vr = node.size() / 4;
        if (vr - vl == 1)
        {
            node[v] = a[vl]; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = (node[2 * v] + node[2 * v + 1]) % MOD[m]; // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1)
    {
        if (vr == -1)
            vr = node.size() / 4;
        if (l == vl && r == vr)
            return node[v];
        int vm = (vl + vr) / 2;
        T val = 0; // neutral element
        if (l >= vr || r <= vl)
            return val;
        val += query(l, min(r, vm), 2 * v, vl, vm); // query op
        val %= MOD[m];
        val += query(max(l, vm), r, 2 * v + 1, vm, vr); // query op
        val %= MOD[m];
        return val;
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1)
    {
        if (vr == -1)
            vr = node.size() / 4;
        if (vr - vl == 1)
        {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm)
        {
            update(i, val, 2 * v, vl, vm);
        }
        else
        {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v] = (node[2 * v] + node[2 * v + 1]) % MOD[m]; // query op
    }
};

int N;
vector<ll> arr;
StSum<ll> hashes[4];
map<int, set<int>> where;

ll binexp(ll a, ll m, ll M)
{
    assert(m >= 0);
    ll res = 1 % M;
    while (m)
    {
        if (m & 1)
            res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

bool almost_eq(int l, int mid, int r, bool del_left)
{
    rep(m, M)
    {
        ll lt = hashes[m].query(l, mid);
        ll rt = hashes[m].query(mid, r);
        int find_l = mid, find_r = r;
        if (del_left)
            swap(lt, rt), find_l = l, find_r = mid;

        ll diff = ((rt - lt) % MOD[m] + MOD[m]) % MOD[m];
        ll missing = INVP[m][diff];
        auto it = where[missing].lower_bound(find_l);
        if (it == where[missing].end())
            return false;
        if (*it >= find_r)
            return false;
        // cerr << "found missing value " << missing << " at position " << *it + 1 << endl;
    }

    /*int differ = 0;
    repx(k, 'a', 'z' + 1)
    {
        int diff = getcnt(k, mid, r) - getcnt(k, l, mid);
        diff *= invert;
        if (diff == 0)
            continue;
        if (diff != 1)
            return false;
        differ += diff;
    }
    if (differ > 1)
        return false;*/
    return true;
}

bool is_valid(int l, int r)
{
    if ((r - l) % 2 == 0)
        return false;
    return almost_eq(l, (l + r) / 2, r, false) || almost_eq(l, (l + r + 1) / 2, r, true);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(m, M) P[m].resize(2e6), P[m][0] = 1;
    rep(m, M) P[m][1] = rng();
    rep(m, M) P[m][1] %= 1 << 29;
    rep(m, M) repx(i, 2, 2e6) P[m][i] = P[m][i - 1] * P[m][1] % MOD[m];
    rep(m, M) rep(i, 2e6) INVP[m][P[m][i]] = i;

    cerr << "built P" << endl;

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cin >> N;
        arr.resize(N);
        rep(i, N) cin >> arr[i];

        where.clear();
        rep(i, N) where[arr[i]].insert(i);

        rep(m, M)
        {
            hashes[m].m = m;
            hashes[m].reset(N);
            rep(i, N) hashes[m].update(i, P[m][arr[i]]);
        }

        int Q, ans = 0;
        cin >> Q;
        rep(q, Q)
        {
            int t, l, r;
            cin >> t >> l >> r;
            l -= 1;
            if (t == 1)
            {
                // set arr[l] = r
                // cerr << "setting arr[" << l + 1 << "] = " << r << endl;
                where[arr[l]].erase(l);
                rep(m, M) hashes[m].update(l, P[m][r]);
                arr[l] = r;
                where[r].insert(l);
            }
            else
            {
                // check if [l, r) is valid
                // cerr << "checking range [" << l + 1 << ", " << r << "]" << endl;
                ans += is_valid(l, r);
            }
        }

        cout << "Case #" << tc + 1 << ": " << ans
             << "\n";
    }
}
