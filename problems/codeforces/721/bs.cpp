#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int a;
int b;
int c;
bool alice;
bool canr;
int cost[2];

vector<char> plays[2];

int play(int depth) {
    if (a <= 0 && b <= 0 && c <= 0) {
        if (cost[alice] > cost[!alice]) {
            // won
            return alice;
        } else if (cost[alice] < cost[!alice]) {
            // lost
            return !alice;
        } else {
            // draw
            return -1;
        }
    }
    alice = !alice;
    int won = -1;
    bool draw = false;
    if (canr && b > 0) {
        canr = false;
        plays[alice].push_back('R');
        won = play(depth + 1);
        if (won == !alice) {
            canr = true;
            alice = !alice;
            return won;
        }
        plays[alice].resize(depth);
        if (won == -1) {
            draw = true;
        }
    }
    canr = true;
    if (b > 0) {
        b--;
        cost[alice]++;
        plays[alice].push_back('1');
        won = play(depth + 1);
        b++;
        cost[alice]--;
        if (won == !alice) {
            alice = !alice;
            return won;
        }
        plays[alice].resize(depth);
        if (won == -1) {
            draw = true;
        }
    }
    if (a > 0) {
        a--;
        cost[alice]++;
        canr = true;
        plays[alice].push_back('0');
        won = play(depth + 1);
        a++;
        cost[alice]--;
        if (won == !alice) {
            alice = !alice;
            return won;
        }
        plays[alice].resize(depth);
        if (won == -1) {
            draw = true;
        }
    }
    if (c > 0) {
        c--;
        b++;
        cost[alice]++;
        plays[alice].push_back('2');
        won = play(depth + 1);
        c++;
        b--;
        cost[alice]--;
        if (won == !alice) {
            alice = !alice;
            return won;
        }
        plays[alice].resize(depth);
        if (won == -1) {
            draw = true;
        }
    }
    alice = !alice;
    if (draw) {
        return -1;
    } else {
        return won;
    }
}

int run(int ap, int bp, int cp) {
    a = ap;
    b = bp;
    c = cp;
    alice = true;
    canr = true;
    cost[0] = 0;
    cost[1] = 0;
    plays[0].clear();
    plays[1].clear();
    return play(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    /*int ts;
    cin >> ts;
    rep(t, ts) {
        cin >> a >> b >> c;
        int result = run(a, b, c);
        if (result == 1) {
            cout << "ALICE\n";
            for (char p : plays[0]) {
                cout << p;
            }
            cout << endl;
        } else if (result == 0) {
            cout << "BOB\n";
            for (char p : plays[1]) {
                cout << p;
            }
            cout << endl;
        } else {
            cout << "DRAW\n";
        }
    }*/
    rep(ap, 2) {
        rep(bp, 8) {
            rep(cp, 8) {
                int result = run(ap, bp, cp);
                if (result == 0) {
                    cout << 'B';
                } else if (result == 1) {
                    cout << 'A';
                } else {
                    cout << 'D';
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}
