#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

const int OUTW = 800, OUTH = 4000;

const int CELLW = 35;
const int CELLH = 48;
const int LPAD = 20;

int N, M;
pair<int, int> propranges[8];
string propnames[8], gamenames[8];
int gameprops[8][8];
char out[OUTH][OUTW];

int drawbox(string txt, int y0, int x0) {
    int y1 = y0 + 3, x1 = x0 + txt.size() + 4;
    repx(x, x0, x1) out[y0][x] = '-', out[y1 - 1][x] = '-';
    out[y0][x0] = '*';
    out[y0][x1 - 1] = '*';
    out[y1 - 1][x0] = '*';
    out[y1 - 1][x1 - 1] = '*';
    out[y0 + 1][x0] = '|';
    out[y0 + 1][x1 - 1] = '|';
    rep(i, txt.size()) out[y0 + 1][x0 + 2 + i] = txt[i];
    return x1;
}

int drawgame(int i, int y0, int x0) { return drawbox(gamenames[i], y0, x0); }
int drawcmp(int j, char cmp, int k, int y0, int x0) {
    string txt = propnames[j];
    txt.push_back(' ');
    txt.push_back(cmp);
    txt.push_back(' ');
    txt.push_back('0' + k);
    return drawbox(txt, y0, x0);
}

void drawcell(int j, char cmp, int k, int y0, int &x0) {
    int x1 = drawcmp(j, cmp, k, y0, x0);
    repx(x, x1, x0 + CELLW) out[y0 + 1][x] = '-';
    out[y0 + 2][x1] = 'Y';

    // int xi = (x0 - LPAD) / CELLW + 7;
    int xi = (x0 - LPAD) / CELLW;
    int yband = y0 + 3 + 20 + xi;
    int xconn = LPAD + (xi < 8 ? 7 - xi : xi - 8);
    repx(y, y0 + 3, yband) out[y][x0 + 9] = '|';
    out[y0 + 3][x0 + 8] = 'N';
    out[yband][x0 + 9] = '/';
    repx(x, (xi < 8 ? xi : xconn), x0 + 9) out[yband][x] = '-';
    out[yband][xi < 8 ? xi : xconn] = '/';
    if (xi < 8) {
        int yband2 = y0 + CELLH + 3 + 7 - xi;
        repx(y, yband + 1, yband2) out[y][xi] = '|';
        out[yband2][xi] = '\\';
        repx(x, xi + 1, xconn) out[yband2][x] = '-';
        out[yband2][xconn] = '/';
        repx(y, y0 + CELLH + 3, yband2) out[y][xconn] = '|';
    } else {
        repx(y, yband + 1, y0 + CELLH) out[y][xconn] = '|';
    }

    x0 += CELLW;
}

bool drawrow(int i, int d, int y0) {
    int x0 = LPAD;
    rep(j, M) {
        int L = gameprops[i][j] - d, R = gameprops[i][j] + d;
        if (L == R) {
            drawcell(j, '=', L, y0, x0);
        } else {
            if (L > 1) drawcell(j, '>', L - 1, y0, x0);
            if (R < 5) drawcell(j, '<', R + 1, y0, x0);
        }
    }
    bool continues = (x0 > LPAD);
    drawgame(i, y0, x0);
    return continues;
}

void draw() {
    int y = 0;
    rep(d, 4) {
        rep(i, N) {
            if (!drawrow(i, d, y)) return;
            y += CELLH;
        }
    }
    drawgame(0, y, LPAD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> lines;
    string s;
    while (getline(cin, s)) lines.push_back(s);

    rep(i, lines[0].size()) {
        if (lines[0][i] != ' ') {
            propranges[M].first = i;
            while (i < (int)lines[0].size() && lines[0][i] != ' ') i += 1;
            propranges[M].second = i;
            propnames[M] = lines[0].substr(propranges[M].first, propranges[M].second - propranges[M].first);
            M += 1;
        }
    }
    repx(l, 1, lines.size()) if ((int)lines[l].size() >= propranges[0].first) N += 1;
    rep(i, N) {
        gamenames[i] = lines[i + 1].substr(0, propranges[0].first);
        while (gamenames[i].back() == ' ') gamenames[i].pop_back();
    }
    rep(i, N) rep(j, M) {
        repx(k, propranges[j].first, propranges[j].second) if (k < (int)lines[i + 1].size() && lines[i + 1][k] != ' ') gameprops[i][j] = lines[i + 1][k] - '0';
    }

    rep(y, OUTH) rep(x, OUTW) out[y][x] = ' ';

    draw();

    int ymax = 0, xmax = 0;
    rep(y, OUTH) rep(x, OUTW) if (out[y][x] != ' ') ymax = y + 1, xmax = max(xmax, x + 1);
    rep(y, ymax) {
        rep(x, xmax) cout << out[y][x];
        cout << "\n";
    }
}
