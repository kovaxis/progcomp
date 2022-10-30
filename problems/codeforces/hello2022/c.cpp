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

int N, gtime;
vector<bool> seen;
vector<int> p;

int ask(int i) {
    cout << "? " << i + 1 << endl;
    cin >> i;
    gtime += 1;
    return i - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        p.assign(N, -1);
        seen.assign(N, false);
        gtime = 0;

        rep(i, N) {
            if (seen[i]) continue;
            vector<int> nums;
            int ttime = gtime;
            while (true) {
                int x = ask(i);
                if (seen[x]) break;
                seen[x] = true;
                nums.push_back(x);
            }
            int cycle = nums.size();
            int first = ((1 - ttime) % cycle + cycle) % cycle;
            rotate(nums.begin(), nums.begin() + first, nums.end());
            int x = i;
            for (int y : nums) {
                p[x] = y;
                x = y;
            }
        }

        cout << "!";
        rep(i, N) cout << " " << p[i] + 1;
        cout << endl;
    }
}
