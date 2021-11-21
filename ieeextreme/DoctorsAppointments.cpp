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

vector<pair<int, int>> patients;
vector<int> times;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N;
        cin >> N;
        patients.resize(N);
        times.clear();
        rep(i, N) { cin >> patients[i].second >> patients[i].first; }
        sort(patients.begin(), patients.end());
        int last = 0;
        for (auto p : patients) {
            int s = p.second, e = p.first;
            last = max(last + 1, s);
            if (last <= e) {
                times.push_back(last);
            }
        }
        if (times.size() == N) {
            rep(i, N) cout << times[i] << " \n"[i == N - 1];
        } else {
            cout << "impossible\n";
        }
    }
}
