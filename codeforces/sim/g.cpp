#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (int)(n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

string s;
int k;
vector<int> tops[26];

int nxt[1000001];
int prv[1000001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> k;
    rep(i, s.size() + 1) {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
    invrep(i, s.size() - k, s.size()) { tops[s[i] - 'a'].push_back(i); }
    invrep(i, s.size() - k) {
        char& c = s[i];
        int firstlower = 9999999;
        rep(j, 0, c - 'a') {
            if (tops[j].size() == 0) continue;
            if (tops[j].back() < firstlower) firstlower = tops[j].back();
        }
        int firsthigher = 9999999;
        rep(j, c - 'a' + 1, 26) {
            if (tops[j].size() == 0) continue;
            if (tops[j].back() < firsthigher) firsthigher = tops[j].back();
        }
        if (firsthigher < firstlower) {
            int rem;
            if (firstlower < s.size()) {
                rem = prv[firstlower];
            } else {
                rem = s.size() - 1;
            }
            tops[s[rem] - 'a'].pop_back();
            s[rem] = 0;
            int remprev = prv[rem];
            int remnext = nxt[rem];
            nxt[remprev] = remnext;
            prv[remnext] = remprev;
            tops[c - 'a'].push_back(i);
        } else {
            c = 0;
        }
    }
    for (char c : s) {
        if (c != 0) cout << c;
    }
    cout << endl;
}
