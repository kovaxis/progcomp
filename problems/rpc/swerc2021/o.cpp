#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int add(int a, int b) { return ((a + b) % 360 + 360) % 360; }

int N;
vector<vector<bool>> up, rt, seen;

bool dfs(int r, int a) {
    if (r >= up.size()) return true;
    if (seen[r][a]) return false;
    seen[r][a] = true;
    // move up
    if (up[r][a])
        if (dfs(r + 1, a)) return true;
    // move down
    if (r > 0 && up[r - 1][a])
        if (dfs(r - 1, a)) return true;
    // move right
    if (rt[r][a])
        if (dfs(r, add(a, 1))) return true;
    // move left
    if (rt[r][add(a, -1)])
        if (dfs(r, add(a, -1))) return true;
    // reached nothing
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        up.assign(22, vector<bool>(360, true));
        rt.assign(22, vector<bool>(360, true));
        seen.assign(22, vector<bool>(360, false));

        cin >> N;
        rep(i, N) {
            char ty;
            cin >> ty;
            if (ty == 'C') {
                int r, a1, a2;
                cin >> r >> a1 >> a2;
                for (int a = a1; a != a2; a = add(a, 1)) {
                    up[r - 1][a] = false;
                }
            } else if (ty == 'S') {
                int r1, r2, a;
                cin >> r1 >> r2 >> a;
                a = add(a, -1);
                repx(r, r1, r2) { rt[r][a] = false; }
            }
        }

        if (dfs(0, 0))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}