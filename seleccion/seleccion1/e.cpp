#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<int>& give_to, vector<vector<int>>& vertices, int m, int idx) {
    int n = vertices.size();
    int a_owner = give_to[idx];
    for (int j : vertices[idx]) {
        if (give_to[j] == 0) {
            // Decide owners
            give_to[j] = -a_owner;
            if (!dfs(give_to, vertices, m, j)) {
                return false;
            }
        } else if (give_to[j] == a_owner) {
            // Cannot split this edge :(
            return false;
        }
    }
    return true;
}

void print_set(vector<int>& give_to, int user) {
    int n = give_to.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (give_to[i] == user) {
            count += 1;
        }
    }
    cout << count << endl;
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (give_to[i] == user) {
            if (first) {
                first = false;
            } else {
                cout << " ";
            }
            cout << (i + 1);
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    cin >> m;
    vector<vector<int>> vertices;
    vertices.reserve(n);
    for (int i = 0; i < n; i++) {
        vector<int> vec;
        vertices.push_back(vec);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a;
        cin >> b;
        vertices[a - 1].push_back(b - 1);
        vertices[b - 1].push_back(a - 1);
    }
    vector<int> give_to(n, 0);
    for (int i = 0; i < n; i++) {
        if (give_to[i] == 0 && vertices[i].size() > 0) {
            // Start with positive owner
            give_to[i] = 1;
            if (!dfs(give_to, vertices, m, i)) {
                cout << "-1" << endl;
                return 0;
            }
        }
    }
    // Print
    print_set(give_to, 1);
    print_set(give_to, -1);
}
