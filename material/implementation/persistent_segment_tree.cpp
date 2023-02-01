#include "../common.h"

template <class T>
struct Node {
    T x;
    int l, r;
};

// UNTESTED
template <class T>
struct Pst {
    int N;
    vector<Node<T>> a;
    vector<int> head;

    T neut() { return 0; }
    T merge(T l, T r) { return l + r; }

    int build(int vl, int vr) {
        if (vr - vl == 1) a.push_back(neut()); // node construction
        else {
            int vm = (vl + vr) / 2, l = build(vl, vm), r = build(vm, vr);
            a.push_back({merge(a[l].x, a[r].x), l, r}); // node merge
        }
        return a.size() - 1;
    }

    T query(int l, int r, int v, int vl, int vr) {
        if (l <= vl && r >= vr) return a[v].x; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return neut();                                  // item neutral
        return merge(query(a[v].l, l, r, vl, vm), query(a[v].r, l, r, vm, vr)); // item merge
    }

    int update(int i, T x, int v, int vl, int vr) {
        if (vr - vl == 1) v = a.size(), a.push_back(x); // item update
        else {
            int vm = (vl + vr) / 2;
            a.push_back(a[v]), v = a.size() - 1;
            if (i < vm) a[v].l = update(a[v].l, i, x, vl, vm);
            else a[v].r = update(a[v].r, i, x, vm, vr);
            a[v].x = merge(a[a[v].l].x, a[a[v].r].x); // node merge
        }
        return v;
    }

    Pst() {}
    Pst(int N) : N(N) { head.push_back(build(0, N)); }

    T query(int t, int l, int r) { return query(l, r, head[t], 0, N); }
    int update(int t, int i, T x) { return head.push_back(update(i, x, head[t], 0, N)), head.size() - 1; }
};
