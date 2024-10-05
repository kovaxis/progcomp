#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
ll S;
map<int, int> cnt;
vector<int> ans;

bool check(vector<int> centers, ll s) {
    sort(centers.begin(), centers.end());
    vector<int> res;
    invrepx(i, 1, centers.size()) {
        if (centers[i] - centers[i - 1] % 2 == 1) return false;
        res.push_back((centers[i] - centers[i - 1]) / 2);
    }
    if (N % 2) {
        res.push_back(centers[0]);
    } else {
        if (centers[0] % 2 == 1) return false;
        res.push_back(centers[0] / 2);
        res.push_back(centers[0] / 2);
    }
    repx(i, 1, centers.size()) {
        res.push_back((centers[i] - centers[i - 1]) / 2);
    }

    ll send = 0;
    ll s2 = 0;
    rep(i, res.size()) {
        send += ll(i + 1) * res[i];
        s2 += send;
    }

    if (s2 != s) return false;

    ans = res;
    return true;
}

int appears(int i) {
    if (N % 2 == 1 && i == 0) return (N + 1) / 2 * (N + 1) / 2;
    return 2 * ((N + 1) / 2 - i) * (N / 2 + 1 + i);
}

bool checkodd(vector<int> centers, int k) {
    ll s2 = S;
    for (auto x : centers) s2 -= x;

    if (k != 0) centers[k] = centers[k - 1];

    vector<int> res, resx;
    invrepx(i, 1, centers.size()) {
        if (i == k) res.push_back(0), resx.push_back(1);
        else {
            if (centers[i] - centers[i - 1] % 2 == 1) return false;
            res.push_back((centers[i] - centers[i - 1]) / 2);
            resx.push_back(i > k ? -1 : 0);
        }
    }
    if (N % 2) {
        res.push_back(centers[0]);
        if (k == 0) res.push_back(1);
    } else {
        if (centers[0] % 2 == 1) return false;
        res.push_back(centers[0] / 2);
        if (k == 0) res.push_back(1);
        res.push_back(centers[0] / 2);
        if (k == 0) res.push_back(1);
    }
    repx(i, 1, centers.size()) {
        if (i == k) res.push_back(0), resx.push_back(1);
        else {
            res.push_back((centers[i] - centers[i - 1]) / 2);
            resx.push_back(i > k ? -1 : 0);
        }
    }

    ll send = 0;
    ll sendx = 0;
    ll ss = 0;
    ll ssx = 0;
    rep(i, res.size()) {
        send += ll(i + 1) * res[i];
        sendx += ll(i + 1) * resx[i];
        ss += send;
        ssx += sendx;
    }
    ll ssfull = ss, ssxfull = ssx;
    rep(i, centers.size()) {
        ss -= centers[i];
        if (i == k) ssx -= 1;
        if (i > k) ssx += 1;
    }

    assert(ssx != 0);
    // ss + x * ssx = s2
    if (s2 - ss <= 0 || (s2 - ss) % ssx != 0) return false;
    ll x = (s2 - ss) / ssx;
    centers[k] = (k == 0 ? 0 : centers[k - 1]) + x;

    return check(centers, ssfull + ssxfull * x);
}

void solve_remodd() {
    vector<int> odd;
    for (auto [x, n] : cnt) {
        if (n % 2) odd.push_back(x);
    }
    sort(odd.begin(), odd.end());

    rep(i, odd.size() + 1) {
        vector<int> centers = odd;
        centers.insert(centers.begin() + i, 0);
        if (checkodd(centers, i)) return;
    }

    throw "?";
}

void solve_remeven() {
    vector<int> odd;
    for (auto [x, n] : cnt) {
        if (n % 2) odd.push_back(x);
    }

    rep(i, odd.size()) {
        vector<int> centers = odd;
        centers.erase(centers.begin() + i);
        ll s = S;
        rep(j, odd.size()) {
            if (j == i) s += odd[j];
        }
        if (check(centers, s)) {
            return;
        }
    }

    throw "?";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        cnt.clear();
        rep(i, N * (N + 1) / 2 - 1) {
            int s;
            cin >> s;
            cnt[s] += 1;
        }

        int odd = 0;
        for (auto [x, n] : cnt) {
            if (n % 2) odd += 1;
        }

        S = 0;
        for (auto [x, n] : cnt) {
            S += (ll)x * n;
        }

        ans.assign(N, -1);
        if (odd == (N + 1) / 2 - 1) solve_remodd();
        else if (odd == (N + 1) / 2 + 1) solve_remeven();
        else throw "?";

        rep(i, N) cout << ans[i] << " ";
        cout << "\n";
    }
}
