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

struct Node {
    int nxt[27];
    vector<int> words;
};

const pair<pair<int, int>, pair<int, int>> NONEPOS = {{INT32_MAX, INT32_MAX},
                                                      {INT32_MAX, INT32_MAX}};

int W, H;
vector<Node> nodes;
vector<vector<int>> words;
vector<pair<pair<int, int>, pair<int, int>>> wordpos;
int grid[100][100];

int char_at(int x, int y) {
    if (x < 0 || x >= W || y < 0 || y >= H) return 26;
    return grid[x][y];
}

void search(int x, int y, int dx, int dy) {
    int sx = x, sy = y;
    int cur = 0;
    while (true) {
        int nxt = nodes[cur].nxt[char_at(x, y)];
        if (nxt == 0) break;
        for (int word : nodes[nxt].words) {
            wordpos[word] = min(wordpos[word], {{sy, sx}, {y, x}});
        }
        cur = nxt;
        x += dx;
        y += dy;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string tmpword;
    int Q;
    cin >> H >> W >> Q;
    rep(y, H) rep(x, W) {
        char c;
        cin >> c;
        grid[x][y] = c - 'a';
    }
    words.resize(Q);
    wordpos.resize(Q, NONEPOS);
    rep(q, Q) {
        cin >> tmpword;
        for (char c : tmpword) words[q].push_back(c - 'a');
    }

    nodes.push_back({{}, {}});
    rep(q, Q) {
        auto& word = words[q];
        int cur = 0;
        for (int c : word) {
            int& nxt = nodes[cur].nxt[c];
            if (nxt == 0) {
                nxt = nodes.size();
                nodes.push_back({{}, {}});
            }
            cur = nxt;
        }
        nodes[cur].words.push_back(q);
    }

    rep(x, W) rep(y, H) {
        search(x, y, -1, -1);
        search(x, y, -1, 0);
        search(x, y, -1, 1);
        search(x, y, 0, -1);
        search(x, y, 0, 0);
        search(x, y, 0, 1);
        search(x, y, 1, -1);
        search(x, y, 1, 0);
        search(x, y, 1, 1);
    }

    for (auto& pos : wordpos) {
        if (pos == NONEPOS) {
            cout << "-1\n";
        } else {
            cout << pos.first.first << " " << pos.first.second << " "
                 << pos.second.first << " " << pos.second.second << "\n";
        }
    }
}
