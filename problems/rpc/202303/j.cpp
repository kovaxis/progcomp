#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        int corneta;
        cin >> corneta >> A[i];
        A[i] += 180;
    }

    bool polo = false;
    vector<bool> longitud(360, false);

    for (int i = 0; i < n; i++) {
        cerr << "hola" << endl;
        int l1 = min(A[i], A[(i + 1) % n]);
        int l2 = max(A[i], A[(i + 1) % n]);
        int d = (l2 - l1 + 360) % 360;
        if (d == 180) {
            polo = true;
        }
        if (d < 180) {
            cerr << "no" << endl;
            for (int j = l1; j < l2; j++) {
                longitud[j] = true;
            }
        } else {
            cerr << "si" << endl;
            for (int j = l2; j != l1; j = (j + 1) % 360) {
                longitud[j] = true;
            }
            cerr << "sis" << endl;
        }
    }

    if (polo == true) {
        cout << "yes\n";
        return 0;
    }

    polo = true;
    for (int i = 0; i < 360; i++) {
        if (longitud[i] == false) {
            polo = false;
        }
    }

    if (polo == true) {
        cout << "yes\n";
    } else {
        cout << "no\n";
    }

    return 0;
}