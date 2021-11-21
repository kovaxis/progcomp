#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int N;
vector<ll> b;
ll bpairs[1024][1024];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    // pos, count
    vector<pair<int, int>> pairstk;
    vector<pair<ll, int>> lvlstk;
    ll lvl = 0;
    ll bpairs = 0;
    rep(i, N) {
        if (i % 2 == 0) {
            // cerr << "opening " << b[i] << " brackets" << endl;
            pairstk.push_back({i, b[i]});
            lvl += b[i];
            // cerr << "  on lvl " << lvl << endl;
        } else {
            // cerr << "closing " << b[i] << " brackets" << endl;
            int c = b[i];
            while (!pairstk.empty() && c > 0) {
                int close = min(pairstk.back().second, c);
                lvl -= close;
                // cerr << "  closing " << close << " brackets with pos "
                //     << pairstk.back().first << ", now at lvl " << lvl <<
                //     endl;
                while (!lvlstk.empty() && lvlstk.back().first > lvl) {
                    if (lvl + close > lvlstk.back().first) {
                        // cerr << "  extra " << lvlstk.back().second
                        //     << " pairs for closing sequential lvl "
                        //     << lvlstk.back().first << endl;
                        bpairs += lvlstk.back().second;
                    }
                    lvlstk.pop_back();
                }
                if (!lvlstk.empty() && lvlstk.back().first == lvl) {
                    // cerr << "  extra " << lvlstk.back().second
                    //     << " pairs for sequential lvl " << lvl << endl;
                    bpairs += lvlstk.back().second;
                    lvlstk.back().second += 1;
                } else {
                    // cerr << "  adding sequential at lvl " << lvl << endl;
                    lvlstk.push_back({lvl, 1});
                }
                bpairs += close;
                pairstk.back().second -= close;
                c -= close;
                if (pairstk.back().second == 0) pairstk.pop_back();
            }
            if (c > 0) lvlstk.clear();
        }
    }
    cout << bpairs << endl;
}
