#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string a;
    string b;
    cin >> a >> b;
    int carry = 0;
    int largest = 0;
    rep(i, min(a.size(), b.size())) {
        int dig_a = a[a.size() - i - 1] - '0';
        int dig_b = b[b.size() - i - 1] - '0';
        if (dig_a + dig_b + carry >= 10) {
            carry = 1;
            largest = i + 1;
        } else {
            carry = 0;
        }
    }
    rep(i, a.size() - largest, a.size()) { cout << a[i]; }
    cout << endl;
}
