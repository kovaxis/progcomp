#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

vector<int> A, B;
ll C, D;
vector<int> bpos[10];

vector<int> readnum() {
    string s;
    cin >> s;
    vector<int> x;
    for(char c : s) x.push_back(c - '0');
    return x;
}

vector<int> tostr(__int128 x) {
    if (x == 0) return {0};
    vector<int> s;
    while(x) {
        s.push_back(x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

ll buildnum(const vector<int>& num, int m) {
    ll x = 0;
    int first = -1, last = -1;
    rep(i, num.size()) if ((m >> i) & 1) {
        if (first == -1) first = i;
        last = i;
        x = x * 10 + num[i];
    }
    if (first == -1) return 0; // ?
    if (first != last && num[first] == 0) return 0;
    return x;
}

void cancel(int ma) {
    int bnxt[10];
    rep(d, 10) bnxt[d] = 0;

    ll a = buildnum(A, ~ma);
    if (a == 0) return;

    __int128 ad = (__int128)a * D;
    if (ad % C != 0) return;
    __int128 b = ad / C;
    vector<int> bwant = tostr(b);
    if (bwant.size() > B.size()) return;

    int remcnt[10];
    rep(d, 10) remcnt[d] = 0;
    rep(i, A.size()) if ((ma >> i) & 1) remcnt[A[i]] += 1;

    int bwantnxt = 0;
    rep(j, B.size()) {
        if (bwantnxt >= (int)bwant.size() || B[j] != bwant[bwantnxt]) {
            remcnt[B[j]] -= 1;
        } else {
            bwantnxt += 1;
        }
    }
    if (bwantnxt != bwant.size()) return;
    rep(d, 10) if (remcnt[d] != 0) return;

    cout << "possible" << endl;
    cout << a << " " << (ll)b << endl;
    exit(0);
}

void solve() {
    rep(m, 1 << A.size()) cancel(m);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    A = readnum(), B = readnum();
    cin >> C >> D;
    
    rep(i, B.size()) bpos[B[i]].push_back(i);

    solve();

    cout << "impossible" << endl;
}
