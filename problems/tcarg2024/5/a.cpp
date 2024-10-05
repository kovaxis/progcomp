#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < ll(b); i++)
#define rep(i, n) repx(i, 0, n)

const double EPS = 1e-8;

struct P {
    double x, y;

    double magsq() const { return *this * *this; }

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(double r) const { return {x * r, y * r}; }
    P operator/(double r) const { return {x / r, y / r}; }
    double operator*(P r) const { return x * r.x + y * r.y; }
    double operator%(P r) const { return perp() * r; }

    P perp() const { return {-y, x}; }

    bool half() const { return (abs(y) <= EPS && x < -EPS) || y < -EPS; };
    double angcmp(P r) const {
        int h = (int)half() - r.half();
        return h ? h : r % *this;
    }

    friend ostream &operator<<(ostream &s, P r) {
        return s << r.x << " " << r.y;
    }
};

P mn, mx;

struct L {
    P o, d;
    int id;

    L(P o, P d, int id) : o(o), d(d), id(id) {}
    L(P ab, double c, int id) : o(ab * -c / ab.magsq()), d(ab.perp()), id(id) {}

    double side(P r) const { return (r - o) % d; }

    double inter(L r) const { return (r.o - o) % r.d; }

    P intersection(L r) const {
        return o + d * inter(r) / (d % r.d);
    }

    bool parallel(L r) const { return abs(d % r.d) <= EPS; }

    friend ostream &operator<<(ostream &s, L r) {
        return s << r.o << " -> " << (r.o + r.d);
    }
};

ostream &operator<<(ostream &s, const vector<L> &r) {
    bool first = true;
    for (const L &l : r) {
        if (!first) s << ", ";
        first = false;
        s << l;
    }
    return s;
}

ostream &operator<<(ostream &s, const vector<pair<vector<L>, int>> &r) {
    s << "{" << endl;
    for (const auto &[shape, d] : r) {
        s << "  (" << shape << "): " << d << endl;
    }
    return s << "}";
}

void halfplane_intersect(vector<L> &H) {
    H.push_back({mn, {mx.x - mn.x, 0}, 0});
    H.push_back({{mx.x, mn.y}, {0, mx.y - mn.y}, 1});
    H.push_back({mx, {mn.x - mx.x, 0}, 2});
    H.push_back({{mn.x, mx.y}, {0, mn.y - mx.y}, 3});

    // cerr << "added halfplanes to obtain (" << H << ")" << endl;

    sort(H.begin(), H.end(), [](L a, L b) {
        return a.d.angcmp(b.d) < 0;
    });
    deque<L> q;
    int n = 0;
    rep(i, H.size()) {
        // cerr << "q = (" << vector<L>(q.begin(), q.end()) << ")" << endl;
        // cerr << "processing " << H[i] << endl;
        while (n >= 2 && H[i].side(q[n - 1].intersection(q[n - 2])) >= -EPS)
            q.pop_back(), n--;
        while (n >= 2 && H[i].side(q[0].intersection(q[1])) >= -EPS)
            q.pop_front(), n--;
        // cerr << "  just before parallel check: " << vector<L>(q.begin(), q.end()) << endl;
        if (n > 0 && H[i].parallel(q[n - 1])) {
            if (H[i].d * q[n - 1].d < -EPS) {
                // cerr << "parallel in opposite direction: " << H[i] << " and " << q[n - 1] << endl;
                return H.clear();
            }
            if (H[i].side(q[n - 1].o) > EPS) q.pop_back(), n--;
            else continue;
        }
        q.push_back(H[i]), n++;
    }

    while (n >= 3 && q[0].side(q[n - 1].intersection(q[n - 2])) >= -EPS)
        q.pop_back(), n--;
    while (n >= 3 && q[n - 1].side(q[0].intersection(q[1])) >= -EPS)
        q.pop_front(), n--;
    if (n < 3) {
        // cerr << "<3" << endl;
        return H.clear();
    }

    H.clear();
    rep(i, n) H.push_back(q[i]);
}

vector<P> pointify(const vector<L> &q) {
    int n = q.size();
    vector<P> ps(n);
    rep(i, n) ps[i] = q[i].intersection(q[(i + 1) % n]);
    return ps;
}

struct Node {
    char ty;
    Node *l, *r;
    int a, b, c;
};

