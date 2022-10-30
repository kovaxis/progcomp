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

struct Link {
    int pos[3][2];
};

pair<vector<int>, umap<int, int>> compress[3];
vector<Link> links;
pair<int, int> axisrange[3][3];
vector<int> axisoverlap[3][3];
int link_counts[3];

void intersect(pair<int, int>& a, pair<int, int> b) {
    a = {max(a.first, b.first), min(a.second, b.second)};
}

void unite(pair<int, int>& a, pair<int, int> b) {
    if (a.first > a.second)
        a = b;
    else if (b.first <= b.second)
        a = {min(a.first, b.first), max(a.second, b.second)};
}

bool is_subset(pair<int, int> sub, pair<int, int> sup) {
    return sub.first > sup.first && sub.second < sup.second ||
           sub.second < sub.first && sup.first <= sup.second;
}

bool do_axes_match(int ax0, int ax1, int ax2) {
    if (!is_subset(axisrange[ax0][ax0], axisrange[ax1][ax0])) return false;
    if (!is_subset(axisrange[ax1][ax1], axisrange[ax0][ax1])) return false;
    for (auto& link : links) {
        if (link.pos[ax1][0] != link.pos[ax1][1]) continue;
        int cross = axisoverlap[ax0][ax2][link.pos[ax2][0]] +
                    axisoverlap[ax0][ax2][link.pos[ax2][1]];
        if (cross != link_counts[ax0]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        // read links
        int N;
        cin >> N;
        links.resize(N);
        for (auto& link : links) {
            rep(j, 2) rep(k, 3) cin >> link.pos[k][j];
            rep(k, 3) if (link.pos[k][0] > link.pos[k][1])
                swap(link.pos[k][0], link.pos[k][1]);
        }

        // compress
        rep(k, 3) {
            compress[k].first.clear();
            compress[k].second.clear();
        }
        for (auto& link : links)
            rep(k, 3) rep(j, 2) compress[k].first.push_back(link.pos[k][j]);
        int M[3];
        rep(k, 3) {
            sort(compress[k].first.begin(), compress[k].first.end());
            M[k] = 0;
            for (int x : compress[k].first)
                if (!compress[k].second.count(x))
                    compress[k].second[x] = M[k]++;
        }
        for (auto& link : links) {
            rep(k, 3) rep(j, 2) link.pos[k][j] =
                compress[k].second[link.pos[k][j]];
        }

        // preprocess link axes
        rep(k0, 3) rep(k1, 3) {
            if (k0 == k1) {
                axisrange[k0][k1] = {INT32_MAX, INT32_MIN};
            } else {
                axisrange[k0][k1] = {INT32_MIN, INT32_MAX};
                axisoverlap[k0][k1].clear();
                axisoverlap[k0][k1].resize(M[k1]);
            }
        }
        rep(k, 3) link_counts[k] = 0;
        for (auto& link : links) {
            int axis;
            rep(k, 3) if (link.pos[k][0] == link.pos[k][1]) axis = k;
            rep(k, 3) {
                if (k == axis) {
                    unite(axisrange[axis][k], {link.pos[k][0], link.pos[k][1]});
                } else {
                    intersect(axisrange[axis][k],
                              {link.pos[k][0], link.pos[k][1]});
                    axisoverlap[axis][k][link.pos[k][0]] += 1;
                    axisoverlap[axis][k][link.pos[k][1]] -= 1;
                }
            }
            link_counts[axis] += 1;
        }
        rep(axis, 3) rep(k, 3) {
            int acc = 0;
            for (int& active : axisoverlap[axis][k])
                acc += active, active = acc;
        }

        // find a pivot axis
        bool ok = false;
        rep(k0, 3) {
            int k1 = (k0 + 1) % 3, k2 = (k0 + 2) % 3;
            if (link_counts[k0] == 0 || link_counts[k1] + link_counts[k2] == 0)
                continue;
            ok = ok || do_axes_match(k0, k1, k2) && do_axes_match(k0, k2, k1);
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
}
