#include "../../implementation/unordered_map.cpp"
#include "../test.h"

int main() {
    int N = 1e4;
    int M = 1e4, Q = 10;

    unordered_map<int, int> i_std;
    umap<int, int> i_umap;
    Map<int> i_arr;
    i_arr.recap(N);

    vector<pair<int, int>> pairs;
    rep(j, M) {
        int k = random_int(0, N), v = random_int(-1e9, 1e9);
        pairs.push_back({k, v});
        i_std[k] = v;
        i_umap[k] = v;
        i_arr[k] = v;

        rep(q, Q) {
            int i = random_int(0, pairs.size());
            int k = pairs[i].first;
            int v = i_std[k];
            assert(i_umap[k] == v);
            assert(i_arr[k] == v);
        }
    }

    cerr << "all ok" << endl;
}
