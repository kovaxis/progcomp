#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

typedef double T;
const T EPS = 1e-8;

struct P {
    double x, y;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(T r) const { return {x * r, y * r}; }
    P operator/(T r) const { return {x / r, y / r}; }

    P perp() const { return {-y, x}; }
    T operator*(P r) const { return x * r.x + y * r.y; }
    T operator%(P r) const { return perp() * r; }

    T magsq() const { return x * x + y * y; }
    T mag() const { return sqrt(magsq()); }
    P unit() const { return *this / mag(); }
};

const double ALPHA = 9.80665 / 2;

int W, H, Sx, Sy;
double L, V;
vector<vector<int>> D;
vector<vector<double>> Z_;
bool swapz;

double &Z(int x, int y) {
    if (swapz) swap(x, y);
    return Z_[x][y];
}

bool crashblock(P start, P end, P crash, double crash_z, int block_x_idx, int block_y_idx, double z0) {
    if (crash.y < block_y_idx * L - EPS) return false;
    if (crash.y > (block_y_idx + 1) * L + EPS) return false;
    double wall_z = Z(block_x_idx, block_y_idx) - z0;
    cerr << "      checking against block with relative Z = " << wall_z << endl;

    return crash_z <= wall_z + EPS;
}

bool crashwall(P start, P end, int wall_x_idx, double vx, double vy, double z0) {
    // check collision from start to end against walls with x = wall_x
    P delta = end - start;
    assert(delta.x != 0);
    double wall_x = wall_x_idx * L;
    double delta_wall_x = wall_x - start.x;
    assert(delta_wall_x != 0);
    double delta_y = delta_wall_x / delta.x * delta.y;
    double crash_y = start.y + delta_y;

    int wall_y_idx = floor(crash_y / L + 0.5);

    P crash = {wall_x, crash_y};
    double t = (crash - start).mag() / vx;
    double crash_z = -ALPHA * t * t + vy * t;

    cerr << "      crash is at " << wall_x << " " << crash_y << " with relative z = " << crash_z << endl;
    if (crashblock(start, end, crash, crash_z, wall_x_idx, wall_y_idx, z0)) return true;
    if (crashblock(start, end, crash, crash_z, wall_x_idx, wall_y_idx - 1, z0)) return true;
    if (crashblock(start, end, crash, crash_z, wall_x_idx - 1, wall_y_idx, z0)) return true;
    if (crashblock(start, end, crash, crash_z, wall_x_idx - 1, wall_y_idx - 1, z0)) return true;
    return false;
}

bool canjump(int x1, int y1, int x2, int y2, P start, P end, double u, double tx, double ty) {
    if (u <= EPS) {
        cerr << "  nonpositive u, cannot jump" << endl;
        return false;
    }
    double t = sqrt(u);
    double vx = tx / t;
    double vy = sqrt(V * V - vx * vx);
    cerr << "  trying jump with vx = " << vx << ", vy = " << vy << endl;

    // check solution
    double real_ty = t * (vy - ALPHA * t);
    if (abs(real_ty - ty) > EPS) {
        cerr << "  final z is " << real_ty << " as opposed to target " << ty << ", cannot jump" << endl;
        return false;
    }
    cerr << "  final z is " << real_ty << ", equal to target " << ty << endl;

    // check wall collisions
    double z0 = Z(x1, y1);
    if (x1 != x2) {
        // collisions against vertical walls
        repx(x, min(x1, x2) + 1, max(x1, x2) + 1) {
            cerr << "    checking against wall at x = " << x << endl;
            if (crashwall(start, end, x, vx, vy, z0)) return false;
        }
    }
    if (y1 != y2) {
        // collisions against horizontal walls
        swap(start.x, start.y);
        swap(end.x, end.y);
        swapz = true;
        repx(y, min(y1, y2) + 1, max(y1, y2) + 1) {
            cerr << "    checking against wall at y = " << y << endl;
            if (crashwall(start, end, y, vx, vy, z0)) {
                swapz = false;
                return false;
            }
        }
        swapz = false;
    }
    return true;
}

bool canjump(int x1, int y1, int x2, int y2) {
    cerr << "checking jump from " << x1 << " " << y1 << " to " << x2 << " " << y2 << endl;
    P start = P{(x1 + 0.5) * L, (y1 + 0.5) * L};
    P end = P{(x2 + 0.5) * L, (y2 + 0.5) * L};

    // figure out jump dynamics
    double tx = (end - start).mag();
    double ty = Z(x2, y2) - Z(x1, y1);
    double a = ALPHA * ALPHA;
    double b = 2 * ALPHA * ty - V * V;
    double c = ty * ty + tx * tx;

    double disc = b * b - 4 * a * c;
    if (disc < -EPS) {
        // not enough speed to make the jump
        cerr << "  not enough speed to perform jump" << endl;
        return false;
    }
    disc = max(disc, 0.0);

    double u1 = (-b + sqrt(disc)) / (2 * a);
    double u2 = (-b - sqrt(disc)) / (2 * a);
    if (canjump(x1, y1, x2, y2, start, end, u1, tx, ty)) return true;
    if (canjump(x1, y1, x2, y2, start, end, u2, tx, ty)) return true;
    cerr << "  cannot perform jump" << endl;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> W >> H >> L >> V >> Sx >> Sy;
    Sx--, Sy--;
    Z_.assign(W, vector<double>(H));
    rep(y, H) rep(x, W) cin >> Z(x, y);

    vector<pair<int, int>> Q;
    int q = 0;
    D.assign(W, vector<int>(H, -1));
    D[Sx][Sy] = 0;
    Q.push_back({Sx, Sy});
    while (q < (int)Q.size()) {
        auto [x1, y1] = Q[q++];
        rep(x2, W) rep(y2, H) if (x2 != x1 || y2 != y1) {
            if (D[x2][y2] == -1 && canjump(x1, y1, x2, y2)) {
                D[x2][y2] = D[x1][y1] + 1;
                Q.push_back({x2, y2});
            }
        }
    }

    rep(y, H) {
        rep(x, W) {
            if (D[x][y] == -1) cout << "X ";
            else cout << D[x][y] << " ";
        }
        cout << "\n";
    }
}