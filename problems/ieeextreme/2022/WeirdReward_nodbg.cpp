#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll K;
string expr;

// ---------------- parser -------------

const int OP_ADD = 1;
const int OP_MUL = 2;
const int OP_LIT = 3;
const int OP_PAREN = 4;
struct SemiNode {
    int lhs, rhs, ty;
};

vector<SemiNode> seminodes;

int parse_lit(int &i) {
    int l = i;
    while (expr[i] >= '0' && expr[i] <= '9') i += 1;
    seminodes.push_back({l, i, OP_LIT});
    return seminodes.size() - 1;
}

int parse_expr(int &i);

int parse_term(int &i) {
    if (expr[i] == '(') {
        i += 1;
        int sub = parse_expr(i);
        i += 1;
        seminodes.push_back({sub, -1, OP_PAREN});
        return seminodes.size() - 1;
    } else {
        return parse_lit(i);
    }
}

int parse_muls(int &i) {
    int sub = parse_term(i);
    if (expr[i] == '*') {
        i += 1;
        int sub2 = parse_muls(i);
        seminodes.push_back({sub, sub2, OP_MUL});
        return seminodes.size() - 1;
    }
    return sub;
}

int parse_expr(int &i) {
    int sub = parse_muls(i);
    if (expr[i] == '+') {
        i += 1;
        int sub2 = parse_expr(i);
        seminodes.push_back({sub, sub2, OP_ADD});
        return seminodes.size() - 1;
    }
    return sub;
}

// ----------------- solver ------------------

// represents a set of values.
struct ValueSet {
    ll sums[10];

    ValueSet() {
        rep(i, 10) sums[i] = 0;
    }

    // apply a function to all values in the set.
    template <class OP>
    ValueSet map(OP op) const {
        ValueSet out;
        rep(k, K) {
            out.sums[op(k) % K] += sums[k];
        }
        return out;
    }

    // take the cross product of both sets and apply the given operation over the pairs.
    template <class OP>
    ValueSet join(const ValueSet &other, OP op) const {
        ValueSet out;
        rep(i, K) rep(j, K) {
            out.sums[op(i, j) % K] += sums[i] * other.sums[j];
        }
        return out;
    }

    // insert a value mod K into the set.
    void insert(int val) { sums[val % K] += 1; }

    // insert all values from another set into this set.
    void insert_all(const ValueSet &other) {
        rep(k, K) sums[k] += other.sums[k];
    }

    ll count(int x) { return sums[x % K]; }
};

struct Node {
    ValueSet left, right, any, all;
};

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

Node evaluate(int id) {
    SemiNode &sn = seminodes[id];
    Node out;
    if (sn.ty == OP_LIT) {
        char *s = &expr[sn.lhs];
        int n = sn.rhs - sn.lhs;

        ValueSet cur;
        cur.insert(0);
        rep(i, n) {
            int digit = s[i] - '0';
            cur = cur.map([&](auto x) { return x * 10 + digit; });
            out.left.insert_all(cur);
        }

        out.all.insert_all(cur);

        ValueSet dp;
        ValueSet acc;
        rep(i, n) {
            int digit = s[i] - '0';

            // add a zero prefix to represent the number formed by the single digit `digit`
            // (unless its zero, in that case add it only to the accumulator)
            if (digit == 0) acc.insert(0);
            else dp.insert(0);

            // multiply values of the dp by 10 and add digit value
            dp = dp.map([&](auto x) { return x * 10 + digit; });

            // add new numbers to the accumulator
            acc.insert_all(dp);

            if (i == n - 1) {
                out.right.insert_all(dp);
                if (digit == 0) out.right.insert(0);
            }
        }
        out.any = acc;
    } else if (sn.ty == OP_PAREN) {
        out = evaluate(sn.lhs);
        out.left = out.all;
        out.right = out.all;
        out.any.insert_all(out.all);
    } else {
        Node lhs = evaluate(sn.lhs);
        Node rhs = evaluate(sn.rhs);

        out.left = lhs.all.join(rhs.left, (sn.ty == OP_ADD ? add : mul));
        out.left.insert_all(lhs.left);

        out.right = rhs.all.join(lhs.right, (sn.ty == OP_ADD ? add : mul));
        out.right.insert_all(rhs.right);

        out.any = lhs.right.join(rhs.left, (sn.ty == OP_ADD ? add : mul));
        out.any.insert_all(lhs.any);
        out.any.insert_all(rhs.any);

        out.all = lhs.all.join(rhs.all, (sn.ty == OP_ADD ? add : mul));
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N_;
    cin >> K >> N_ >> expr;
    int cursor = 0;
    int root = parse_expr(cursor);
    Node ans = evaluate(root);
    cout << ans.any.count(0) << "\n";
}
