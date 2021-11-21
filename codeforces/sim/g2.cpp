#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (int)(n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

string s;
int k;

int nxt[1000001];
int prv[1000001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> k;
    rep(i, s.size() + 1) {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
    int last = 0;
    priority_queue<int> falls;
    invrep(i, s.size() - k, s.size()) {
        if (s[i] > last) falls.push(-i);
        last = s[i];
    }
    invrep(i, s.size() - k) {
        if (s[i] <= last) {
            int rem = -falls.top();
            falls.pop();
            int remprev = prv[rem];
            int remnext = nxt[rem];
            if (remnext == s.size() || s[remnext] < s[remprev]) {
                falls.push(-remprev);
            }
            nxt[remprev] = remnext;
            prv[remnext] = remprev;
            s[rem] = 0;
            last = s[i];
        } else {
            int iprev = prv[i];
            int inext = nxt[i];
            nxt[iprev] = inext;
            prv[inext] = iprev;
            s[i] = 0;
        }
    }
    for (char c : s) {
        if (c != 0) cout << c;
    }
    cout << endl;
}
