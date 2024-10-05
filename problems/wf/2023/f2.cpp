#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

typedef pair<short, short> Pos;

ostream &operator<<(ostream &s, vector<int> &a) {
    for (int x : a) s << x << " ";
    return s;
}
ostream &operator<<(ostream &s, vector<pair<int, int>> &a) {
    for (auto x : a) s << x.first << "," << x.second << " ";
    return s;
}

int N, M;

struct Board {
    char a[512][512];

    void read() {
        rep(i, N) rep(j, M) cin >> a[i][j];
    }

    void print() const {
        rep(i, N) {
            rep(j, M) cerr << a[i][j];
            cerr << endl;
        }
    }

    bool operator==(const Board &r) const {
        rep(i, N) rep(j, M) if (a[i][j] != r.a[i][j]) return false;
        return true;
    }

    char operator[](Pos x) const {
        return a[x.first][x.second];
    }
};

struct Arrows {
    Pos p[512][512];

    Pos operator[](Pos x) {
        return p[x.first][x.second];
    }
};

Board ini, fin;
vector<int> opstk;
bool ans;
vector<int> fact, reduced;
vector<pair<int, int>> f;

void gravity(const Board &src, Board &dst, Arrows &arr, int op) {
    rep(i, N) rep(j, M) dst.a[i][j] = '.';
    if (op == 0) {
        rep(i, N) {
            int k = M - 1;
            invrep(j, M) if (src.a[i][j] != '.') arr.p[i][j] = {i, k}, dst.a[i][k--] = src.a[i][j];
        }
    } else if (op == 1) {
        rep(j, M) {
            int k = N - 1;
            invrep(i, N) if (src.a[i][j] != '.') arr.p[i][j] = {k, j}, dst.a[k--][j] = src.a[i][j];
        }
    } else if (op == 2) {
        rep(i, N) {
            int k = 0;
            rep(j, M) if (src.a[i][j] != '.') arr.p[i][j] = {i, k}, dst.a[i][k++] = src.a[i][j];
        }
    } else if (op == 3) {
        rep(j, M) {
            int k = 0;
            rep(i, N) if (src.a[i][j] != '.') arr.p[i][j] = {k, j}, dst.a[k++][j] = src.a[i][j];
        }
    } else throw "?";
}

void factorize(int x, vector<pair<int, int>> &f) {
    f.clear();
    while (x != 1) {
        int ff = fact[x];
        x = reduced[x];
        if (f.size() && f.back().first == ff) f.back().second *= ff;
        else f.push_back({ff, ff});
    }
}

void checkloop(const Board &b) {
    rep(i, N) rep(j, M) if ((b.a[i][j] == '.') != (fin.a[i][j] == '.')) return;
    cerr << "checking circling with steps " << opstk << endl;
    // b.print();
    int dir = (4 + opstk[opstk.size() - 1] - opstk[opstk.size() - 2]) % 4;
    Arrows tmparr[4];
    Board tmp[5];
    tmp[0] = b;
    rep(k, 4) {
        gravity(tmp[k], tmp[k + 1], tmparr[k], (opstk.back() + (k + 1) * dir) % 4);
    }
    Arrows arr;
    rep(i, N) rep(j, M) if (b.a[i][j] != '.') arr.p[i][j] = tmparr[3][tmparr[2][tmparr[1][tmparr[0].p[i][j]]]];
    map<int, pair<int, int>> restrs;
    rep(i0, N) rep(j0, M) if (tmp[0].a[i0][j0] != '.') {
        Pos cur = {i0, j0};
        int m0 = -1, m1 = -1, k = 0;
        // cerr << "  loop starting at " << i0 << " " << j0 << endl;
        do {
            Pos p0 = {i0, j0}, p1 = cur;
            bool match = true;
            do {
                if (b[p0] != fin[p1]) match = false;
                p0 = arr[p0], p1 = arr[p1];
            } while (p0 != Pos{i0, j0});
            // cerr << "    step " << k << " at " << cur.first << " " << cur.second << " with " << b[cur] << " has match = " << match << endl;
            if (match) {
                if (m0 == -1) m0 = k;
                else if (m1 == -1) m1 = k;
            }
            tmp[0].a[cur.first][cur.second] = '.';
            cur = arr[cur];
            k += 1;
        } while (cur != Pos{i0, j0});
        // cerr << "  loop at " << i0 << " " << j0 << " with len " << k << ", m0 = " << m0 << ", m1 = " << m1 << endl;
        if (m0 == -1) return;
        if (m1 == -1) m1 = m0 + k;
        int m = m1 - m0;
        // t === m0 (mod m)
        factorize(m, f);
        // cerr << "  checking loop of len " << m << " and remainder " << m0 << " with factorization " << f << endl;
        for (auto [prime, thispow] : f) {
            auto &[allpow, allrem] = restrs[prime];
            if (allpow == 0) allpow = 1;
            int compow = min(allpow, thispow);
            if (m0 % compow != allrem % compow) {
                // cerr << "  mismatch (m0 = " << m0 << ", allrem = " << allrem << ", compow = " << compow << ")" << endl;
                return;
            }
            allpow = max(allpow, thispow);
            allrem = max(allrem, m0);
        }
    }
    cerr << "  match!" << endl;
    ans = true;
}

void backtrack(const Board &b) {
    if (opstk.size() >= 6) return;
    if (opstk.size() >= 2) checkloop(b);
    if (b == fin) {
        // cerr << "found board with steps " << opstk << endl;
        ans = true;
    }
    rep(op, 4) {
        int n = opstk.size();
        if (n > 0 && (op == opstk[n - 1] || (op + 2) % 4 == opstk[n - 1])) continue;
        if (n > 1 && op == opstk[n - 2]) continue;
        Board sub;
        Arrows arr;
        gravity(b, sub, arr, op);
        opstk.push_back(op);
        backtrack(sub);
        opstk.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    fact.resize(2 * N * M, 1), reduced.resize(2 * N * M, 1);
    repx(x, 2, 2 * N * M) if (fact[x] == 1) {
        for (int k = 1; k * x < 2 * N * M; k += 1)
            if (fact[k * x] == 1) {
                fact[k * x] = x;
                reduced[k * x] = k;
            }
    }

    ini.read(), fin.read();
    backtrack(ini);
    cout << (ans ? "yes" : "no") << endl;
}
