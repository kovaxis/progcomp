#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

const int Blim = 2000;

int N, Qn;
vector<pair<int, int>> sup;
vector<pair<char, pair<int, int>>> Q;
vector<ll> best;
vector<pair<int, int>> pending;
vector<pair<int, int>> goodclients;

ll profit(pair<int, int> s, pair<int, int> c) {
    return ll(c.first - s.first) * (c.second - s.second);
}

void compute(int Li, int Ri, int Lj, int Rj) {
    if (Li >= Ri) return;
    int Mi = (Li + Ri) / 2;
    int lj = Rj - 1, rj = Rj;
    repx(j, Lj, Rj) if (goodclients[j].first >= sup[Mi].first) {
        lj = j;
        break;
    }
    repx(j, lj, Rj) if (goodclients[j].second < sup[Mi].second) {
        rj = j;
        break;
    }
    int ans_j = lj;
    repx(j, lj, rj) {
        if (profit(sup[Mi], goodclients[j]) >= profit(sup[Mi], goodclients[ans_j])) {
            ans_j = j;
        }
    }
    if (sup[Mi].first <= goodclients[ans_j].first && sup[Mi].second <= goodclients[ans_j].second) {
        best[Mi] = max(best[Mi], profit(sup[Mi], goodclients[ans_j]));
    }
    compute(Li, Mi, Lj, ans_j + 1);
    compute(Mi + 1, Ri, ans_j, Rj);
}

void rebuild_best() {
    sort(pending.begin(), pending.end());
    goodclients.clear();
    goodclients.reserve(pending.size());
    for (auto c : pending) {
        while (goodclients.size() && c.second >= goodclients.back().second) goodclients.pop_back();
        goodclients.push_back(c);
    }
    compute(0, N, 0, goodclients.size());
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    sup.resize(N);
    rep(i, N) cin >> sup[i].first >> sup[i].second;
    rep(i, N) sup[i].first -= 1;

    cin >> Qn;
    Q.resize(Qn);
    rep(qi, Qn) {
        char ty;
        cin >> ty;
        if (ty == 's') {
            int i;
            cin >> i;
            i -= 1;
            Q[qi] = {ty, {i, 0}};
        } else if (ty == 'c') {
            int x, y;
            cin >> x >> y;
            Q[qi] = {ty, {x, y}};
        }
    }

    best.assign(N, 0);
    rep(qi, Qn) {
        if (Q[qi].first == 's') {
            // question
            int i = Q[qi].second.first;
            ll ans = best[i];
            for (auto c : pending) {
                if (c.first >= sup[i].first) {
                    ans = max(ans, profit(sup[i], c));
                }
            }
            cout << ans << "\n";
        } else {
            // new client
            pending.push_back(Q[qi].second);
            if (pending.size() >= Blim) {
                rebuild_best();
                pending.clear();
            }
        }
    }
}
