#include "point.cpp"

template <class OP>
void all_pair_points(vector<P> &ps, OP op) {
    int N = ps.size();
    sort(ps.begin(), ps.end(), [](P a, P b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    vector<pair<int, int>> ss;
    rep(i, N) rep(j, N) if (i != j) ss.push_back({i, j});
    stable_sort(ss.begin(), ss.end(), [&](auto a, auto b) {
        return (ps[a.second] - ps[a.first]).angle_lt(ps[b.second] - ps[b.first]);
    });
    vector<int> p(N);
    rep(i, N) p[i] = i;
    for (auto [i, j] : ss) {
        op(p[i], p[j], N - p[i]);
        swap(ps[p[i]], ps[p[j]]);
        swap(p[i], p[j]);
    }
}
