#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int A = 0, B = 1, L = 2, R = 3;

int N;
vector<int> balls;

int encode(vector<int>& a) {
    int x = 0;
    for (int b : a) {
        x *= 4;
        x += b;
    }
    return x;
}

void fact(int x, vector<double>& p) {
    if (x < 0) p.push_back(0.);
    repx(i, 1, x + 1) p.push_back(i);
}

double getprob(vector<int>& a);

double explore(vector<int>& a, vector<int>& bin, int i, bool found) {
    if (i >= a.size()) {
        if (!found) return 0.;
        return getprob(bin);
    }
    if (a[i] == 0) {
        double res = 0.;
        bin[i] = 1;
        res += explore(a, bin, i + 1, true);
        bin[i] = 2;
        res += explore(a, bin, i + 1, true);
        return res;
    } else {
        bin[i] = a[i];
        return explore(a, bin, i + 1, found);
    }
}

vector<double> dpmem;
double getprob(vector<int>& a) {
    int code = encode(a);
    if (dpmem[code] != -1.) return dpmem[code];

    int left = 0, right = 0, both = 0;
    rep(i, a.size()) if (a[i] == L) left += balls[i];
    else if (a[i] == R) right += balls[i];
    else both += balls[i];

    vector<double> up, dn;
    fact(N, up);
    fact(N - left, dn);

    fact(N, up);
    fact(N - right, dn);

    fact(both, up);
    fact(2 * N, dn);

    double prob = 1.;
    rep(i, min(up.size(), dn.size())) prob *= up[i], prob /= dn[i];
    repx(i, min(up.size(), dn.size()), up.size()) prob *= up[i];
    repx(i, min(up.size(), dn.size()), dn.size()) prob /= dn[i];
    if (!isfinite(prob)) prob = 0.;

    vector<int> bin(a);
    rep(i, a.size()) if (a[i] == B) bin[i] = A;
    rep(i, a.size()) {
        if (a[i] == B) {
            bin[i] = L;
            prob -= getprob(bin);
            bin[i] = R;
            prob -= getprob(bin);
            bin[i] = B;
        }
    }

    if (false) {
        cerr << "probability of ";
        rep(i, a.size()) cerr << "ABLR"[a[i]];
        cerr << " = " << prob << endl;
    }

    return dpmem[code] = prob;
}

double explore2(vector<int>& a, int i, int lt, int rt) {
    if (i >= a.size()) {
        if (lt != rt) return 0.;
        return getprob(a);
    }
    double res = 0.;
    repx(j, 1, 4) {
        a[i] = j;
        res += explore2(a, i + 1, lt + (j == L), rt + (j == R));
    }
    return res;
}

class Solution {
   public:
    double getProbability(vector<int>& balls_param) {
        balls = balls_param;

        N = 0;
        for (int c : balls) N += c;
        N /= 2;

        int dpsize = 1;
        rep(i, balls.size()) dpsize *= 4;
        dpmem.assign(dpsize, -1.);

        vector<int> a(balls.size());
        return explore2(a, 0, 0, 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> balls;
    int x;
    while (cin >> x) balls.push_back(x);
    Solution sol;
    double ans = sol.getProbability(balls);
    cout << fixed << setprecision(8) << setw(8) << ans << endl;
}
