#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int main() {
    int n;
    cin >> n;

    int waiting = 0;
    int dir;
    int T;
    cin >> T >> dir;
    int stop = T + 10;
    for (int i = 1; i < n; i++) {
        int t, d;
        cin >> t >> d;
        if (t < stop) {
            if (d == dir)
                stop = t + 10;
            else
                waiting += 1;
        } else {
            if (waiting > 0) {
                dir = !dir;
                waiting = 0;
                stop = stop + 10;
            }

            if (t < stop) {
                if (d == dir)
                    stop = t + 10;
                else
                    waiting += 1;
            } else {
                dir = d;
                stop = t + 10;
            }
        }
    }
    if (waiting > 0) stop += 10;
    cout << stop << endl;

    return 0;
}
