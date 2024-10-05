#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<int> fact, reduced;
vector<pair<int, int>> facts;

void factorize(int x, vector<pair<int, int>> &f) {
    f.clear();
    while (x != 1) {
        int ff = fact[x];
        x = reduced[x];
        if (f.size() && f.back().first == ff) f.back().second += 1;
        else f.push_back({ff, 1});
    }
}

template <class OP>
void divisors(int upper, OP op) {
    static vector<int> f;
    f.assign(facts.size(), 0);
    int y = 1;
    while (true) {
        op(y);

        int i;
        for (i = 0; i < f.size(); i++) {
            y *= facts[i].first;
            f[i] += 1;
            if (f[i] > facts[i].second || y > upper) {
                int m = 1;
                rep(j, f[i]) m *= facts[i].first;
                y /= m;
                f[i] = 0;
            } else {
                break;
            }
        }
        if (i == f.size()) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int fmax = 3e6;
    fact.resize(fmax, 1), reduced.resize(fmax, 1);
    repx(i, 2, fmax) if (fact[i] == 1) {
        for (int k = 1; i * k < fmax; k++)
            if (fact[i * k] == 1) {
                fact[i * k] = i;
                reduced[i * k] = k;
            }
    }

    int TC;
    cin >> TC;
    while (TC--) {
        int N, M;
        cin >> N >> M;
        int ans = 0;
        for (int b = 1; b <= M; b++) {
            factorize(b, facts);
            for (auto &[f, n] : facts) n *= 2;
            divisors(b + N, [&](int d) {
                int a = d - b;
                if (a < 1 || a > N) return;
                ans += ((ll)b * __gcd(b, a) % d == 0);
            });
        }
        cout << ans << "\n";
    }
}
