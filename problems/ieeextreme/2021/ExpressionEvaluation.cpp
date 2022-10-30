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

const ll MOD = 1000000007;

string expr;
int nxt;
bool err;

ll eval_expr(bool);

ll eval_unit() {
    if (expr[nxt] == '(') {
        // nested
        nxt += 1;
        return eval_expr(true);
    } else if (expr[nxt] >= '0' && expr[nxt] <= '9') {
        // int literal
        ll num = 0;
        while (nxt < expr.size() && expr[nxt] >= '0' && expr[nxt] <= '9') {
            num *= 10;
            num += expr[nxt] - '0';
            nxt += 1;
        }
        return num;
    } else {
        err = true;
        return 0;
    }
}

ll eval_mul() {
    ll ans = 1;
    while (true) {
        if (nxt >= expr.size() || expr[nxt] != '*') break;
        nxt += 1;
        ll sub = eval_unit();
        ans = ans * sub % MOD;
    }
    return ans;
}

ll eval_expr(bool expect_close) {
    ll ans = 0;
    char op = '+';
    while (true) {
        ll sub = eval_unit();
        if (nxt < expr.size() && expr[nxt] == '*') {
            sub = sub * eval_mul() % MOD;
        }
        if (op == '+') {
            ans = (ans + sub) % MOD;
        } else if (op == '-') {
            ans = (ans + MOD - sub) % MOD;
        }

        if (nxt >= expr.size()) {
            err |= expect_close;
            break;
        } else if (expr[nxt] == ')') {
            nxt += 1;
            err |= !expect_close;
            break;
        } else if (expr[nxt] == '+' || expr[nxt] == '-') {
            op = expr[nxt];
            nxt += 1;
        } else {
            err = true;
            break;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> expr;
        nxt = 0;
        err = false;

        ll ans = eval_expr(false);
        if (err) {
            cout << "invalid\n";
        } else {
            cout << ans << "\n";
        }
    }
}
