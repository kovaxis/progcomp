#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define DBG 0

#define cerr \
    if (DBG) cerr

ll K;
string expr;

// ---------------- parser -------------

const int OP_ADD = 1;
const int OP_MUL = 2;
const int OP_LIT = 3;
const int OP_PAREN = 4;
struct SemiNode {
    int lhs, rhs, ty;
    int l, r;
};

vector<SemiNode> seminodes;

int parse_lit(int &i) {
    int l = i;
    while (expr[i] >= '0' && expr[i] <= '9') i += 1;
    seminodes.push_back({-1, -1, OP_LIT, l, i});
    return seminodes.size() - 1;
}

int parse_expr(int &i);

int parse_term(int &i) {
    if (expr[i] == '(') {
        int l = i;
        i += 1;
        int sub = parse_expr(i);
        i += 1;
        seminodes.push_back({sub, -1, OP_PAREN, l, i});
        return seminodes.size() - 1;
    } else {
        return parse_lit(i);
    }
}

int parse_muls(int &i) {
    int l = i;
    int sub = parse_term(i);
    if (expr[i] == '*') {
        i += 1;
        int sub2 = parse_muls(i);
        seminodes.push_back({sub, sub2, OP_MUL, l, i});
        return seminodes.size() - 1;
    }
    return sub;
}

int parse_expr(int &i) {
    int l = i;
    int sub = parse_muls(i);
    if (expr[i] == '+') {
        i += 1;
        int sub2 = parse_expr(i);
        seminodes.push_back({sub, sub2, OP_ADD, l, i});
        return seminodes.size() - 1;
    }
    return sub;
}

// ----------------- solver ------------------

// represents a set of values.
struct ValuesMod {
    ll sums[10];

    ValuesMod() {
        rep(i, 10) sums[i] = 0;
    }

    // apply a function to all values in the set.
    template <class OP>
    ValuesMod map(OP op) const {
        ValuesMod out;
        rep(k, K) {
            auto [nk, pos_] = op(pair<int, pair<int, int>>{k, {0, 0}});
            out.sums[nk % K] += sums[k];
        }
        return out;
    }

    // take the cross product of both sets and apply the given operation over the pairs.
    template <class OP>
    ValuesMod join(const ValuesMod &other, OP op) const {
        ValuesMod out;
        rep(i, K) rep(j, K) {
            auto [k, pos_] = op({i, {0, 0}}, {j, {0, 0}});
            out.sums[k % K] += sums[i] * other.sums[j];
        }
        return out;
    }

    // insert a value mod K into the set.
    void insert(pair<int, pair<int, int>> val) {
        sums[val.first % K] += 1;
    }

    // insert all values from another set into this set.
    void insert_all(const ValuesMod &other) {
        rep(k, K) sums[k] += other.sums[k];
    }

    void print() const {
        bool printed = false;
        cerr << "{";
        rep(k, K) if (sums[k] != 0) {
            if (printed) cerr << ",";
            cerr << " " << k << " x" << sums[k];
            printed = true;
        }
        if (printed) cerr << " ";
        cerr << "}";
    }

    void show() {
        cerr << ": ";
        print();
        cerr << endl;
    }

    ll count(int x) {
        return sums[x % K];
    }
};

// represents the values as an actual list of values
struct ValueList {
    vector<pair<int, pair<int, int>>> vals;

    ValueList() {}

    // apply a function to all values in the set.
    template <class OP>
    ValueList map(OP op) const {
        ValueList out = *this;
        for (auto &x : out.vals) x = op(x);
        return out;
    }

    // take the cross product of both sets and apply the given operation over the pairs.
    template <class OP>
    ValueList join(const ValueList &other, OP op) const {
        ValueList out;
        for (auto x : vals)
            for (auto y : other.vals) out.vals.push_back(op(x, y));
        return out;
    }

    // insert a value mod K into the set.
    void insert(pair<int, pair<int, int>> x) {
        vals.push_back(x);
    }

    // insert all values from another set into this set.
    void insert_all(const ValueList &other) {
        for (auto x : other.vals) vals.push_back(x);
    }

