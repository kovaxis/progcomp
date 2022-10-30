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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    set<string> dedup;
    string input;
    string norm;
    rep(i, n) {
        cin >> input;
        norm.clear();
        bool ignoring = false;
        bool normalizing = true;
        for (char c : input) {
            if (normalizing && c == '+') ignoring = true;
            if (c == '@') {
                normalizing = false;
                ignoring = false;
            }
            if (!ignoring && (!normalizing || (c != '.' && c != '+')))
                norm.push_back(c);
        }
        dedup.insert(norm);
    }
    cout << dedup.size() << endl;
}
