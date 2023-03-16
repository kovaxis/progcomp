#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Sock {
    ll l, r, any;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    map<string, Sock> socks;
    string s1, s2;
    ll total = 0;
    rep(i, N) {
        int id, side;
        ll n;
        cin >> s1 >> s2 >> n;
        if (socks.count(s1) == 0) socks[s1].l = socks[s1].r = socks[s1].any = 0;
        if (s2 == "left") socks[s1].l = n;
        if (s2 == "right") socks[s1].r = n;
        if (s2 == "any") socks[s1].any = n;
        total += n;
    }
    ll s = 0;
    for (auto &p : socks) {
        Sock sock = p.second;
        s += max(max(sock.l, sock.r), min(1ll, sock.any));
    }
    s += 1;
    if (s <= total) {
        cout << s << endl;
    } else {
        cout << "impossible" << endl;
    }
}