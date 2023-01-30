#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e9;

int N;
vector<int> a, nxt, prv;
set<int> delqueue;
vector<bool> rem;
vector<set<int>> deleted;

bool should_del(int i) {
    if (prv[i] >= 0 && a[i] < a[prv[i]]) return true;
    if (nxt[i] < N && a[i] < a[nxt[i]]) return true;
    return false;
}

void remove(int i) {
    if (rem[i]) return;
    if (prv[i] >= 0) nxt[prv[i]] = nxt[i];
    if (nxt[i] < N) prv[nxt[i]] = prv[i];
    rem[i] = true;
}

void check_remove(int i) {
    if (i < 0 || i >= N || rem[i]) return;
    if (should_del(i)) delqueue.insert(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];

    nxt.resize(N), prv.resize(N);
    rem.assign(N, false);
    rep(i, N) nxt[i] = i + 1, prv[i] = i - 1;
    rep(i, N) check_remove(i);

    while (!delqueue.empty()) {
        set<int> old_del;
        swap(delqueue, old_del);
        deleted.push_back(old_del);

        for (int i : old_del) remove(i);
        for (int i : old_del) check_remove(prv[i]), check_remove(nxt[i]);
    }

    cout << deleted.size() << "\n";
    for (auto &delq : deleted) {
        bool first = true;
        for (int i : delq) {
            if (first) first = false;
            else cout << " ";
            cout << a[i];
        }
        cout << "\n";
    }
    bool first = true;
    rep(i, N) {
        if (rem[i]) continue;
        if (first) first = false;
        else cout << " ";
        cout << a[i];
    }
    cout << "\n";
}
