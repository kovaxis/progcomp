#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

template <class T>
ostream &operator<<(ostream &s, const vector<T> &a) {
    rep(i, a.size()) {
        s << a[i];
        if (i != a.size() - 1) s << " ";
    }
    return s;
}

const int MOD = 1e9 + 7, P = 5627851;

int binexp(int a, ll e, int M = MOD) {
    assert(e >= 0);
    int res = 1 % M;
    while (e) {
        if (e & 1) res = (ll)res * a % M;
        a = (ll)a * a % M;
        e >>= 1;
    }
    return res;
}

int N;
map<ll, int> cnt;
int cnth;
ll cntsum;
vector<ll> answer;

ll allsum(const vector<ll> &a) {
    ll suff = 0;
    ll acc = 0;
    rep(i, a.size()) {
        suff += (i + 1) * a[i];
        acc += suff;
    }
    return acc;
}

vector<ll> buildpali(const vector<ll> &vals) {
    assert(vals.size() == (N + 1) / 2);
    vector<ll> out;
    out.insert(out.end(), vals.rbegin(), vals.rend());
    if (N % 2) out.insert(out.end(), vals.begin() + 1, vals.end());
    else out.insert(out.end(), vals.begin(), vals.end());
    return out;
}

bool check(vector<ll> vals, ll missing) {
    if (missing <= 0) return false;
    vector<ll> ans = buildpali(vals);
    int suff = 0, h = 0;
    rep(i, ans.size()) {
        if (ans[i] <= 0) return false;
        suff = ll(suff + 1) * binexp(P, ans[i]) % MOD;
        h = (h + suff) % MOD;
    }

    cerr << "  checking " << ans << " with h " << h << ", and total expected h " << (cnth + binexp(P, missing)) % MOD << endl;
    if (h != (cnth + binexp(P, missing)) % MOD) return false;
    answer = ans;
    return true;
}

vector<ll> vals2center(const vector<ll> &vals) {
    assert(vals.size() == (N + 1) / 2);
    vector<ll> center(vals.size());
    ll acc = 0;
    rep(i, vals.size()) {
        acc += (i == 0 && N % 2 ? 1 : 2) * vals[i];
        center[i] = acc;
    }
    return center;
}

vector<ll> center2vals(const vector<ll> &center) {
    assert(center.size() == (N + 1) / 2);
    vector<ll> vals(center.size());
    rep(i, center.size()) {
        ll mult = (i == 0 && N % 2 ? 1 : 2);
        ll d = center[i] - (i == 0 ? 0 : center[i - 1]);
        if (d % mult != 0) return {};
        vals[i] = d / mult;
    }
    return vals;
}

ll symmsum(const vector<ll> &vals) {
    vector<ll> center = vals2center(vals);
    ll s = 0;
    for (ll x : center) s += x;
    return s;
}

bool remval(vector<ll> centers, ll removed) {
    cerr << "trying remval with centers " << centers << " and removed value " << removed << endl;
    assert(centers.size() == (N + 1) / 2);
    vector<ll> vals = center2vals(centers);
    if (vals.empty()) return false;
    return check(vals, removed);
}

void remvals() {
    vector<ll> centers;
    for (auto [x, n] : cnt) {
        if (n % 2) centers.push_back(x);
    }
    assert(centers.size() == (N + 1) / 2 + 1);
    sort(centers.begin(), centers.end());

    rep(i, centers.size()) {
        vector<ll> trimmed_centers = centers;
        trimmed_centers.erase(trimmed_centers.begin() + i);
        if (remval(trimmed_centers, centers[i])) return;
    }

    cerr << "no remval" << endl;
    throw "no remval";
}

bool addval(vector<ll> centers, int k) {
    cerr << "trying addval with centers " << centers << endl;
    assert(centers.size() == (N + 1) / 2);

    if (k == 0 && N % 2) {
        for (auto [yx, n] : cnt) {
            ll y = centers[1] - yx;
            ll x = yx - y;
            if (y <= 0 || x <= 0) continue;

            centers[0] = x;
            vector<ll> vals = center2vals(centers);
            if (vals.empty()) continue;
            cerr << "  checking with vals = " << vals << endl;
            if (check(vals, x)) return true;
        }
        return false;
    } else {
        if (k > 0) centers[k] = centers[k - 1];
        vector<ll> vals = center2vals(centers);
        if (vals.empty()) return false;
        vector<ll> valsx(centers.size());
        valsx[k] = 1;
        if (k + 1 < centers.size()) valsx[k + 1] = -1;

        ll nsum = allsum(buildpali(vals));
        ll xsum = allsum(buildpali(valsx));
        ll nmissing = vals2center(vals)[k];
        ll xmissing = vals2center(valsx)[k];
        cerr << "  vals: " << vals << endl;
        cerr << "  valsx: " << valsx << endl;
        cerr << "  nsum = " << nsum << ", xsum = " << xsum << endl;
        cerr << "  real sum: " << cntsum << " + " << nmissing << " + x * " << xmissing << endl;
        // nsum + x * hsum = cntsum + nmissing + x * hmissing
        // x * (hsum - hmissing) = cntsum + nmissing - nsum
        // x = (cntsum + nmissing - nsum) / (hsum - hmissing)
        ll den = xsum - xmissing;
        ll num = (cntsum + nmissing - nsum);
        if (den == 0)
            while (true) { cerr << "alo"; }
        if (num % den != 0 || num / den <= 0) return false;
        ll x = num / den;
        rep(i, vals.size()) vals[i] += x * valsx[i];

        vector<ll> center = vals2center(vals);
        cerr << "  using x = " << x << ", vals = " << vals << ", center = " << center << endl;
        return check(vals, center[k]);
    }
}

void addvals() {
    vector<ll> centers;
    for (auto [x, n] : cnt) {
        if (n % 2) centers.push_back(x);
    }
    assert(centers.size() == (N + 1) / 2 - 1);
    sort(centers.begin(), centers.end());

    rep(i, centers.size() + 1) {
        vector<ll> expanded_centers = centers;
        expanded_centers.insert(expanded_centers.begin() + i, 0);
        if (addval(expanded_centers, i)) return;
    }

    cerr << "no addval" << endl;
    throw "no addval";
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
            ll s;
            cin >> s;
            cnt[s] += 1;
        }

        int odd = 0;
        for (auto [x, n] : cnt) {
            if (n % 2) odd += 1;
        }

        cntsum = 0, cnth = 0;
        for (auto [x, n] : cnt) {
            cntsum += (ll)x * n;
            cnth = (cnth + (ll)n * binexp(P, x)) % MOD;
        }

        answer.clear();
        if (odd == (N + 1) / 2 - 1) addvals();
        else if (odd == (N + 1) / 2 + 1) remvals();
        else throw "?";

        assert(answer.size() == N);
        rep(i, N) cout << answer[i] << " ";
        cout << "\n";
    }
}
