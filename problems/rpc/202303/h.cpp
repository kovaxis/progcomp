#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

ll N;
vector<ll> A;
vector<ll> nxtl, nxtr;

void calcnext(vector<ll> &nxt) {
    cerr << "calc" << endl;
    nxt.resize(2 * N);
    vector<ll> stk;
    invrep(i, 2 * N) {
        cerr << "checking " << i + 1 << endl;
        int l = -1, r = int(stk.size()) - 1;
        while (l != r) {
            int m = (l + r + 1) / 2;
            if (A[stk[m]] <= 2 * A[i]) r = m - 1;
            else l = m;
        }
        if (l == -1) nxt[i] = i;
        else nxt[i] = stk[l];

        while (!stk.empty() && A[stk.back()] <= A[i]) stk.pop_back();
        stk.push_back(i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cerr << "reading" << endl;

    cin >> N;
    A.resize(2 * N);
    rep(i, N) cin >> A[i];
    rep(i, N) A[i + N] = A[i];

    cerr << "calcing" << endl;
    calcnext(nxtr);
    reverse(A.begin(), A.end());
    calcnext(nxtl);
    reverse(A.begin(), A.end());
    reverse(nxtl.begin(), nxtl.end());
    rep(i, 2 * N) nxtl[i] = 2 * N - nxtl[i] - 1;

    cerr << "adding" << endl;
    vector<ll> sum(A);
    repx(i, 1, 2 * N) {
        sum[i] += sum[i - 1];
    }

    rep(i, 2 * N) cerr << A[i] << " ";
    cerr << endl;
    rep(i, 2 * N) cerr << nxtl[i] + 1 << " ";
    cerr << endl;
    rep(i, 2 * N) cerr << nxtr[i] + 1 << " ";
    cerr << endl;

    cerr << "doing" << endl;
    ll best = 1e18;
    rep(start, N) {
        ll l = start + 1, r = start + N - 1;
        ll ans = A[start];
        ll curr = ans + A[start];
        while (1) {
            if (A[l] < A[r]) {
                if (A[l] > curr) ans += A[l] - curr, curr = A[l];
                ll next = nxtr[l];
                if (next == l || next > r) break;
                curr += A[l] + sum[next - 1] - sum[l];
                l = next;
            } else {
                if (A[r] > curr) ans += A[r] - curr, curr = A[r];
                ll next = nxtl[r];
                if (next == r || next < l) break;
                curr += sum[r] - sum[next];
                r = next;
            }
        }
        best = min(best, ans);
        cerr << ans << " ";
    }
    cerr << endl;
    cout << best << endl;
}