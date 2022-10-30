#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const int INF = 1e9;

vector<int> nxtsame;
int N;
string s;

int isregular(int i, int upto) {
    if (i >= upto) return -1;
    if (i >= N) return -1;
    if (s[i] != '(') return -1;
    int e = i + 1;
    while (e < N && s[e] != ')') {
        e = isregular(e, upto);
        if (e == -1) return -1;
    }
    if (e >= N) return -1;
    return e + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> s;
        N = s.size();

        {
            vector<int> nxtof(128, N);
            nxtsame.resize(N);
            invrep(i, N) {
                nxtsame[i] = nxtof[s[i]];
                nxtof[s[i]] = i;
            }
        }

        int i = 0;
        int ops = 0;
        while (i < N) {
            int upto = nxtsame[i] + 1;
            int re = isregular(i, upto);
            if (re == -1 && upto == N + 1) break;
            if (re != -1) {
                upto = min(re, upto);
            }
            ops += 1;
            i = upto;
        }
        cout << ops << " " << N - i << "\n";
    }
}
