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

typedef long long ll;

vector<string> dict_raw;
vector<pair<int, int>> dict[12];
vector<int> to_word[12];

char letters[12];
int inv_letters[128];

pair<int, int> dp[12][1 << 12];

pair<int, int> search(int bits, int letter) {
    auto& cached = dp[letter][bits];
    if (bits == 0xfff) return {0, 0};
    if (cached.first != -1) return cached;
    int mincost = 999999;
    int minword = -1;
    cached.first = mincost;
    rep(i, dict[letter].size()) {
        auto& w = dict[letter][i];
        int scost = search(bits | w.first, w.second).first + 1;
        if (scost < mincost) {
            mincost = scost;
            minword = i;
        }
    }
    cached = {mincost, minword};
    return {mincost, minword};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    rep(i, n) {
        string s;
        cin >> s;
        if (s.size() < 3) continue;
        dict_raw.push_back(s);
    }

    cin >> letters[0];
    cin >> letters[1];
    cin >> letters[2];
    cin >> letters[3];
    cin >> letters[6];
    cin >> letters[4];
    cin >> letters[7];
    cin >> letters[5];
    cin >> letters[8];
    cin >> letters[9];
    cin >> letters[10];
    cin >> letters[11];
    rep(i, 128) { inv_letters[i] = -1; }
    rep(i, 12) { inv_letters[letters[i]] = i; }

    rep(i, dict_raw.size()) {
        string& w = dict_raw[i];
        int last = -1;
        int first = -1;
        bool ok = true;
        int bits = 0;
        for (char c : w) {
            int s = inv_letters[c];
            if (first == -1) first = s;
            if (s / 3 == last / 3 || s == -1) {
                ok = false;
                break;
            }
            bits |= 1 << s;
            last = s;
        }
        if (ok) {
            dict[first].push_back({bits, last});
            to_word[first].push_back(i);
        }
    }

    rep(i, 12) {
        rep(j, 1 << 12) { dp[i][j].first = -1; }
    }

    int mincost = 999999;
    int letter;
    int word;
    rep(i, 12) {
        auto minnext = search(0, i);
        if (minnext.first < mincost) {
            mincost = minnext.first;
            letter = i;
            word = minnext.second;
        }
    }
    if (mincost == 999999) {
        cout << "impossible\n";
        return 0;
    }
    int bits = 0;
    rep(i, mincost) {
        cout << dict_raw[to_word[letter][word]] << '\n';
        bits |= dict[letter][word].first;
        int nletter = dict[letter][word].second;
        int nword = dp[letter][bits].second;
        letter = nletter;
        word = nword;
    }
}