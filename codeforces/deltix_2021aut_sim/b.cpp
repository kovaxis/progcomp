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

int N, Q, M;
string s;
vector<bool> st;

void check(int i) {
    if (i < 0 || i + 2 >= N) return;
    bool start = s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c';
    if (!st[i] && start) M += 1;
    if (st[i] && !start) M -= 1;
    st[i] = start;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> s;
    N = s.size();
    st.assign(N, false);

    rep(i, N) check(i);

    rep(q, Q) {
        int i;
        char c;
        cin >> i >> c;
        i -= 1;

        s[i] = c;
        check(i - 2);
        check(i - 1);
        check(i);
        cout << M << "\n";
    }
}
