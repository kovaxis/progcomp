#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    int resp = 0;
    int acc = 0;
    rep(i, n) {
        int a = ((int)s1[i] - (int)'a' + acc) % 26;
        int b = s2[i] - 'a';
        if (a != b) {
            resp += 1;
            acc += b - a + 26;
        }
    }
    cout << resp << endl;
}