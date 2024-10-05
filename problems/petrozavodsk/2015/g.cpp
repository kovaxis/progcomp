#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
struct item {
    int p;
    pair<ll, ll> k;
    ll sm;
    item *l = 0, *r = 0;
    item(ll k) : p(rng()), k(k, rng()), sm(k) {}
};

ll getsm(item *x) {
    return x ? x->sm : 0;
}
void recalc(item *x) {
    if (x) x->sm = getsm(x->l) + x->k.first + getsm(x->r);
}
void split(item *x, pair<ll, ll> k, item *&l, item *&r) {
    if (!x) l = r = 0;
    else if (k < x->k) split(x->l, k, l, x->l), r = x;
    else split(x->r, k, x->r, r), l = x;
    recalc(x);
}
void merge(item *&x, item *l, item *r) {
    if (!l || !r) x = l ? l : r;
    else if (l->p > r->p) merge(l->r, l->r, r), x = l;
    else merge(r->l, l, r->l), x = r;
    recalc(x);
}
void insert(item *&x, item *y) {
    if (!x) x = y;
    else if (y->p > x->p) split(x, y->k, y->l, y->r), x = y;
    else insert(y->k < x->k ? x->l : x->r, y);
    recalc(x);
}
void erase(item *&x, ll k) {
    if (x->k.first == k) merge(x, x->l, x->r);
    else erase(k < x->k.first ? x->l : x->r, k);
    recalc(x);
}
void show(ostream &s, item *x, int d = 0) {
    if (x->l) show(s, x->l, d + 1);
    rep(i, d) s << "  ";
    s << x->k.first << endl;
    if (x->r) show(s, x->r, d + 1);
}

int N;
vector<ll> A;
item *B;

void init() {
    A.assign(N, 0);
    rep(i, N) {
        insert(B, new item(0));
    }
}

void update(int i, ll x) {
    erase(B, A[i]);
    A[i] = x;
    insert(B, new item(x));
    // cerr << "after update " << i + 1 << " <- " << x << ":" << endl;
    // show(cerr, B, 4);
}

int solve() {
    item *f = B;
    while (f->l) f = f->l;
    // cerr << "searching with first = " << f->k.first << endl;
    int ans = 1;
    pair<ll, ll> nxt = f->k;
    nxt.second += 1;
    while (true) {
        item *l, *r;
        split(B, nxt, l, r);
        if (!r) {
            merge(B, l, r);
            break;
        }
        item *x = r;
        while (x->l) x = x->l;
        // cerr << "  value " << x->k.first << " is " << (x->k.first >= getsm(l)) << endl;
        ans += (x->k.first >= getsm(l));
        nxt = {getsm(l) + x->k.first, 0};
        merge(B, l, r);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    init();
    rep(i, N) {
        ll x;
        cin >> x;
        update(i, x);
    }
    int Q;
    cin >> Q;
    cout << solve() << "\n";
    rep(qi, Q) {
        int i;
        ll x;
        cin >> i >> x;
        i -= 1;
        update(i, x);
        cout << solve() << "\n";
    }
}
