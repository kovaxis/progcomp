#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e9;

int N;
set<int> cards[2][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        N /= 4;
        rep(k, 2) rep(p, 2) {
            cards[p][k].clear();
            rep(i, N) {
                int c;
                cin >> c;
                cards[p][k].insert(c);
            }
        }

        int a_score = 0;
        rep(t, N) {
            int max_p, max_k, max_card = 0;
            rep(p, 2) rep(k, 2) if (*(--cards[p][k].end()) > max_card) max_p = p, max_k = k, max_card = *(--cards[p][k].end());
            cerr << "turn " << t + 1 << ": "
                 << "AB"[max_p] << "12"[max_k] << " plays max card" << endl;
            a_score += (max_p == 0);
            int loser_card = max(*cards[!max_p][0].begin(), *cards[!max_p][1].begin());
            int winner_k, winner_card = INF;
            rep(k, 2) {
                auto it = cards[max_p][k].lower_bound(loser_card);
                if (it != cards[max_p][k].end()) {
                    if (*it < winner_card) winner_k = k, winner_card = *it;
                }
            }
            rep(k, 2) rep(p, 2) {
                if (p == max_p && k == winner_k) {
                    cerr << "  player "
                         << "AB"[p] << "12"[k] << " plays card " << winner_card << endl;
                    cards[p][k].erase(winner_card);
                } else {
                    cerr << "  player "
                         << "AB"[p] << "12"[k] << " plays card " << *cards[p][k].begin() << endl;
                    cards[p][k].erase(cards[p][k].begin());
                }
            }
        }

        cout << "Case #" << tc + 1 << ": " << a_score
             << "\n";
    }
}
