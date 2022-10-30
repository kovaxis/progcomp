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

int n;
vector<string> as;
vector<string> bs;
vector<bool> avail;
string sa;
string sb;

string shortest;

void check() {
    int sa_size = sa.size();
    int sb_size = sb.size();
    if (sa_size == sb_size && sa_size != 0) {
        // Solution
        if (shortest.size() == 0 || sa_size < shortest.size() ||
            (sa_size == shortest.size() && sa < shortest)) {
            shortest = sa;
            return;
        }
    }
    if (shortest.size() != 0 && max(sa_size, sb_size) >= shortest.size()) {
        return;
    }
    int from = min(sa.size(), sb.size());
    rep(i, n) {
        if (avail[i]) {
            sa.append(as[i]);
            sb.append(bs[i]);
            int to = min(sa.size(), sb.size());
            bool notequal = false;
            rep(j, from, to) {
                if (sa[j] != sb[j]) {
                    notequal = true;
                }
            }
            if (!notequal) {
                avail[i] = false;
                check();
                avail[i] = true;
            }
            sa.resize(sa_size);
            sb.resize(sb_size);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int t = 0;
    while (cin >> n) {
        t += 1;
        as.clear();
        bs.clear();
        avail.clear();
        rep(i, n) {
            cin >> s;
            as.push_back(s);
            cin >> s;
            bs.push_back(s);
            avail.push_back(true);
        }
        sa.clear();
        sb.clear();
        shortest.clear();
        check();
        cout << "Case " << t << ": ";
        if (shortest.size() == 0) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << shortest << endl;
        }
    }
}
