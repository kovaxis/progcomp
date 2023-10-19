#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

void sleep(int ms) {
    clock_t until = clock() + CLOCKS_PER_SEC * ms / 1000;
    while (clock() < until) {}
}

int N, M;
int8_t mp[100][100];

void printboard() {
    rep(i, N) {
        rep(j, M) {
            if (mp[i][j] == 1) cout << 'W';
            else if (mp[i][j] == -1) cout << 'B';
            else if (mp[i][j] == 0) cout << '?';
            else assert(false);
        }
        cout << "\n";
    }
}

pair<int, int> count_square(int i, int j) {
    int b = 0, w = 0;
    repx(ii, i, i + 2) repx(jj, j, j + 2) {
        if (mp[ii][jj] == -1) b += 1;
        else if (mp[ii][jj] == 1) w += 1;
    }
    return {b, w};
}

bool update(int i, int j, int v);

bool check(int i, int j) {
    if (i < 0 || j < 0 || i >= N - 1 || j >= M - 1) return true;
    auto [b, w] = count_square(i, j);
    if (b == 4 || w == 4) return false;
    if (b == 3 || w == 3) {
        int maj = (b == 3 ? -1 : 1);
        repx(ii, i, i + 2) repx(jj, j, j + 2) {
            if (mp[ii][jj] != maj) {
                if (!update(ii, jj, -maj)) return false;
            }
        }
    }
    return true;
}

bool update(int i, int j, int v) {
    if (mp[i][j] == v) return true;
    if (mp[i][j] == -v) return false;
    mp[i][j] = v;
    // cout << "set " << i + 1 << " " << j + 1 << " to " << v << endl;
    if (!check(i - 1, j - 1)) return false;
    if (!check(i - 1, j)) return false;
    if (!check(i, j - 1)) return false;
    if (!check(i, j)) return false;
    return true;
}

bool solve() {
    rep(i, N) rep(j, M) if ((i ^ j) & 1) {
        mp[i][j] *= -1;
    }

    // cout << "input:" << endl;
    // printboard();

    // propagate direct consecuences
    rep(i, N - 1) rep(j, M - 1) {
        if (!check(i, j)) return false;
    }

    // set missing blocks arbitrarily
    rep(i, N) rep(j, M) {
        if (mp[i][j] == 0) assert(update(i, j, 1));
    }

    // cout << "output:" << endl;
    // printboard();

    rep(i, N) rep(j, M) if ((i ^ j) & 1) {
        mp[i][j] *= -1;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        rep(i, N) rep(j, M) {
            char c;
            cin >> c;
            if (c == 'B') mp[i][j] = -1;
            else if (c == 'W') mp[i][j] = 1;
            else mp[i][j] = 0;
        }

        if (solve()) {
            cout << "YES\n";
            printboard();
        } else {
            cout << "NO\n";
        }
    }
}
