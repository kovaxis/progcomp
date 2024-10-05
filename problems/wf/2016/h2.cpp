#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= int(a); i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef double db;

const db EPS = 1e-11;

struct P {
    db x, y;

    P operator+(P r) const { return {x+r.x, y+r.y}; }
    P operator-(P r) const { return {x-r.x, y-r.y}; }
    P operator*(db r) const { return {x*r, y*r}; }

    P perp() const { return {-y, x}; }
    db operator*(P r) const { return x*r.x + y*r.y; }
    
    db mag2() const { return x*x + y*y; }
    db mag() const { return sqrt(mag2()); }
    P unit() const { return *this * (1.0 / mag()); }

    db angle() const { return atan2(y, x); }
};

int N, M;
vector<P> A0, A1, A, B0, B, Ap, Bp;
db answer;

void alignpoly(vector<P>& S, vector<P>& T, P o, P d) {
    T.resize(S.size());
    d.y = -d.y;
    rep(i, S.size()) {
        P u = S[i] - o;
        T[i] = d * u.x + d.perp() * u.y;
    }
}

void shiftpoly(vector<P>& S, vector<P>& T, db x) {
    T.resize(S.size());
    rep(i, S.size()) {
        T[i] = S[i];
        T[i].x += x;
    }
}

static vector<pair<pair<P, P>, string>> svglines;
P svgdelta;

static void svgprint(ostream& s) {
    P svgmn = {0, 0};
    P svgmx = {0, 0};
    for(auto& [u, c] : svglines) {
        auto [a, b] = u;
        svgmn.x = min(svgmn.x, min(a.x, b.x));
        svgmn.y = min(svgmn.y, min(a.y, b.y));
        svgmx.x = max(svgmx.x, max(a.x, b.x));
        svgmx.y = max(svgmx.y, max(a.y, b.y));
    }

    s << fixed << setprecision(6);
    s << "<svg width=\""<<ceil(svgmx.x-svgmn.x)<<"\" height=\""<<ceil(svgmx.y-svgmn.y)<<"\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    for(auto [x, color] : svglines) {
        auto [a, b] = x;
        a = a - svgmn;
        b = b - svgmn;
        s << "  <line x1=\"" << a.x << "\" y1=\""<<a.y<<"\" x2=\""<<b.x<<"\" y2=\""<<b.y<<"\" style=\"stroke:"<<color<<"\" />" << endl;
    }
    s << "</svg>" << endl;
}

void svgline(P a, P b, string color) {
    // svglines.push_back({{a+svgdelta, b+svgdelta}, color});
}

void svgpoly(const vector<P>& A, string color) {
    rep(i, A.size()) {
        int j = (i+1) % A.size();
        P a = A[i], b = A[j];
        svgline(a, b, color);
    }
}

void perturbpoly(const vector<P>& A, vector<P>& Ap) {
    Ap.resize(A.size());
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    rep(j, A.size()) {
        int i = (j + A.size() - 1) % A.size();
        int k = (j + 1) % A.size();
        P lo = A[i] - A[j];
        P hi = A[k] - A[j];
        if (lo.perp() * hi > 0) {
            lo = lo * -1;
            hi = hi * -1;
        }
        lo = lo.unit(), hi = hi.unit();
        P d = lo + (hi - lo) * uniform_real_distribution<db>()(rng);
        d = d.unit() * 1e-7;
        Ap[j] = A[j] + d;
    }
}

int in_poly(const vector<P> &p, P q) {
    int w = 0;
    rep(i, p.size()) {
        P a = p[i], b = p[(i + 1) % p.size()];
        double k = (b - a).perp() * (q - a);
        double u = a.y - q.y, v = b.y - q.y;
        if (k > 0 && u < -0 && v >= -0) w++;
        if (k < -0 && v < -0 && u >= -0) w--;
        if (abs(k) <= 0 && (q - a) * (q - b) <= 0) return 0;
    }
    return w ? 1 : -1;
}

bool check() {
    perturbpoly(A, Ap);
    perturbpoly(B, Bp);

    svgpoly(A, "blue");
    svgpoly(Ap, "gray");
    svgpoly(B, "green");
    svgpoly(Bp, "gray");

    db len = 0;
    rep(i0, N) rep(j0, M) {
        int i1 = (i0+1)%N, j1 = (j0+1)%M;

        P ao = A[i0], ad = A[i1] - A[i0];
        P bo = B[j0], bd = B[j1] - B[j0];

        db z = ad.perp() * bd;
        if (abs(z) <= EPS) {
            // parallel
            if (abs(ad.perp() * (bo - ao)) > EPS) continue;
            if (bd * ad < 0) bo = bo + bd, bd = bd * -1;
            P s = ao * ad < bo * ad ? bo : ao;
            P e = (ao + ad) * ad < (bo + bd) * ad ? ao + ad : bo + bd;
            if (s * ad > e * ad) continue;
            svgline(s, e, "red");
            len += (e - s) * ad.unit();
        }
    }
    rep(i, N) if (abs(in_poly(Bp, Ap[i])) <= EPS) throw "?";
    rep(j, M) if (abs(in_poly(Ap, Bp[j])) <= EPS) throw "?";
    rep(i, N) if (in_poly(Bp, Ap[i]) > 0) return false;
    rep(j, M) if (in_poly(Ap, Bp[j]) > 0) return false;
    rep(i0, N) rep(j0, M) {
        int i1 = (i0+1)%N, j1 = (j0+1)%M;

        P ao = Ap[i0], ad = Ap[i1] - Ap[i0];
        P bo = Bp[j0], bd = Bp[j1] - Bp[j0];

        db z = ad.perp() * bd;
        if (abs(z) > EPS) {
            db s = (bo - ao).perp() * bd, t = (bo - ao).perp() * ad;
            if (z < 0) s = -s, t = -t, z = -z;
            if (s > EPS && s < z - EPS && t > EPS && t < z - EPS) return false;
        }
    }
    answer = max(answer, len);

    return true;
}

void readpoly(int& N, vector<P>& A) {
    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;
    reverse(A.begin(), A.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    readpoly(N, A0);
    readpoly(M, B0);

    rep(i0, N) {
        int i1 = (i0+1)%N;
        alignpoly(A0, A1, A0[i0], (A0[i1] - A0[i0]).unit());
        rep(j0, M) {
            int j1 = (j0+1)%M;
            alignpoly(B0, B, B0[j0], (B0[j0] - B0[j1]).unit());
            rep(k0, N) {
                int k1 = (k0+1)%N;
                P d = A1[k1] - A1[k0];
                if (abs(d.y) <= EPS) continue;
                db x = A1[k0].x - A1[k0].y * d.x / d.y;
                shiftpoly(A1, A, -x);
                if (!check()) {
                    svgline({-10, -10}, {10, 10}, "red");
                    svgline({-10, 10}, {10, -10}, "red");
                }
                svgdelta = svgdelta + P{0, 100};
                shiftpoly(A1, A, -x+B[j1].x);
                if (!check()) {
                    svgline({-10, -10}, {10, 10}, "red");
                    svgline({-10, 10}, {10, -10}, "red");
                }
                svgdelta = svgdelta + P{0, 100};
            }
        }
    }

    cout << fixed << setprecision(12) << answer << endl;

    // svgprint(cout);
}
