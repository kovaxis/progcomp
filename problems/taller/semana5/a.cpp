#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

const int NCOLORS = 4;

int color(int n, vector<int>* nodes, int* colors, int* seen, int idx) {
    seen[idx] = 1;
    bool avail[NCOLORS];
    rep(i, NCOLORS) { avail[i] = true; }
    for (int adj : nodes[idx]) {
        if (colors[adj] != -1) {
            avail[colors[adj]] = false;
        }
    }
    int min_colors = NCOLORS + 1;
    rep(i, NCOLORS) {
        if (!avail[i]) {
            continue;
        }
        int colors_used = i + 1;
        if (colors_used >= min_colors) {
            break;
        }
        colors[idx] = i;
        for (int adj : nodes[idx]) {
            if (colors[adj] == -1) {
                colors_used =
                    max(colors_used, color(n, nodes, colors, seen, adj));
                if (colors_used >= min_colors) {
                    break;
                }
            }
        }
        min_colors = min(min_colors, colors_used);
    }
    colors[idx] = -1;
    return min_colors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> nodes[16];
    int colors[16];
    int seen[16];
    int tests;
    cin >> tests;
    rep(t, tests) {
        int n, m;
        cin >> n;
        cin >> m;
        rep(i, n) {
            nodes[i].clear();
            colors[i] = -1;
            seen[i] = 0;
        }
        rep(i, m) {
            int l, r;
            cin >> l;
            cin >> r;
            nodes[l].push_back(r);
            nodes[r].push_back(l);
        }
        int min_colors = 0;
        rep(i, n) {
            if (seen[i] == 0) {
                min_colors = max(min_colors, color(n, nodes, colors, seen, i));
            }
        }
        if (min_colors > NCOLORS) {
            cout << "many" << endl;
        } else {
            cout << min_colors << endl;
        }
    }
}
