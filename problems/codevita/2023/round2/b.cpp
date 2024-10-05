#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N, K;
vector<string> names;
string letters;

const bool ignore_case = true;
const bool allow2 = true;
const int opt = 4;

int solve() {
    vector<int> alive(N);
    rep(i, N) alive[i] = i;

    // phase 1
    while (true) {
        string s;
        for (int j : alive) s.push_back(j);
        int elim = -1;
        rep(i, (int)alive.size()) {
            if (i >= 2) {
                if (letters[alive[i - 2]] == letters[alive[i]]) {
                    elim = i;
                    break;
                }
            }
            // NOTE: allow 2-letter palindromes?
            if (allow2 && i >= 1) {
                if (letters[alive[i - 1]] == letters[alive[i]]) {
                    elim = i;
                    break;
                }
            }
        }
        if (elim == -1) break;
        cerr << "erasing " << names[alive[elim]] << endl;
        alive.erase(alive.begin() + elim);
    }

    // phase 2
    // NOTE: very ambiguous when K is not 1 or 2

    if (opt == 1) {
        // option 1: first/last
        if (K > 1) {
            // first
            cerr << "picking first" << endl;
            return alive.front();
        } else {
            // last
            cerr << "picking last" << endl;
            return alive.back();
        }
    } else if (opt == 2) {
        // option 2: remove the Kth from the start, cycling if there are not enough names
        while (alive.size() > 1) {
            int elim = (K - 1) % int(alive.size());
            alive.erase(alive.begin() + elim);
        }
        return alive[0];
    } else if (opt == 3) {
        // option 3: remove the Kth until there are not enough people, then choose the last
        while ((int)alive.size() >= K && alive.size() > 1) {
            alive.erase(alive.begin() + (K - 1));
        }
        return alive.back();
    } else if (opt == 4) {
        // option 4: advance K, remove, advance K, remove, etc. cyclic
        int i = 0;
        while ((int)alive.size() > 1) {
            i = (i + K - 1) % (int)alive.size();
            alive.erase(alive.begin() + i);
        }
        return alive[0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    getline(cin, s);
    stringstream ss(s);
    string n;
    while (ss >> n) {
        N += 1;
        names.push_back(n);
        char letter = n[0];
        if (ignore_case) letter = tolower(letter);
        letters.push_back(letter);
    }
    cin >> K;

    cout << names[solve()] << endl;
}
