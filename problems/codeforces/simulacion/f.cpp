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

bool col_over(pair<int, int> line, ll up_to, int x, int v) {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //(x,v), up_to (-1 if infinite)
    vector<pair<pair<int, int>, ll>> stack;
    int n;
    cin >> n;
    int cols = 0;
    rep(i, n) {
        int x, v;
        cin >> x >> v;
        if (stack.size() == 0) {
            stack.push_back({x, v});
            continue;
        }
        if (v - stack.back().second >= 0) {
            // Never collide
            stack.clear();
            stack.push_back({{x, v}, -1});
            continue;
        }
        bool last_popped = true;
        ll last_col;
        while (stack.size() > 0) {
            if (col_over(stack.back().first, stack.back().second, x, v)) {
                last_popped = true;
                stack.pop_back();
            } else {
                last_popped = false;
                break;
            }
        }
    }
}
