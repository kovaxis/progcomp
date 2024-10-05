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

    L(P o, P d) : o(o), d(d) {}
    L(P ab, double c) : o(ab * -c / ab.magsq()), d(ab.perp()) {}

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
    // cerr << "added halfplanes to obtain (" << H << ")" << endl;

    sort(H.begin(), H.end(), [](L a, L b) {
        return a.d.angcmp(b.d) < 0;
    });
    static deque<L> q;
    q.clear();
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

double area(const vector<P> &p) {
    int n = p.size();
    double a = 0;
    rep(i, n) a += (p[i] - p[0]) % (p[(i + 1) % n] - p[i]);
    return a / 2;
}

void cut_poly(const vector<L> &poly)

    void cut(vector<vector<L>> &polys, Node x) {
    static vector<vector<L>> polys2;
    if (x.ty == '.') {
        L line = L({(double)x.a, (double)x.b}, (double)x.c);
        L antiline = L(line.o, line.d * -1);
        polys2.clear();
        for (const auto &poly : polys) {
            cut_poly(poly, line, polys2);
            vector<L> left = poly;
            left.push_back(line);
            halfplane_intersect(left);
            if (!left.empty()) polys2.push_back(left);

            vector<L> right = poly;
            right.push_back(antiline);
            halfplane_intersect(right);
            if (!right.empty()) polys2.push_back(right);
        }
        swap(polys, polys2);
    } else if (x.ty == '!') {
        cut(polys, *x.l);
    } else {
        cut(polys, *x.l);
        cut(polys, *x.r);
    }
}

bool eval(P pt, Node x) {
    if (x.ty == '.') {
        return pt.x * x.a + pt.y * x.b >= x.c;
    } else if (x.ty == '!') {

    } else {
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> mn.x >> mx.x >> mn.y >> mx.y;
    Node expr = parse();

    vector<vector<L>> polys;
    {
        vector<L> H;
        H.push_back({mn, {mx.x - mn.x, 0}});
        H.push_back({{mx.x, mn.y}, {0, mx.y - mn.y}});
        H.push_back({mx, {mn.x - mx.x, 0}});
        H.push_back({{mn.x, mx.y}, {0, mn.y - mx.y}});
        polys.push_back(H);
    }
    cut(polys, expr);
    double ans = 0;
    for (const auto &poly : polys) {
        vector<P> pts = pointify(poly);
        P p = P{0, 0};
        for (P pt : pts) p = p + pt;
        p = p / pts.size();
        if (eval(p, expr)) ans += area(pts);
    }
    cout << fixed << setprecision(10) << ans << endl;
}
