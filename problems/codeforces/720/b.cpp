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

pair<int, int> nums[100009];
int orig[100009];
int pos[100009];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int n;
        cin >> n;
        rep(i, n) {
            int num;
            cin >> num;
            orig[i] = num;
            nums[i] = {num, i};
            pos[i] = i;
        }
        if (n <= 1) {
            cout << "0\n";
            continue;
        }
        sort(&nums[0], &nums[n]);
        int smallest = nums[0].first;
        int largest = nums[n - 1].first;
        int next_num = smallest * ((largest + smallest - 1) / smallest);
        cout << n << '\n';
        rep(i, n) {
            int num = nums[n - i - 1].first;
            int idx = nums[n - i - 1].second;
            int oi, oj, ox, oy;
            if (i != pos[idx]) {
                oi = i;
                oj = pos[idx];
                ox = next_num;
                oy = orig[i];
                pos[i] = pos[idx];
            } else {
                if (i == n - 1) {
                    oi = 0;
                    oj = n - 1;
                    ox = num;
                    oy = next_num;
                } else {
                    auto& smaller = nums[n - i - 2];
                    oi = pos[idx];
                    oj = pos[smaller.second];
                    ox = next_num;
                    oy = smaller.first;
                }
            }
            cout << oi + 1 << " " << oj + 1 << " " << ox << " " << oy << '\n';
            next_num ^= 1;
        }
    }
}
