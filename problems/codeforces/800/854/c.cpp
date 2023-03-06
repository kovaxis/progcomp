#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

string makeans(string &front, string &back) {
    string ans(front.begin(), front.end());
    ans.append(back.rbegin(), back.rend());
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int TC;
    cin >> TC;
    while (TC--) {
        cin >> s;
        vector<int> cnt(26);
        for (char c : s) {
            cnt[c - 'a'] += 1;
        }

        string front, back;
        rep(c, 26) {
            while (cnt[c] >= 2) {
                front.push_back('a' + c);
                back.push_back('a' + c);
                cnt[c] -= 2;
            }
            if (cnt[c] == 1) {
                int diff = 0;
                repx(i, c + 1, 26) diff += (cnt[i] != 0);
                if (diff == 1) {
                    int c2;
                    repx(i, c + 1, 26) if (cnt[i] != 0) c2 = i;
                    while (cnt[c2] > 0) {
                        if (cnt[c2] % 2) front.push_back('a' + c2);
                        else back.push_back('a' + c2);
                        cnt[c2] -= 1;
                    }
                    front.push_back('a' + c);
                } else {
                    back.push_back('a' + c);
                    repx(i, c + 1, 26) rep(j, cnt[i]) front.push_back('a' + i);
                }
                break;
            }
        }

        front.append(back.rbegin(), back.rend());

        cout << front << "\n";
    }
}
