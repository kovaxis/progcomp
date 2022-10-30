#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define invrep(i, n) for (int i = n - 1; i >= 0; i--)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string vit;
    unsigned int min_with[8];
    rep(i, 8) { min_with[i] = 999999; }
    int n;
    cin >> n;
    rep(i, n) {
        unsigned int c;
        cin >> c >> vit;
        int vits = 0;
        for (char ch : vit) {
            if (ch == 'A') {
                vits |= 1;
            } else if (ch == 'B') {
                vits |= 2;
            } else if (ch == 'C') {
                vits |= 4;
            }
        }
        rep(i, 8) {
            int sv = vits & i;
            min_with[sv] = min(min_with[sv], c);
        }
    }
    unsigned int mins[5] = {
        min_with[7], min_with[3] + min_with[4], min_with[5] + min_with[2],
        min_with[6] + min_with[1], min_with[1] + min_with[2] + min_with[4]};
    unsigned int min_c = 999999;
    rep(i, 5) { min_c = min(min_c, mins[i]); }
    if (min_c < 999999) {
        cout << min_c << endl;
    } else {
        cout << "-1" << endl;
    }
}
