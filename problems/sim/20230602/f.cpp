#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
vector<double> dp;
int B, P, Q;
double p;
double q;
double nop;
double noq;

double DP(int n) {
    if (dp[n] != -1) {
        return dp[n];
    }

    double opt1 = 0;
    double opt2 = 0;

    if (n - B >= 0) {
        opt1 = opt1 + p * (DP(n - B) + double(2));
        opt1 = opt1 + nop * (DP(n - B) + double(1));
        opt2 = opt2 + q * (DP(n - B + 1) + double(1));
        opt2 = opt2 + noq * (DP(n - B) + double(1));
    }

    dp[n] = max(opt1, opt2);

    return dp[n];
}

void casodiferente(int A) {

    // cout << "hola" << endl;

    vector<double> X(A + 1, 0);

    for (int i = 1; i <= A; i++) {
        /*double inf = 0;
        double sup = 1000000000;
        while (sup - inf > 0.0000000000001) {
            double guess = (inf + sup) / double(2);
            double compute = q * (guess + double(1)) + noq * (X[i - 1] + double(1));
            if(guess <= compute){

            }
            if(guess >= compute){

            }
        }
        X[i] = max(p * (X[i - 1] + double(2)) + nop * (X[i - 1] + double(1)), (inf + sup) / double(2));
        */
        double opt1 = p * (X[i - 1] + double(2)) + nop * (X[i - 1] + double(1));
        double opt2 = (q + noq * (X[i - 1] + double(1))) / noq;
        // cout << i << ": " << opt1 << " " << opt2 << endl;
        X[i] = max(opt1, opt2);
    }

    cout << X[A] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed << setprecision(15) << setw(15);

    int A;
    cin >> A >> B >> P >> Q;

    p = double(P) / double(100);
    q = double(Q) / double(100);
    nop = double(100 - P) / double(100);
    noq = double(100 - Q) / double(100);

    if (B == 1) {
        casodiferente(A);
        return 0;
    }

    dp.resize(A + 1, -1);
    cout << DP(A) << endl;

    return 0;
}