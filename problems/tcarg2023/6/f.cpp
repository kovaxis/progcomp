// 6F

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

const ll INF = 1e18;

struct Expr {
    int8_t result[3][3];

    friend istream &operator>>(istream &s, Expr &e) {
        rep(x, 3) rep(y, 3) {
            char r;
            s >> r;
            int ri;
            if (r == 'F') ri = 0;
            else if (r == 'U') ri = 1;
            else if (r == 'T') ri = 2;
            e.result[x][y] = ri;
        }
        return s;
    }

    static Expr fromstr(string s) {
        stringstream ss(s);
        Expr e;
        ss >> e;
        return e;
    }

    Expr operate(Expr l, Expr r) {
        Expr e;
        rep(x, 3) rep(y, 3) {
            e.result[x][y] = result[l.result[x][y]][r.result[x][y]];
        }
        return e;
    }

    int id() const {
        int id = 0;
        rep(x, 3) rep(y, 3) id = id * 3 + result[x][y];
        return id;
    }

    static Expr fromid(int id) {
        Expr e;
        for (int x = 2; x >= 0; x--)
            for (int y = 2; y >= 0; y--) {
                e.result[x][y] = id % 3;
                id /= 3;
            }
        return e;
    }

    Expr transpose() {
        Expr e;
        rep(x, 3) rep(y, 3) e.result[x][y] = result[y][x];
        return e;
    }
};

bitset<19683> canreach;
vector<Expr> canreach_list;
vector<Expr> basic = {
    Expr::fromstr("FFF FUU FUT"),
    Expr::fromstr("FUT UUT TTT"),
    Expr::fromstr("TTT UTT FUT"),
    Expr::fromstr("TFF FTF FFT"),
    Expr::fromstr("FFF FUU FUT").transpose(),
    Expr::fromstr("FUT UUT TTT").transpose(),
    Expr::fromstr("TTT UTT FUT").transpose(),
    Expr::fromstr("TFF FTF FFT").transpose(),
};
vector<Expr> initial = {
    Expr::fromstr("FFFUUUTTT"),
    Expr::fromstr("FFFUUUTTT").transpose(),
};

int main() {
    int qi = 0;
    vector<Expr> q;
    for (Expr e : initial) {
        canreach[e.id()] = true;
        q.push_back(e);
        canreach_list.push_back(e);
    }

    while (qi < q.size()) {
        Expr ne = q[qi++];
        // cerr << "checking expression " << ne.id() << " at index " << qi << endl;
        for (int i = 0; i < canreach_list.size(); i++) {
            for (Expr op : basic) {
                Expr r = op.operate(canreach_list[i], ne);
                int rid = r.id();
                if (!canreach[rid]) {
                    // cerr << "found " << canreach_list.size() << ", " << (q.size() - qi) << " left in queue" << endl;
                    canreach.set(rid);
                    canreach_list.push_back(r);
                    q.push_back(r);
                }
            }
        }

        /*bool did_anything = false;
        cerr << "iterating" << endl;
        rep(i, canreach.size()) rep(j, canreach.size()) if (canreach[i] && canreach[j]) {
            for (Expr op : basic) {
                Expr r = op.operate(Expr::fromid(i), Expr::fromid(j));
                if (!canreach[r.id()]) {
                    did_anything = true;
                    canreach[r.id()] = true;
                }
            }
        }
        if (!did_anything) break;*/
    }

    cerr << "done" << endl;

    int N;
    cin >> N;
    rep(q, N) {
        Expr expr;
        cin >> expr;
        cout << (canreach[expr.id()] ? "definable" : "undefinable") << endl;
    }
}
