#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

bool is_king_row(int player, int i) {
    if (player < 0) return i < 4;
    else return i >= 28;
}

struct Piece {
    int color = 0, needs_king = 201, becomes_king = 200;

    void set_color(int c) {
        assert(color == 0 || color == c);
        color = c;
    }

    void require_king(int k) {
        needs_king = min(needs_king, k);
    }

    void arrive_at(int k, int i) {
        assert(color != 0);
        if (is_king_row(color, i)) becomes_king = min(becomes_king, k);
    }
};

Piece A[32];
int B[32];
char out[8][17];

pair<int, int> num2pos(int x) {
    int i = x / 4;
    int j = (x % 4) * 2;
    if (i % 2 == 0) j += 1;
    return {i, j};
}

bool is_backwards(int d, int player) {
    d *= player;
    return d < 0;
}

int middle_of(int i1, int i2) {
    return (i1 + i2 + 1 - i1 / 4 % 2) / 2;
}

char piece_char(int color, bool king) {
    if (color == 0) return '.';
    char c = (color < 0 ? 'w' : 'b');
    if (king) c += 'W' - 'w';
    return c;
}

void render_at(const Piece &piece, int k, int base_x, int i) {
    assert(piece.color != 0);
    bool king = k >= piece.becomes_king || piece.needs_king < piece.becomes_king;
    char c = piece_char(piece.color, king);

    int y = i / 4;
    int x = base_x + (i % 4) * 2 + 1 - y % 2;
    out[y][x] = c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    char start_p;
    int N;
    cin >> start_p >> N;
    string empty;
    getline(cin, empty);

    rep(i, 32) B[i] = i;

    int cur = start_p == 'W' ? -1 : 1;
    rep(k, N) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        char sep;
        vector<int> a;
        while (true) {
            int x;
            if (ss >> x) {
                a.push_back(x - 1);
                char c;
                if (ss >> c) sep = c;
            } else {
                break;
            }
        }

        if (sep == 'x') {
            // jump
            int from = a[0];
            int to = a.back();
            Piece &piece = A[B[from]];
            bool backwards = false;
            rep(j, (int)a.size() - 1) if (is_backwards(a[j + 1] - a[j], cur)) backwards = true;
            if (backwards) piece.require_king(k);
            piece.set_color(cur);
            piece.arrive_at(k + 1, to);
            B[to] = B[from];
            rep(j, (int)a.size() - 1) B[a[j]] = -1;
            rep(j, (int)a.size() - 1) {
                int m = middle_of(a[j], a[j + 1]);
                A[B[m]].set_color(-cur);
                B[m] = -1;
            }
        } else {
            // move
            int from = a[0];
            int to = a[1];
            Piece &piece = A[B[from]];
            if (is_backwards(to - from, cur)) piece.require_king(k);
            piece.set_color(cur);
            piece.arrive_at(k + 1, to);
            B[to] = B[from];
            B[from] = -1;
        }

        cur = -cur;
    }

    rep(i, 32) if (A[i].color != 0) A[i].arrive_at(0, i);

    rep(i, 8) rep(j, 17) out[i][j] = (j == 8 ? ' ' : ((i + j - (j > 8)) % 2 ? '.' : '-'));
    rep(i, 32) {
        if (A[i].color == 0) continue;
        render_at(A[i], 0, 0, i);
    }
    rep(i, 32) {
        if (B[i] == -1 || A[B[i]].color == 0) continue;
        render_at(A[B[i]], N, 9, i);
    }

    rep(i, 8) {
        rep(j, 17) cout << out[i][j];
        cout << endl;
    }
}
