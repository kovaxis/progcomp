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

// deadline, needless
pair<int, bool> people[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> m >> n;
    rep(i, n) {
        char paper;
        cin >> people[i].first >> paper;
        people[i].second = paper == 'n';
    }
    sort(people, people + n);

    ll last = 0;
    ll slot_p = 0;
    ll slot_np = 0;
    rep(i, n) {
        int deadline = people[i].first;
        bool needless = people[i].second;
        slot_p += deadline - last;
        slot_np += (deadline - last) * m;
        last = (ll)deadline;
        if (needless) {
            slot_np -= 1;
            slot_p = min(slot_p, slot_np);
        } else {
            slot_np -= 1;
            slot_p -= 1;
        }
        if (slot_np < 0 || slot_p < 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
}
