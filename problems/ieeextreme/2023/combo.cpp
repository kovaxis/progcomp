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

const int MOD = 1e9 + 9;

struct Dsu {
    vector<int> p, r;

    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets that `i` and `j` belong to
    void unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

int N, M, T;
ll H, A, B, Q;
Dsu dsu;
vector<bool> allow;
set<int> seen;
vector<int> D, W;
vector<int> que;
int que_i;

int pow10(int x) {
    int r = 1;
    while (x) r *= 10, x--;
    return r;
}

int delta(int x, int i, int d) {
    int dig = x / pow10(i) % 10;
    int newdig = (dig + d + 10) % 10;
    return x + (newdig - dig) * pow10(i);
}

void connect(int x, int y) {
    if (allow[x] && allow[y]) {
        cerr << "uniting " << x << " and " << y << endl;
        dsu.unite(x, y);
    }
}

void connect_neighbors_of(int x) {
    rep(i, N) {
        connect(x, delta(x, i, 1));
        connect(x, delta(x, i, -1));
    }
}

void visit(int x, int y) {
    if (!allow[y]) return;
    if (D[y] < D[x] + 1) return;
    if (D[y] > D[x] + 1) que.push_back(y);
    D[y] = D[x] + 1;
    W[y] = (W[x] + W[y]) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> T >> H >> A >> B >> Q;
        M = pow10(N);
        dsu.reset(M);
        allow.assign(M, false);
        allow[0] = true;
        allow[T] = true;
        connect_neighbors_of(0);
        seen.clear();

        while (true) {
            // check if looping
            if (seen.count(H)) {
                cerr << "looped at " << H << endl;
                break;
            }

            // check if target is reachable
            if (dsu.find(0) == dsu.find(T)) {
                cerr << "can reach target " << T << endl;
                break;
            }

            // allow h
            cerr << "allowing " << H << endl;
            seen.insert(H);
            allow[H % M] = true;
            connect_neighbors_of(H % M);

            // advance sequence
            H = (A * H + B) % Q;
        }

        if (dsu.find(0) == dsu.find(T)) {
            // there is a way
            que_i = 0;
            que.clear();
            D.assign(M, 1e9);
            W.assign(M, 0);
            que.push_back(0);
            D[0] = 0;
            W[0] = 1;
            while (que_i < que.size()) {
                int x = que[que_i++];
                rep(i, N) {
                    visit(x, delta(x, i, 1));
                    visit(x, delta(x, i, -1));
                }
            }
            cout << D[T] << " " << W[T] << "\n";
        } else {
            // there is no way
            cout << "-1\n";
        }
    }
}
