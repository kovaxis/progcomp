#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

void rot(char &c) {
    c = 'a' + (char)(((int)(c - 'a') + 1) % 26);
}

string step(string s) {
    string o;
    int n = s.size();
    o.append(s.begin(), s.begin() + n / 2);
    o.append(s.begin(), s.end());
    o.append(s.begin() + n / 2, s.end());
    repx(i, (int)o.size() - n / 2, (int)o.size()) {
        rot(o[i]);
    }
    return o;
}

int N, M;
string A;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> A;
    int k = 1;
    rep(i, 100) k = k * 10 % 26;
    while ((int)A.size() < 2 * M) A = step(A), k = (k + 26 - 1) % 26;
    string B(A.end() - M, A.end());
    rep(s, k) for (char &c : B) rot(c);
    cout << B << endl;
}