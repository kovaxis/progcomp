#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

int N;
map<int, int> comp;
vector<int> decomp;
vector<pair<int, int>> A_og, B_og, A, B;
vector<int> Aord, Bord;
vector<int> mat, invmat;

ll area(int i) {
    int j = mat[i];
    return ll(B[j].first - A[i].first) * (B[j].second - A[i].second);
}

bool collides(int i, int j) {
    pair<int, int> a1 = A[i], b1 = B[mat[i]], a2 = A[j], b2 = B[mat[j]];
    if (a1.first < a2.first && a1.second < a2.second && b1.first > b2.first && b1.second > b2.second) return false;
    if (a2.first < a1.first && a2.second < a1.second && b2.first > b1.first && b2.second > b1.second) return false;
    return a1.first <= b2.first && b1.first >= a2.first && a1.second <= b2.second && b1.second >= a2.second;
}

bool solve() {
    vector<pair<bool, int>> evs;
    rep(i, N) evs.push_back({true, i}), evs.push_back({false, i});
    sort(evs.begin(), evs.end(), [](auto a, auto b) {
        return (a.first ? A[a.second] : B[a.second]) > (b.first ? A[b.second] : B[b.second]);
    });

    map<int, int> pending;
    mat.resize(N), invmat.resize(N);
    for (auto [ty, i] : evs) {
        if (ty) {
            auto it = pending.lower_bound(A[i].second);
            if (it == pending.end()) return false;
            mat[i] = it->second;
            invmat[it->second] = i;
            pending.erase(it);
        } else {
            if (pending.count(B[i].second)) return false;
            pending[B[i].second] = i;
        }
    }

    for (auto [ty, i] : evs) {
        if (ty) {
            pending.erase(B[mat[i]].second);
        } else {
            auto it = pending.lower_bound(B[i].second);
            if (it != pending.end()) {
                if (collides(invmat[i], invmat[it->second])) return false;
            }
            if (it != pending.begin()) {
                if (collides(invmat[i], invmat[(--it)->second])) return false;
            }
            pending[B[i].second] = i;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A_og.resize(N), B_og.resize(N);
    rep(i, N) cin >> A_og[i].first >> A_og[i].second;
    rep(i, N) cin >> B_og[i].first >> B_og[i].second;

    rep(i, N) {
        comp[A_og[i].first] = 0;
        comp[A_og[i].second] = 0;
        comp[B_og[i].first] = 0;
        comp[B_og[i].second] = 0;
    }
    for (auto &[d, c] : comp) {
        c = decomp.size();
        decomp.push_back(d);
    }
    A.resize(N), B.resize(N);
    rep(i, N) A[i] = {comp[A_og[i].first], comp[A_og[i].second]};
    rep(i, N) B[i] = {comp[B_og[i].first], comp[B_og[i].second]};

    if (solve()) {
        rep(i, N) cout << mat[i] + 1 << "\n";
    } else {
        cout << "syntax error\n";
    }
}
