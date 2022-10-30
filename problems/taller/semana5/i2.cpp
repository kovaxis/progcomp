#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int16_t hsum[8];
uint8_t hrem[8];
int16_t vsum[8];
uint8_t vrem[8];
pair<int8_t, int8_t> pos[64];
uint64_t unknown;

uint64_t shift(uint64_t b, int x, int y) {
    if (y < 0) {
        b = b >> (y * -8);
    } else {
        b = b << (y * 8);
    }
    if (x < 0) {
        uint64_t mask = 0x8080808080808080ull;
        rep(i, 7 + x) { mask = (mask >> 1) | mask; }
        return (b & mask) >> (-x);
    } else {
        uint64_t mask = 0x0101010101010101ull;
        rep(i, 7 - x) { mask = (mask << 1) | mask; }
        return (b & mask) << x;
    }
}
uint64_t step_board(uint64_t b) {
    return shift(b, 1, 2) | shift(b, 1, -2) | shift(b, -1, 2) |
           shift(b, -1, -2) | shift(b, 2, 1) | shift(b, 2, -1) |
           shift(b, -2, 1) | shift(b, -2, -1);
}
uint64_t piece_at(int x, int y) { return ((uint64_t)1) << (x + y * 8); }

// board is -1 at (x, y)
bool search(int num, int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return false;
    if ((unknown & piece_at(x, y)) == 0) {
        if (pos[num - 1].first == -1) {
            return false;
        } else {
            if (pos[num - 1].first == x && pos[num - 1].second == y) {
                num += 1;
                while (num <= 64 && pos[num - 1].first != -1) {
                    num += 1;
                }
            } else {
                return false;
            }
        }
    }

    bool ok = true;
    unknown &= ~piece_at(x, y);
    pos[num - 1] = {x, y};
    vsum[x] += num;
    vrem[x] -= 1;
    hsum[y] += num;
    hrem[y] -= 1;
    rep(i, 8) {
        if (vsum[i] + vrem[i] * (vrem[i] + num) > 260 ||
            hsum[i] + hrem[i] * (hrem[i] + num) > 260) {
            ok = false;
            break;
        }
    }
    if (num >= 64) {
        bool exact = true;
        rep(i, 8) {
            if (vsum[i] != 260 || hsum[i] != 260) {
                exact = false;
                break;
            }
        }
        if (exact) return true;
    }
    if (ok) {
        int nknown = num;
        uint64_t canreach = piece_at(x, y);
        while (nknown <= 64 && pos[nknown - 1].first == -1) {
            canreach = unknown & step_board(canreach);
            nknown += 1;
        }
        if (nknown > 64 || (canreach & piece_at(pos[nknown - 1].first,
                                                pos[nknown - 1].second)) != 0) {
            bool done =
                search(nnum, nx + 2, ny - 1) || search(nnum, nx + 2, ny + 1) ||
                search(nnum, nx - 2, ny - 1) || search(nnum, nx - 2, ny + 1) ||
                search(nnum, nx + 1, ny - 2) || search(nnum, nx + 1, ny + 2) ||
                search(nnum, nx - 1, ny - 2) || search(nnum, nx - 1, ny + 2);
            if (done) {
                return true;
            }
        }
    }
    unknown |= piece_at(x, y);
    pos[num - 1].first = -1;
    vsum[x] -= num;
    vrem[x] += 1;
    hsum[y] -= num;
    hrem[y] += 1;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(i, 64) { pos[i] = {-1, -1}; }
    rep(i, 8) {
        vrem[i] = 8;
        hrem[i] = 8;
        vsum[i] = 0;
        hsum[i] = 0;
    }
    unknown = ~0ull;
    rep(y, 8) {
        rep(x, 8) {
            int v;
            cin >> v;
            if (v >= 1) {
                vsum[x] += v;
                vrem[x] -= 1;
                hsum[y] += v;
                hrem[y] -= 1;
                pos[v - 1] = {x, y};
                unknown &= ~piece_at(x, y);
            }
        }
    }

    search(1, pos[0].first, pos[0].second);
    uint8_t board[8][8];
    rep(i, 64) { board[pos[i].first][pos[i].second] = i + 1; }
    rep(y, 8) {
        rep(x, 8) {
            if (x != 0) cout << " ";
            cout << (int)board[x][y];
        }
        cout << '\n';
    }
}
