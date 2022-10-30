#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

const char* PHRASE = "ALLIZZWELL";
const int PHRASELEN = 10;

bool check(char* mat, int w, int h, int x, int y, int idx) {
    if (x < 0 || x >= w || y < 0 || y >= h || mat[y * w + x] != PHRASE[idx]) {
        return false;
    }
    if (idx >= PHRASELEN - 1) {
        return true;
    }
    mat[y * w + x] = ' ';
    for (int suby = -1; suby <= 1; suby++) {
        for (int subx = -1; subx <= 1; subx++) {
            if (subx == 0 && suby == 0) {
                continue;
            }
            if (check(mat, w, h, x + subx, y + suby, idx + 1)) {
                return true;
            }
        }
    }
    mat[y * w + x] = PHRASE[idx];
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    char mat[100 * 100];
    rep(t, ts) {
        int h, w;
        cin >> h;
        cin >> w;
        int i = 0;
        cin.ignore();
        rep(y, h) {
            rep(x, w) {
                char c;
                cin >> c;
                mat[i++] = c;
            }
            cin.ignore();
        }
        bool done = false;
        rep(y, h) {
            rep(x, w) {
                if (check(mat, w, h, x, y, 0)) {
                    done = true;
                    break;
                }
            }
            if (done) {
                break;
            }
        }
        if (done) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
