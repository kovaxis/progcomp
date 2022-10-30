#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Pos {
    int x, y, z, w;
};

Pos id2pos(unsigned int id) {
    int x = id % 64;
    id /= 64;
    int y = id % 64;
    id /= 64;
    int z = id % 64;
    id /= 64;
    int w = id;
    return {x, y, z, w};
}

int pos2id(Pos pos) {
    unsigned int id = 0;
    id |= pos.w;
    id *= 64;
    id |= pos.z;
    id *= 64;
    id |= pos.y;
    id *= 64;
    id |= pos.x;
    return id;
}

int D[3];
char M[64][64][64];
int MX = 64 * 64 * 64 * 3;

template <class OP>
void iter_over_left(OP op) {
    rep(x, D[0]) rep(y, D[1]) rep(z, D[2] + 2) {
        if ((x + y + z) & 1) {
            if (M[x][y][z] == '*') {
                rep(w, 3) op(pos2id({x, y, z, w}));
            } else if (M[x][y][z] == 'o') {
                op(pos2id({x, y, z, 0}));
            }
        }
    }
}

template <class OP>
void iter_over_all(OP op) {
    rep(x, D[0]) rep(y, D[1]) rep(z, D[2] + 2) {
        if (M[x][y][z] == '*') {
            rep(w, 3) op(pos2id({x, y, z, w}));
        } else if (M[x][y][z] == 'o') {
            op(pos2id({x, y, z, 0}));
        }
    }
}

bool is_valid(int x, int y, int z) {
    if (x < 0 || x >= D[0] || y < 0 || y >= D[1] || z < 0 || z >= D[2] + 2) return false;
    if (M[x][y][z] == '#') return false;
    return true;
}

template <class OP>
bool iter_over_adj(int u, OP op) {
#define CHECK(x, y, z, w) \
    if (is_valid(x, y, z) && op(pos2id({x, y, z, w}))) return true;

    Pos pos = id2pos(u);
    char ty = M[pos.x][pos.y][pos.z];
    if (ty == '*') {
        CHECK(pos.x - 1, pos.y, pos.z, pos.w);
        CHECK(pos.x + 1, pos.y, pos.z, pos.w);
        CHECK(pos.x, pos.y - 1, pos.z, pos.w);
        CHECK(pos.x, pos.y + 1, pos.z, pos.w);
        if (pos.z - 1 == 0 && M[pos.x][pos.y][pos.z - 1] == 'o') {
            if (op(pos2id({pos.x, pos.y, pos.z - 1, 0}))) return true;
        } else CHECK(pos.x, pos.y, pos.z - 1, pos.w);
        if (pos.z + 1 == D[2] + 1 && M[pos.x][pos.y][pos.z + 1] == 'o') {
            if (op(pos2id({pos.x, pos.y, pos.z + 1, 0}))) return true;
        } else CHECK(pos.x, pos.y, pos.z + 1, pos.w);
    } else if (ty == 'o') {
        if (pos.z == 0) {
            rep(w, 3) CHECK(pos.x, pos.y, pos.z + 1, w);
        } else if (pos.z == D[2] + 1) {
            rep(w, 3) CHECK(pos.x, pos.y, pos.z - 1, w);
        }
    }
    return false;
#undef CHECK
}

class Hopcroft {
    vector<int> dist;
    int inf = 1e9;

    bool bfs() {
        queue<int> q;
        iter_over_left([&](int u) {
            if (match[u] == nil) dist[u] = 0, q.push(u);
            else dist[u] = inf;
        });
        dist[nil] = inf;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u != nil)
                iter_over_adj(u, [&](int v) {
                    if (dist[match[v]] == inf) {
                        dist[match[v]] = dist[u] + 1;
                        q.push(match[v]);
                    }
                    return false;
                });
        }
        return (dist[nil] != inf);
    }

    bool dfs(int u) {
        if (u == nil)
            return true;
        bool ex = iter_over_adj(u, [&](int v) {
            if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
                match[v] = u, match[u] = v;
                return true;
            }
            return false;
        });
        if (ex) return true;
        dist[u] = inf;
        return false;
    }

public:
    vector<int> match;
    int nil, isPerfect, matchSize = 0, Usize = 0, Gsize = 0;

    // gg is a bidirectional graph, UU has the nodes in the left partition
    Hopcroft() {
        nil = MX;
        match.assign(MX + 1, nil);
        dist.assign(MX + 1, inf);
        iter_over_left([&](int u) { Usize += 1; });
        iter_over_all([&](int u) { Gsize += 1; });
        while (bfs())
            iter_over_left([&](int u) {
                if (match[u] == nil and dfs(u))
                    matchSize++;
            });
        isPerfect = (matchSize == Usize and Gsize == Usize * 2);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> D[1] >> D[0] >> D[2];
        rep(x, D[0]) rep(y, D[1]) M[x][y][0] = '#', M[x][y][D[2] + 1] = '#';
        repx(z, 1, D[2] + 1) rep(y, D[1]) rep(x, D[0]) {
            char c;
            cin >> c;
            if (c == 'o') {
                if (z == 1) {
                    M[x][y][z - 1] = 'o';
                    M[x][y][z] = '*';
                } else if (z == D[2]) {
                    M[x][y][z] = '*';
                    M[x][y][z + 1] = 'o';
                }
            } else {
                M[x][y][z] = c;
            }
        }

        Hopcroft hop = Hopcroft();

        if (false) {
            cerr << "U size = " << hop.Usize << ", G size = " << hop.Gsize << endl;

            char m[64][64][64][3];
            rep(x, 64) rep(y, 64) rep(z, 64) rep(w, 3) m[x][y][z][w] = ' ';
            cerr << "matched " << hop.matchSize << " nodes" << endl;
            rep(id, MX) {
                if (hop.match[id] == MX) continue;
                Pos u = id2pos(id);
                Pos v = id2pos(hop.match[id]);
                char c = '?';
                if (v.x == u.x + 1) c = '>';
                if (v.x == u.x - 1) c = '<';
                if (v.y == u.y + 1) c = 'v';
                if (v.y == u.y - 1) c = '^';
                if (v.z == u.z + 1) c = 'D';
                if (v.z == u.z - 1) c = 'U';
                m[u.x][u.y][u.z][u.w] = c;
                // cerr << "matched node at (" << u.x + 1 << ", " << u.y + 1 << ", " << u.z << " : " << u.w << ") to node at (" << v.x + 1 << ", " << v.y + 1 << ", " << v.z << " : " << v.w << ")" << endl;
            }
            rep(z, D[2] + 2) {
                rep(y, D[1]) {
                    rep(x, D[0]) {
                        rep(w, 3) cerr << m[x][y][z][w];
                        cerr << " ";
                    }
                    cerr << "\n";
                }
                cerr << "\n";
            }
        }

        cout << (hop.isPerfect ? "YES\n" : "NO\n");
    }
}
