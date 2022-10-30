#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n;
// wants
string want_list[101];
// has
// idx
unordered_map<string, int> has_map;
bool seen[101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    string name, has, wants;
    rep(i, n) {
        cin >> name >> has >> wants;
        has_map[has] = i;
        want_list[i] = wants;
    }
    int longlen = 0;
    rep(i, n) {
        if (seen[i]) continue;
        int j = i;
        int len = 0;
        while (true) {
            string& wants = want_list[j];
            if (has_map.count(wants) == 0) {
                len = 0;
                break;
            }
            seen[j] = true;
            j = has_map[wants];
            len += 1;
            if (j == i) break;
        }
        longlen = max(longlen, len);
    }
    if (longlen > 1) {
        cout << longlen << endl;
    } else {
        cout << "No trades possible" << endl;
    }
}
