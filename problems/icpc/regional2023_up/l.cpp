#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int N;
string S;
vector<int> pairof;
ll ans;

int findpair(int i, int n) {
    while (i < n) {
        if (S[i] == '(') {
            int j = findpair(i + 1, n);
            if (j < n) {
                pairof[i] = j, pairof[j] = i;
                i = j + 1;
            } else {
                return n;
            }
        } else if (S[i] == ')') {
            return i;
        } else {
            i += 1;
        }
    }
    return i;
}

void do_count(int l, int r) {
    if ((S[l] == '(' || S[l] == ')') && pairof[l] == -1) return;

    int k = 0;
    repx(i, l, r) {
        if (S[i] == 'a') {
            k += 1;
        } else if (S[i] == '*') {
            // nothing
        } else if (S[i] == '(') {
            do_count(i + 1, pairof[i]);
            i = pairof[i];
            k += 1;
        }
    }
    cerr << "  " << k << " valid points in string '" << S.substr(l, r - l) << "'" << endl;
    ans += ll(k) * (k + 1) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> S;

    for (char &c : S) {
        if (c >= 'a' && c <= 'z') c = 'a';
        if (c == '+' || c == '-' || c == '/') c = '*';
    }

    S.insert(S.begin(), '(');
    S.push_back(')');
    N = S.size();

    vector<bool> boundary(N + 1);
    vector<string> illegal = {
        "a(",
        ")a",
        "**",
        "(*",
        "*)",
        ")(",
        "()",
    };
    rep(i, N - 1) {
        for (string &il : illegal) {
            if (S[i] == il[0] && S[i + 1] == il[1]) boundary[i + 1] = true;
        }
    }
    boundary[1] = true;
    boundary[N - 1] = true;
    boundary[N] = true;

    pairof.assign(N, -1);
    for (int i = 0; i < N;) {
        int l = i++;
        while (!boundary[i]) i++;
        cerr << "finding pairs in segment [" << l << ", " << i << ")" << endl;
        for (int j = l; j < i;) j = findpair(j, i) + 1;
        repx(j, l, i) if ((S[j] == '(' || S[j] == ')') && pairof[j] == -1) boundary[j] = true, boundary[j + 1] = true;
    }

    rep(i, N) {
        cerr << "pairof[" << i << "] = " << pairof[i] << endl;
    }

    for (int i = 0; i < N;) {
        int l = i++;
        while (!boundary[i]) i++;
        cerr << "finding count in segment [" << l << ", " << i << ")" << endl;
        do_count(l, i);
    }

    cout << ans << endl;
}
