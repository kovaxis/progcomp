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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    priority_queue<int> taken;
    ll hp = 0;
    int potions = 0;
    rep(i, n) {
        int a;
        cin >> a;
        a = -a;
        if (hp >= a) {
            hp -= a;
            if (a > 0) {
                taken.push(a);
            }
            potions += 1;
            continue;
        }
        if (taken.empty()) continue;
        if (taken.top() <= a) continue;
        hp += taken.top();
        hp -= a;
        taken.pop();
        taken.push(a);
    }
    cout << potions << endl;
}
