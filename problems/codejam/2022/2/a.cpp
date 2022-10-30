#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<vector<int>> a;
vector<pair<int, int>> pos;
vector<pair<int, int>> scuts;

void add_scut(int x1, int y1, int x2, int y2) {
    int i1 = a[x1][y1], i2 = a[x2][y2];
    if (i1 + 1 == i2) return;
    scuts.push_back({i1 + 1, i2 + 1});
}

void scuts_x(int& x, int& y) {
    while (x < N / 2) add_scut(x, y, x + 1, y), x++;
    while (x > N / 2) add_scut(x, y, x - 1, y), x--;
}

void scuts_y(int& x, int& y) {
    while (y < N / 2) add_scut(x, y, x, y + 1), y++;
    while (y > N / 2) add_scut(x, y, x, y - 1), y--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";

        cin >> N >> K;

        a.assign(N, vector<int>(N, -1));
        int x = -1, y = 0, i = 0;
        // cerr << "visiting" << endl;
        while (x != N / 2 || y != N / 2) {
            while (x + 1 < N && a[x + 1][y] == -1) a[++x][y] = i++;
            while (y + 1 < N && a[x][y + 1] == -1) a[x][++y] = i++;
            while (x - 1 >= 0 && a[x - 1][y] == -1) a[--x][y] = i++;
            while (y - 1 >= 0 && a[x][y - 1] == -1) a[x][--y] = i++;
            // cerr << "at " << x << ", " << y << endl;
        }

        pos.assign(N * N, {0, 0});
        rep(x, N) rep(y, N) pos[a[x][y]] = {x, y};

        i = 0;
        // cerr << "finding" << endl;
        while (i < N * N) {
            if (i + abs(pos[i].first - N / 2) + abs(pos[i].second - N / 2) == K)
                break;
            i += 1;
        }

        if (i >= N * N) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        x = pos[i].first, y = pos[i].second;
        scuts.clear();
        // cerr << "cutting" << endl;
        if (x < N / 2 && a[x + 1][y] > i)
            scuts_x(x, y), scuts_y(x, y);
        else if (x > N / 2 && a[x - 1][y] > i)
            scuts_x(x, y), scuts_y(x, y);
        else if (y < N / 2 && a[x][y + 1] > i)
            scuts_y(x, y), scuts_x(x, y);
        else if (y > N / 2 && a[x][y - 1] > i)
            scuts_y(x, y), scuts_x(x, y);
        else
            scuts_x(x, y), scuts_y(x, y);
        // cerr << "done" << endl;

        cout << scuts.size() << "\n";
        for (auto cut : scuts) cout << cut.first << " " << cut.second << "\n";
    }
}
