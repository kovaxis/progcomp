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

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

uint64_t splitmix64(uint64_t* x) {
    uint64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}
struct Hash {
    size_t operator()(const int& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

template <class T, class U>
using umap = unordered_map<T, U, Hash>;

int N;
vector<int> boxes;
vector<int> candies;
umap<ll, bool> known_cmps;

int raw_cmp(int a, int b, int c, int d) {
    cout << "? " << a << " " << b << " " << c << " " << d << endl;
    char cmp;
    cin >> cmp;
    if (cmp == '<')
        return -1;
    else if (cmp == '>')
        return 1;
    else
        return 0;
}

void add_known_cmp(int little, int big) {
    int mn = min(little, big), mx = max(little, big);
    ll code = (ll)mx * N + (ll)mn;
    known_cmps[code] = little < big;
}

bool cmp_boxes(const int& a, const int& b) {
    {
        int mn = min(a, b), mx = max(a, b);
        ll code = (ll)mx * N + (ll)mn;
        if (known_cmps.count(code)) {
            bool lt = known_cmps[code];
            if (a > b) lt = !lt;
            return lt;
        }
    }
    uniform_int_distribution<> getrand(1, N);
    while (true) {
        int c = a, d = a;
        while (c == a || c == b) c = getrand(rng);
        while (d == a || d == b || d == c) d = getrand(rng);
        int raw_cmps[3] = {raw_cmp(a, b, c, d), raw_cmp(a, c, b, d),
                           raw_cmp(a, d, b, c)};
        int let_cmps[4][3] = {{1, 1, 1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}};
        int let_scores[4] = {0, 0, 0, 0};
        rep(i, 4) rep(j, 3) let_scores[i] += raw_cmps[j] * let_cmps[i][j];
        int minscore = 0, mincount = 0;
        int maxscore = 0, maxcount = 0;
        rep(i, 4) {
            if (let_scores[i] < minscore)
                minscore = let_scores[i], mincount = 0;
            if (let_scores[i] <= minscore) mincount += 1;
            if (let_scores[i] > maxscore)
                maxscore = let_scores[i], maxcount = 0;
            if (let_scores[i] >= maxscore) maxcount += 1;
        }
        int nums[4] = {a, b, c, d};
        if (mincount == 1) {
            rep(i, 4) if (minscore == let_scores[i]) {
                rep(j, 4) if (i != j) add_known_cmp(nums[i], nums[j]);
                break;
            }
        }
        if (maxcount == 1) {
            rep(i, 4) if (maxscore == let_scores[i]) {
                rep(j, 4) if (i != j) add_known_cmp(nums[j], nums[i]);
                break;
            }
        }
        if (mincount == 1 && minscore == let_scores[0]) return true;
        if (maxcount == 1 && maxscore == let_scores[0]) return false;
        if (mincount == 1 && minscore == let_scores[1]) return false;
        if (maxcount == 1 && maxscore == let_scores[1]) return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T >> N;
    string verdict;
    rep(t, T) {
        known_cmps.clear();
        boxes.resize(N);
        candies.resize(N);
        rep(i, N) boxes[i] = i + 1;
        sort(boxes.begin(), boxes.end(), cmp_boxes);
        rep(i, N) candies[boxes[i] - 1] = i + 1;
        cout << "!";
        rep(i, N) cout << " " << candies[i];
        cout << endl;
        cin >> verdict;
        if (verdict != "OK") return 0;
    }
}
