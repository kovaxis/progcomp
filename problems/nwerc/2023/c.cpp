#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr if (0) cerr

int ext_gcd(int a, int b, int& x, int& y) {
    if (b == 0) return x = 1, y = 0, a; // ?
    int d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int multinv(int a, int m) {
    int x, y;
    ext_gcd(a, m, x, y);
    return ((x % m) + m) % m;
}

int N, n, Q, A, B, a;
vector<int> P, prv, nxt, at;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> Q;

    P.resize(N);
    rep(i, N) P[i] = i;
    prv.resize(N), nxt.resize(N), at.resize(N);

    n = N;
    A = 1, a = 1;
    B = 0;

    while(Q--) {
        string qx;
        int x;
        cin >> qx >> x;
        x %= N;

        if (qx == "+") {
            B = (B + x) % N;
            cerr << "added " << x << endl;
        }
        if (qx == "*") {
            int g = __gcd(x, n);
            a = (ll)a * (x / g) % n;
            if (g != 1) {
                cerr << "complex mult by " << x << ", reducing by " << g << endl;
                rep(i, N) prv[i] = ((ll)A * i + B) % N;
                A = (ll)A * x % N;
                B = (ll)B * x % N;
                rep(i, N) nxt[i] = ((ll)A * i + B) % N;

                at.assign(N, -1);
                rep(i, N) if (P[i] == i) {
                    cerr << "  " << i << " moves from " << prv[i] << " to " << nxt[i] << endl;
                    if (at[nxt[i]] == -1 || (nxt[i] - prv[i] + N) % N < (nxt[at[nxt[i]]] - prv[at[nxt[i]]] + N) % N) {
                        at[nxt[i]] = i;
                    }
                }
                rep(i, N) {
                    P[i] = at[nxt[i]];
                    if (P[i] == i) cerr << "  " << i << " ends at itself" << endl;
                }

                n /= g;
            }else{
                A = (ll)A * x % N;
                B = (ll)B * x % N;
                cerr << "simple mult by " << x << endl;
            }
        }
        if (qx == "?") {
            int x2 = (x + N - B) % N;
            if (x2 % (N / n) != 0) {
                cout << "-1\n";
            }else{
                int xn = x2 / (N / n);
                cerr << "querying at pos " << x << " which corresponds to " << xn << endl;
                int in = xn * multinv(a, n) % n;
                cerr << "  formula is " << A << " * i + " << B << " % " << N << ", so i = " << in << endl;
                int i = P[in];
                cerr << "  some guy is " << in << ", representative is " << i << endl;
                cout << (i == 0 ? N : i) << "\n";
            }
        }
    }
}