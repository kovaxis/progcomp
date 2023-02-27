#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int N, M;
vector<int> pass;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    pass.resize(N);
    rep(i, N) cin >> pass[i];

    sort(pass.rbegin(), pass.rend());

    int idx = -1;
    rep(i, N) {
        int a = M / pass[i];
        if (i >= a) {
            idx = i;
        }
    }

    vector<bool> marked(M);
    if (idx == -1) {
        // alice
        cout << "Alessia" << endl;
        rep(t, N) {
            int nxt = 0, a = -1;
            rep(i, M) {
                nxt = max(nxt, i);
                while (nxt < M && !marked[nxt]) nxt += 1;
                if (nxt - i >= pass[t]) {
                    a = i;
                }
            }
            assert(a != -1);
            cout << pass[t] << " " << a + 1 << endl;

            int b;
            cin >> b;
            marked[b - 1] = true;
        }
    } else {
        // bob
        cout << "Bernardo" << endl;
        vector<bool> hot(M);
        rep(i, M) {
            hot[i] = (i % pass[idx] == pass[idx] - 1);
        }
        rep(t, N) {
            int n, l;
            cin >> n >> l;
            l--;
            int to_mark = -1;
            repx(i, l, l + n) {
                if (marked[i]) {
                    to_mark = i;
                    break;
                }
            }
            if (to_mark == -1) {
                repx(i, l, l + n) {
                    if (hot[i]) {
                        to_mark = i;
                        break;
                    }
                }
            }
            if (to_mark == -1) to_mark = l;
            marked[to_mark] = true;
            cout << to_mark + 1 << endl;
        }
    }
}
