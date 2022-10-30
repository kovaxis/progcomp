#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

struct Rule {
    int l, r, k;
};

int N, M, P;
umap<int, Rule> rules;

void impossible() {
    cout << "None\n";
    exit(0);
}

int mod(int x) {
    return (x % P + P) % P;
}

void add_rule(Rule rule) {
    if (!rules.count(rule.r)) {
        rules[rule.r] = rule;
        return;
    }
    Rule &prev = rules[rule.r];
    if (prev.l < rule.l) {
        // adding small rule
        // split previous rule
        swap(prev, rule);
    } else if (prev.l > rule.l) {
        // adding big rule
        // split this rule
    } else {
        if (rule.k != prev.k) impossible();
        // duplicate rules
        return;
    }
    // split `rule`
    // `prev` is small rule
    rule.r = prev.l - 1;
    rule.k = mod(rule.k - prev.k);
    return add_rule(rule);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> P;
    rep(i, M) {
        int l, r, k;
        cin >> l >> r >> k;
        add_rule({l - 1, r - 1, k});
    }

    vector<int> acc(N + 1), ans(N);
    rep(i, N) {
        if (rules.count(i)) {
            Rule &rule = rules[i];
            int prevsum = mod(acc[rule.r] - acc[rule.l]);
            ans[i] = mod(rule.k - prevsum);
        }
        acc[i + 1] = mod(acc[i] + ans[i]);
    }

    rep(i, N) cout << ans[i] << " \n"[i == N - 1];
}
