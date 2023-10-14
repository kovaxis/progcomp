#include "../common.h"

// usage:
// St<Node<ll>> st;
// st = {N};
// st.update(index, new_value);
// Node<ll> result = st.query(left, right);

template <class T>
struct St {
    int n;
    vector<T> a;

    T neut() { return 0; }
    T merge(T x, T y) { return x + y; }

    St(int n = 0) : n(n), a(2 * n, neut()) {}

    T query(int l, int r) {
        T x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, T x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};
