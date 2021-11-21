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

vector<int> balls;
vector<int> N;

// up_to, split_point, left_unique, right_unique
// probability
double dpmem[16][64][16][16];

double dp(int n, int s, int l, int r) {
    if (n == 0) return 0.;
    double& cache = dpmem[n][s][l][r];
    if (cache != -1.) return cache;
    double prob = 0.;
    int b = balls[n - 1];
    return cache = prob;
}

/*
2
X X X X X X
a a a b b b

probability of choosing l on the left side and r on the right side:
choose(L, l) * choose(R, r) / choose(L+R, l+r)
L!/(l! * (L-l)!)*R!/(r!(R-r)!)/(L+R)!*(l+r)!*(L+R-l-r)!
*/

double testcase(vector<int>& balls_param) {
    balls = balls_param;
    N.resize(balls.size());
    N[0] = 0;
    rep(i, balls.size()) N[i + 1] = N[i] + balls[i];
    rep(n, balls.size() + 1) rep(s, N[balls.size()]) rep(l, balls.size() + 1)
        rep(r, balls.size() + 1) dpmem[n][s][l][r] = -1.;
    double ans = 0.;
    rep(lr, balls.size() + 1) ans +=
        dp(balls.size(), N[balls.size()] / 2, lr, lr);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> balls;
    int x;
    while (cin >> x) balls.push_back(x);
    cout << fixed << setprecision(8) << setw(8) << testcase(balls) << endl;
}
