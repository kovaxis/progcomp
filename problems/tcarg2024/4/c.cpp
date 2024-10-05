#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int MOD = 1e9 + 7;

int Ns, Nt, ans;
vector<vector<int>> Gs, Gt;
vector<int> prevkid, lastkid;
int prereq[13][13];
int DP1[1000][12][13];
int DP2[1000][13][1 << 12];

string hasht(int v, int p) {
    vector<string> sub;
    for (int w : Gt[v])
        if (w != p) sub.push_back(hasht(w, v));
    sort(sub.begin(), sub.end());
    string out = "(";
    for (string s : sub) out.append(s);
    out.push_back(')');
    return out;
}

int dp1(int u, int v, int vp);

// number of ways to match a subset of the kids up to `u` to the siblings listed by `bits` in T, using `vp` as their parent
int dp2(int u, int vp, int bits) {
    if (u == -1) {
        return bits == 0;
    }
    int &res = DP2[u][vp][bits];
    if (res != -1) return res;
    int x = dp2(prevkid[u], vp, bits);
    int b = bits;
    while (b != 0) {
        int v = __builtin_ctz(b);
        b &= ~(1 << v);
        if (bits & prereq[v][vp]) continue;
        x = (x + (ll)dp2(prevkid[u], vp, bits & ~(1 << v)) * dp1(u, v, vp)) % MOD;
    }
    // cerr << "ways to match S nodes {";
    // int u2 = u;
    // while (u2 != -1) {
    //     cerr << u2 + 1 << " ";
    //     u2 = prevkid[u2];
    // }
    // cerr << "} to kids of T node [" << vp + 1 << "] {";
    // rep(v2, Nt) if (bits & (1 << v2)) cerr << v2 + 1 << " ";
    // cerr << "} = " << x << endl;
    // cerr << "  no-op = " << dp2(prevkid[u], vp, bits) << endl;
    // b = bits;
    // while (b != 0) {
    //     int v = __builtin_ctz(b);
    //     b &= ~(1 << v);
    //     cerr << "  prereq of " << v + 1 << " with parent " << vp + 1 << " is " << prereq[v][vp] << endl;
    //     if (bits & prereq[v][vp]) cerr << "  skipped";
    //     else cerr << "  added";
    //     cerr << " dp2[" << prevkid[u] + 1 << "][" << vp + 1 << "][" << (bits & ~(1 << v)) << "] * dp1[" << u + 1 << "][" << v + 1 << "][" << vp + 1 << "]";
    //     if (bits & prereq[v][vp]) {
    //     } else {
    //         cerr << " = " << dp2(prevkid[u], vp, bits & ~(1 << v)) << "*" << dp1(u, v, vp);
    //     }
    //     cerr << endl;
    // }
    return res = x;
}

// number of ways to match `u` to `v` (with parent `vp`)
int dp1(int u, int v, int vp) {
    int &res = DP1[u][v][vp];
    if (res != -1) return res;
    int vkids = 0;
    for (int v2 : Gt[v])
        if (v2 != vp) vkids |= (1 << v2);
    res = dp2(lastkid[u], v, vkids);
    // cerr << "ways to match S node [" << u + 1 << "] to T node [" << v + 1 << "] with parent [" << vp + 1 << "] = " << res << endl;
    return res;
}

void addans(int v, int u, int p) {
    ans = (ans + dp1(u, v, Nt)) % MOD;
    // if (dp1(u, v, Nt)) cerr << dp1(u, v, Nt) << " matches of node " << u + 1 << " against node " << v + 1 << endl;
    for (int u2 : Gs[u])
        if (u2 != p) {
            addans(v, u2, u);
        }
}

void prevkid_dfs(int u, int up) {
    int last = -1;
    for (int u2 : Gs[u])
        if (u2 != up) {
            prevkid[u2] = last;
            last = u2;
            prevkid_dfs(u2, u);
        }
    lastkid[u] = last;
}

int solve() {
    memset(&DP1, -1, sizeof(DP1));
    memset(&DP2, -1, sizeof(DP2));

    prevkid.assign(Ns, -1);
    lastkid.assign(Ns, -1);
    prevkid_dfs(0, -1);

    rep(vp, Nt) {
        map<string, int> prev;
        for (int v : Gt[vp]) {
            string h = hasht(v, vp);
            prereq[v][vp] = prev[h];
            prev[h] |= 1 << v;
        }
    }

    set<string> seen;
    rep(v, Nt) {
        string h = hasht(v, -1);
        if (!seen.count(h)) {
            seen.insert(h);
            addans(v, 0, -1);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Ns;
    Gs.resize(Ns);
    rep(j, Ns - 1) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        Gs[u].push_back(v);
        Gs[v].push_back(u);
    }

    cin >> Nt;
    Gt.resize(Nt);
    rep(j, Nt - 1) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        Gt[u].push_back(v);
        Gt[v].push_back(u);
    }

    cout << solve() << endl;
}
