#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

typedef unsigned long long u64;

void check(u64 board, int& soln, int qx, int x) {
    if (x == qx) {
        x++;
    }
    if (x >= 8) {
        soln += 1;
        if (soln >= 10) {
            cout << " " << soln << "    ";
        } else {
            cout << " " << soln << "     ";
        }
        rep(i, 8) {
            int col = (board >> (8 * i)) & 0xff;
            rep(j, 8) {
                if ((col & 1) == 1) {
                    cout << " " << (j + 1);
                    break;
                }
                col >>= 1;
            }
        }
        cout << endl;
        return;
    }
    int used_up = 0;
    rep(j, x) {
        int col = (board >> (8 * j)) & 0xff;
        used_up |= col;
        used_up |= col >> (x - j);
        used_up |= col << (x - j);
    }
    if (qx > x) {
        int col = (board >> (8 * qx)) & 0xff;
        used_up |= col;
        used_up |= col >> (qx - x);
        used_up |= col << (qx - x);
    }
    rep(i, 8) {
        if (((used_up >> i) & 1) == 0) {
            // Avail
            u64 subboard = board | (1ll << (8 * x + i));
            check(subboard, soln, qx, x + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int y, x;
        cin >> y >> x;
        x -= 1;
        y -= 1;
        u64 board = 0;
        board |= 1ll << (8 * x + y);
        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl;
        cout << endl;
        int soln = 0;
        check(board, soln, x, 0);
    }
}
