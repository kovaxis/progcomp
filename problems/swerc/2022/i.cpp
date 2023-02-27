#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

struct P {
    ll x, y;

    P operator+(P b) const { return {x + b.x, y + b.y}; }
    P operator-(P b) const { return {x - b.x, y - b.y}; }
};

int N;
vector<P> p;
vector<bool> taken;

int add(int i, int j) {
    return ((i + j) % N + N) % N;
}

ll cross(P a, P b) {
    return a.x * b.y - a.y * b.x;
}

ll area(int i, int j, int k) {
    return abs(cross(p[j] - p[i], p[k] - p[i]));
}

int find_smallest() {
    ll mn = 1e18;
    int argmn = 0;
    rep(i, N) {
        if (taken[i]) continue;
        int j = add(i, -1);
        while (taken[j]) j = add(j, -1);
        int k = add(i, 1);
        while (taken[k]) k = add(k, 1);
        ll a = area(i, j, k);
        if (a < mn) mn = a, argmn = i;
    }
    return argmn;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    p.resize(N);
    rep(i, N) cin >> p[i].x >> p[i].y;

    taken.resize(N);

    if (N % 2 == 0) {
        cout << "Alberto" << endl;
    } else {
        cout << "Beatrice" << endl;
    }
    rep(t, N - 2) {
        if (t % 2 == N % 2) {
            int i = find_smallest();
            cout << i + 1 << endl;
            taken[i] = true;
        } else {
            int i;
            cin >> i;
            taken[i - 1] = true;
        }
    }
}
