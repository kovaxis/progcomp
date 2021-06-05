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

typedef uint64_t u64;

struct Column {
    vector<u64> bits;
    int bitc;

    void band(const Column& rhs) {
        assert(this->bitc == rhs.bitc);
        rep(i, this->bits.size()) { this->bits[i] &= rhs.bits[i]; }
    }
    void copy_from(const Column& rhs) {
        assert(this->bitc == rhs.bitc);
        rep(i, this->bits.size()) { this->bits[i] = rhs.bits[i]; }
    }
    bool equals(const Column& rhs) const {
        assert(this->bitc == rhs.bitc);
        rep(i, this->bits.size()) {
            if (this->bits[i] != rhs.bits[i]) return false;
        }
        return true;
    }
    int count() const {
        int total = 0;
        for (u64 b : this->bits) {
            total += __builtin_popcountll(b);
        }
        return total;
    }
    void push(bool b) {
        if (this->bitc % 64 == 0) {
            this->bits.push_back(0);
        }
        this->bits[this->bitc / 64] |= ((u64)b) << (this->bitc % 64);
        this->bitc += 1;
    }
    bool get(int i) const {
        return (this->bits[i / 64] & (((u64)1) << (i % 64))) != 0;
    }
};

int n, m, p, g;
Column coins[60];

struct Goodcoin {
    Column* col;
    int count;
    int weight;
    u64 mask;
};

Goodcoin goodcoins[60];
int counts[60];
Column dcoins[70];

u64 max_mask = 0;
int max_mask_depth = 0;

void searchmax(int depth, u64 mask, int idx, const Column& col) {
    if (col.count() >= (n + 1) / 2) {
        if (depth > max_mask_depth) {
            max_mask = mask;
            max_mask_depth = depth;
        }
    } else {
        return;
    }
    rep(i, idx + 1, g) {
        dcoins[depth].copy_from(col);
        dcoins[depth].band(*goodcoins[i].col);
        u64 submask = mask | goodcoins[i].mask;
        searchmax(depth + goodcoins[i].weight, submask, i, dcoins[depth]);
    }
}

void print_bits(u64 b) {
    rep(i, m) {
        cout << (b & 1);
        b >>= 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> n >> m >> p;
    rep(i, n) {
        cin >> s;
        rep(j, m) {
            bool liked = (s[j] - '0') & 1;
            coins[j].push(liked);
            counts[j] += liked;
        }
        rep(j, 70) { dcoins[j].push(1); }
    }
    rep(j, m) {
        if (counts[j] >= (n + 1) / 2) {
            if (counts[j] == n / 2) {
                bool added = false;
                rep(k, g) {
                    if (goodcoins[k].count == n / 2 &&
                        coins[j].equals(*goodcoins[k].col)) {
                        goodcoins[k].weight += 1;
                        goodcoins[k].mask |= ((u64)1) << j;
                        added = true;
                        break;
                    }
                }
                if (added) continue;
            }
            goodcoins[g++] = {
                &coins[j],
                counts[j],
                1,
                ((u64)1) << j,
            };
        }
    }
    searchmax(0, 0, -1, dcoins[69]);
    print_bits(max_mask);
    cout << endl;
}
