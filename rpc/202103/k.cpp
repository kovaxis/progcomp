#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef struct {
    int x;
    int y;
    i64 w;
} Edge;

typedef struct {
    vector<int> cycle;
    vector<int> reach;
} Frame;

bool compare(Edge a, Edge b) { return a.x < b.x; }

typedef i64 long long int;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    cin >> n;
    cin >> m;
    cin >> q;

    vector<Edge> edges;
    edges.reserve(2 * m);
    for (int i = 0; i < m; i++) {
        int x, y;
        i64 w;
        cin >> x;
        cin >> y;
        cin >> w;
        x -= 1;
        y -= 1;
        edges.push_back(Edge{x, y, w});
        edges.push_back(Edge{
            y,
            x,
            w,
        });
    }
    sort(edges.begin(), edges.end(), compare);
    vector<int> adj;
    adj.reserve(n);
    {
        int cur = -1;
        for (int i = 0; i < 2 * m; i++) {
            while (edges[i].x > cur) {
                adj.push(i);
                cur += 1;
            }
        }
    }

    vector<int> visited;
    vector<Frame> stack;
    for (int q_i = 0; q_i < q; q_i++) {
        int a, b;
        cin >> a;
        cin >> b;
        a -= 1;
        b -= 1;

        // DFS
        visited.resize(n, -1);
        stack.clear();
        auto dfs = [&](int idx, int node, i64 dist) {
            if (node == b) {
                return dist;
            }
            if (stack.size() <= idx) {
                stack.push_back(Frame{vector<int>(), vector<int>()});
            }
            stack[idx].cycle.clear();
            stack[idx].reach.clear();
            if (visited[node] < 0) {
                // Not yet visited
                visited[node] = idx;
                for (int i = adj[node]; edges[i].x == node; i++) {
                    dfs(idx + 1, edges[i].y, dist ^ edges[i].w);
                }
                visited[node] = -1;
            } else {
                // Already visited
                stack[visited[node]].cycle.push_back(dist);
            }
        };
        dfs(0, a, 0);

        stack.clear();
        stack.push_back(a);
        while (stack.size() > 0) {
            int node = stack.pop_back();
            if (visited[node] == -1) {
                visited[node] = -2;
                for (int i = adj[a]; edges[i].x == a; i++) {
                    stack.push_back(edges[i].y);
                }
            }
        }
    }
}
