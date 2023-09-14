#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Bridge {
    int i, d;
};

int N, M, S;
vector<Bridge> B;

int wrap(int i) { return (i % N + N) % N; }

struct Stairs {
    vector<int> D;
    set<int> inv_mem[3];

    set<int> &inv(int v) { return inv_mem[v + 1]; }

    Stairs() {}
    Stairs(vector<int> acc) {
        D.resize(N);
        rep(i, N) D[i] = acc[wrap(i + 1)] - acc[i];
        rep(i, N) inv(D[i]).insert(i);
    }

    void modify(int i, int v) {
        assert(-1 <= v && v <= 1);
        inv(D[i]).erase(i);
        D[i] = v;
        inv(D[i]).insert(i);
    }

    void fix_nonplus_right(int i) {
        // increase the first nonplus after i by 1
        assert(D[i] == 1);
        int d = N;
        repx(k, -1, 1) {
            if (!inv(k).empty()) {
                auto it = inv(k).lower_bound(i);
                if (it == inv(k).end()) it = inv(k).begin();
                d = min(d, wrap(*it - i));
            }
        }
        modify(wrap(i + d), D[wrap(i + d)] + 1);
    }

    void fix_nonminus_left(int i) {
        // decrease the last nonminus before i by 1
        assert(D[i] == -1);
        int d = N;
        repx(k, 0, 2) {
            if (!inv(k).empty()) {
                auto it = inv(k).lower_bound(i);
                if (it == inv(k).begin()) it = inv(k).end();
                --it;
                d = min(d, wrap(i - *it));
            }
        }
        modify(wrap(i - d), D[wrap(i - d)] - 1);
    }

    void swap_pair(int i) {
        if (D[i] == 0) return;
        int a[4];
        a[0] = 0;
        rep(k, 3) a[k + 1] = a[k] + D[wrap(i - 1 + k)];
        swap(a[1], a[2]);
        int fix = 0;
        if (D[i] > 0) {
            // first goes up
            if (a[0] + 1 < a[1]) a[1] = a[0] + 1;
            // second goes down
            if (a[3] > a[2] + 1) a[3] = a[2] + 1, fix = 1;
        } else {
            // second goes up
            if (a[3] + 1 < a[2]) a[2] = a[3] + 1;
            // first goes down
            if (a[0] > a[1] + 1) a[0] = a[1] + 1, fix = -1;
        }
        rep(k, 3) modify(wrap(i - 1 + k), a[k + 1] - a[k]);
        if (fix == 1) fix_nonplus_right(wrap(i + 1));
        if (fix == -1) fix_nonminus_left(wrap(i - 1));
    }

    vector<int> eval() {
        vector<int> a(N);
        rep(i, N - 1) a[i + 1] = a[i] + D[i];
        assert(a[0] == a[N - 1] + D[N - 1]);
        int mn = 0;
        rep(i, N) mn = min(mn, a[i]);
        rep(i, N) a[i] -= mn;
        return a;
    }
} A;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S;
    S--;
    B.resize(M);
    rep(j, M) {
        cin >> B[j].d >> B[j].i;
        B[j].i--;
    }

    sort(B.begin(), B.end(), [](Bridge a, Bridge b) {
        return a.d > b.d;
    });

    {
        vector<int> a(N);
        rep(i, N) a[wrap(S + i)] = i;
        rep(i, N) a[wrap(S - i)] = min(a[wrap(S - i)], i);
        A = a;
    }

    // cerr << "initial:" << endl;
    // vector<int> a = A.eval();
    // rep(i, N) cerr << a[i] << " ";
    // cerr << endl;

    for (Bridge b : B) {
        A.swap_pair(b.i);

        // cerr << "after bridge at " << b.i + 1 << ":" << endl;
        // vector<int> a = A.eval();
        // rep(i, N) cerr << a[i] << " ";
        // cerr << endl;
    }

    vector<int> ans = A.eval();
    rep(i, N) {
        cout << ans[i] << "\n";
    }
}