    void print() const {
        std::multimap<int, int> by_val;
        rep(i, vals.size()) {
            by_val.insert({vals[i].first % K, i});
        }

        bool printed = false;
        cerr << "{";
        for (auto [xk, i] : by_val) {
            auto [x, pos] = vals[i];
            if (printed) cerr << ",";
            cerr << " \"" << expr.substr(pos.first, pos.second - pos.first) << "\" = " << x;
            printed = true;
        }
        if (printed) cerr << " ";
        cerr << "}";
    }

    void show() {
        cerr << ": ";
        print();
        cerr << endl;
    }

    ll count(int x) {
        x %= K;
        ll ans = 0;
        for (auto [y, pos] : vals)
            if (y % K == x) ans += 1;
        return ans;
    }
};

#if DBG == 1
typedef ValueList ValueSet;
#else
typedef ValuesMod ValueSet;
#endif

struct Node {
    ValueSet left, right, any, all;
};

pair<int, pair<int, int>> add(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) { return {a.first + b.first, {a.second.first, b.second.second}}; }
pair<int, pair<int, int>> mul(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) { return {a.first * b.first, {a.second.first, b.second.second}}; }

Node evaluate(int id) {
    SemiNode &sn = seminodes[id];
    Node out;
    if (sn.ty == OP_LIT) {
        cerr << "evaluating node \"" << expr.substr(sn.l, sn.r - sn.l) << "\"" << endl;
        cerr << "  literal node" << endl;
        char *s = &expr[sn.l];
        int n = sn.r - sn.l;

        ValueSet cur;
        cur.insert({0, {sn.l, sn.l}});
        rep(i, n) {
            int digit = s[i] - '0';
            cur = cur.map([&](auto x) { return pair<int, pair<int, int>>{x.first * 10 + digit, {x.second.first, x.second.second + 1}}; });
            out.left.insert_all(cur);
        }

        out.all.insert_all(cur);

        ValueSet dp;
        ValueSet acc;
        rep(i, n) {
            int digit = s[i] - '0';

            // add a zero prefix to represent the number formed by the single digit `digit`
            // (unless its zero, in that case add it only to the accumulator)
            if (digit == 0) acc.insert({0, {sn.l + i, sn.l + i + 1}});
            else dp.insert({0, {sn.l + i, sn.l + i}});

            // multiply values of the dp by 10 and add digit value
            dp = dp.map([&](auto x) { return pair<int, pair<int, int>>{x.first * 10 + digit, {x.second.first, x.second.second + 1}}; });

            // add new numbers to the accumulator
            acc.insert_all(dp);

            if (i == n - 1) {
                out.right.insert_all(dp);
                if (digit == 0) out.right.insert({0, {sn.r - 1, sn.r}});
            }
        }
        out.any = acc;
    } else if (sn.ty == OP_PAREN) {
        out = evaluate(sn.lhs);
        cerr << "evaluating node \"" << expr.substr(sn.l, sn.r - sn.l) << "\"" << endl;
        cerr << "  paren node" << endl;
        out.all = out.all.map([](auto x) { return pair<int, pair<int, int>>{x.first, {x.second.first - 1, x.second.second + 1}}; });
        out.left = out.all;
        out.right = out.all;
        out.any.insert_all(out.all);
    } else {
        Node lhs = evaluate(sn.lhs);
        Node rhs = evaluate(sn.rhs);
        cerr << "evaluating node \"" << expr.substr(sn.l, sn.r - sn.l) << "\"" << endl;
        cerr << "  " << (sn.ty == OP_ADD ? "add" : "mul") << " node" << endl;

        out.left = lhs.all.join(rhs.left, (sn.ty == OP_ADD ? add : mul));
        out.left.insert_all(lhs.left);

        out.right = rhs.all.join(lhs.right, (sn.ty == OP_ADD ? add : mul));
        out.right.insert_all(rhs.right);

        out.any = lhs.right.join(rhs.left, (sn.ty == OP_ADD ? add : mul));
        out.any.insert_all(lhs.any);
        out.any.insert_all(rhs.any);

        out.all = lhs.all.join(rhs.all, (sn.ty == OP_ADD ? add : mul));
    }
    cerr << "  left: ";
    out.left.print();
    cerr << endl;
    cerr << "  right: ";
    out.right.print();
    cerr << endl;
    cerr << "  any: ";
    out.any.print();
    cerr << endl;
    cerr << "  all: ";
    out.all.print();
    cerr << endl;
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
