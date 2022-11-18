#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<int> rs = {3000, 2600, 2400, 2300, 2100, 1900, 1600, 1400, 1200};

int nxt(int r) {
    repx(i, 1, rs.size()) {
        if (r >= rs[i]) return rs[i - 1];
    }
    return rs.back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r;
    cin >> r;
    cout << nxt(r) << endl;
}
