#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct Str {
    ll delta, req;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    // delta, require, idx
    vector<Str> a(N);
    string s;
    rep(i, N) {
        cin >> s;
        a[i].req = 0;
        for (char c : s) {
            a[i].delta += (c == '(' ? 1 : -1);
            a[i].req = min(a[i].req, a[i].delta);
        }
        a[i].req *= -1;
        a[i].idx = i;
        cerr << "string " << i + 1 << " has delta " << a[i].delta << " and req " << a[i].req << endl;
    }

    vector<Str> pos, neg;
    rep(i, N)(a[i].delta >= 0 ? pos : neg).push_back(a[i]);

    sort(pos.begin(), pos.end(), [&](Str &a, Str &b) { return a.req < b.req; });
    for (Str &s : neg) s.req += s.delta;
    sort(neg.begin(), neg.end(), [&](Str &a, Str &b) { return a.req < b.req; });

    ll accp = 0;
    for (Str &s : pos) {
        if (accp < s.req) {
            cout << "impossible\n";
            return 0;
        }
        accp += s.delta;
    }

    ll accn = 0;
    for (Str &s : neg) {
        if (accn < s.req) {
            cout << "impossible\n";
            return 0;
        }
        accn -= s.delta;
    }

    vector<int> ans;
    for (Str &s : pos) ans.push_back(s.idx);
    invrep(i, neg.size()) ans.push_back(neg[i].idx);

    if (accn == accp) {
        rep(i, N) cout << ans[i] + 1 << "\n";
    } else {
        cout << "impossible\n";
    }
}
