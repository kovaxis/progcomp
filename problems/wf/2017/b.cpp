#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

const int AM = (1 << 6) - 1;
const int BM = ((1 << 6) - 1) << 6;
const int CM = ((1 << 9) - 1) << 12;
const int M = (1 << 21) - 1;

struct Turn {
    int has_some[4];
    int has_none[4];
};

int N, A, B, C, Ac, Bc, Cc;
int P[4];
int has_all[4];
int has_none[4];
vector<int> has_some[4];

bool is_consistent(int p) {
    if ((has_all[p] & P[p]) != has_all[p]) return false;
    if ((has_none[p] & P[p]) != 0) return false;
    for (int x : has_some[p])
        if ((x & P[p]) == 0) return false;
    return true;
}

int readc() {
    char c;
    cin >> c;
    return 1 << (c - 'A');
}

char anschar(int x) {
    if (__builtin_popcount(x) == 1) return 'A' + __builtin_ctz(x);
    return '?';
}

void printset(int x) {
    while (x) {
        cerr << char('A' + __builtin_ctz(x));
        x &= ~(1 << __builtin_ctz(x));
    }
}

void choose_p(int avail, int p, int i0, int k) {
    if (p == 4) {
        A |= Ac;
        B |= Bc;
        C |= Cc;
        return;
    }
    int K = (p == 1 ? 5 : 4);
    if (k == K) {
        if (!is_consistent(p)) return;
        return choose_p(avail, p + 1, 0, 0);
    }
    repx(i, i0, 21) if (avail & (1 << i)) {
        P[p] |= 1 << i;
        choose_p(avail & ~(1 << i), p, i + 1, k + 1);
        P[p] &= ~(1 << i);
    }
}

void choose_abc(int avail) {
    rep(a, 6) if (avail & (1 << a)) {
        repx(b, 6, 12) if (avail & (1 << b)) {
            repx(c, 12, 21) if (avail & (1 << c)) {
                Ac = 1 << a, Bc = 1 << b, Cc = 1 << c;
                choose_p(avail & ~(1 << a) & ~(1 << b) & ~(1 << c), 1, 0, 0);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, 5) P[0] |= readc();
    rep(t, N) {
        int sel = 0;
        rep(i, 3) sel |= readc();
        int p = (t + 1) % 4;
        rep(k, 3) {
            char res;
            cin >> res;
            if (res == '-') {
                has_none[p] |= sel;
            } else {
                if (res == '*') {
                    has_some[p].push_back(sel);
                } else {
                    has_all[p] |= 1 << (res - 'A');
                }
                break;
            }
            p += 1;
            p %= 4;
        }
    }

    cerr << "trying" << endl;
    choose_abc(M & ~P[0]);

    cout << anschar(A) << anschar(B) << anschar(C) << endl;
}