Node parse() {
    char openc;
    cin >> openc;
    if (openc == '(') {
        // operator
        Node l = parse();
        if (l.ty == '~') {
            char closec;
            cin >> closec;
            assert(closec == ')');
            l.ty = '!';
            return l;
        } else {
            char opc;
            cin >> opc;
            Node r = parse();
            char closec;
            cin >> closec;
            assert(closec == ')');
            Node *lx = (Node *)malloc(sizeof(Node));
            Node *rx = (Node *)malloc(sizeof(Node));
            *lx = l;
            *rx = r;
            return {opc, lx, rx};
        }
    } else if (openc == '[') {
        // atom
        Node x = {'.', nullptr, nullptr};
        char sep1, sep2, closec;
        cin >> x.a >> sep1 >> x.b >> sep2 >> x.c >> closec;
        assert(sep1 == ',');
        assert(sep2 == ',');
        assert(closec == ']');
        return x;
    } else if (openc == '!') {
        // negation
        Node *x = (Node *)malloc(sizeof(Node));
        *x = parse();
        return {'~', x};
    }
    throw "?";
}

vector<pair<vector<L>, int>> intersect(vector<pair<vector<L>, int>> left, vector<pair<vector<L>, int>> right) {
    // cerr << "intersecting:\n"
    //      << left << "\n"
    //      << right << endl;
    vector<pair<vector<L>, int>> res;
    for (auto &[lshape, ld] : left) {
        for (auto &[rshape, rd] : right) {
            vector<L> shape(lshape.begin(), lshape.end());
            shape.insert(shape.begin(), rshape.begin(), rshape.end());
            halfplane_intersect(shape);
            if (shape.size()) res.push_back({shape, ld * rd});
        }
    }
    // cerr << "result is:\n"
    //      << res << endl;
    return res;
}

void dedup(vector<pair<vector<L>, int>> &res) {
    for (auto &[shape, d] : res) {
        sort(shape.begin(), shape.end(), [](L &a, L &b) {
            return a.id < b.id;
        });
    }
    sort(res.begin(), res.end(), [](auto &a, auto &b) {
        // lexicographic cmp
        rep(i, min(a.first.size(), b.first.size())) {
            if (a.first[i].id != b.first[i].id) return a.first[i].id < b.first[i].id;
        }
        return a.first.size() < b.first.size();
    });
    res.erase(unique(res.begin(), res.end(), [](auto &a, auto &b) {
                  if (a.first.size() != b.first.size()) return false;
                  rep(i, a.first.size()) {
                      if (a.first[i].id != b.first[i].id) return false;
                  }
                  a.second += b.second;
                  return true;
              }),
              res.end());
}

vector<pair<vector<L>, int>> compute(Node expr) {
    static int line_id = 4;

    if (expr.ty == '.') {
        L line = L(P{(double)-expr.a, (double)-expr.b}, (double)-expr.c, line_id++);
        vector<L> lines = {line};
        halfplane_intersect(lines);
        // cerr << "atom: (" << lines << ")" << endl;
        vector<pair<vector<L>, int>> out;
        if (lines.size()) out.push_back({lines, 1});
        return out;
    } else if (expr.ty == '!') {
        auto sub = compute(*expr.l);
        for (auto &[shape, d] : sub) d *= -1;
        vector<L> all = {};
        halfplane_intersect(all);
        sub.push_back({all, 1});
        dedup(sub);
        return sub;
    } else if (expr.ty == '&') {
        auto res = intersect(compute(*expr.l), compute(*expr.r));
        dedup(res);
        return res;
    } else if (expr.ty == '|') {
        vector<pair<vector<L>, int>> l = compute(*expr.l), r = compute(*expr.r), res;
        res = intersect(l, r);
        for (auto &[shape, d] : res) d *= -1;
        res.insert(res.end(), l.begin(), l.end());
        res.insert(res.end(), r.begin(), r.end());
        dedup(res);
        return res;
    } else if (expr.ty == '^') {
        vector<pair<vector<L>, int>> l = compute(*expr.l), r = compute(*expr.r), res;
        res = intersect(l, r);
        for (auto &[shape, d] : res) d *= -2;
        res.insert(res.end(), l.begin(), l.end());
        res.insert(res.end(), r.begin(), r.end());
        dedup(res);
        return res;
    } else throw "?";
}

double area(const vector<P> &p) {
    int n = p.size();
    double a = 0;
    rep(i, n) a += (p[i] - p[0]) % (p[(i + 1) % n] - p[i]);
    return a / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> mn.x >> mx.x >> mn.y >> mx.y;
    Node expr = parse();
    vector<pair<vector<L>, int>> res = compute(expr);
    double ans = 0;
    for (auto [shape, d] : res) {
        assert(!shape.empty());
        halfplane_intersect(shape);
        vector<P> sh = pointify(shape);
        // cerr << "area of polygon ";
        // for (auto p : sh) cerr << p.x << " " << p.y << ", ";
        // cerr << "is " << area(sh) << ", with multiplier " << d << endl;
        ans += area(sh) * d;
    }
    cout << fixed << setprecision(10) << ans << endl;
}
