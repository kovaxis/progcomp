#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;

    while (t--) {

        int n, m;
        cin >> n >> m;

        vector<ii> edges(m);
        vector<int> degree(n);

        for (int i = 0; i < m; i++) {
            cin >> edges[i].first >> edges[i].second;
            edges[i].first--;
            edges[i].second--;
            degree[edges[i].first]++;
            degree[edges[i].second]++;
        }

        int bacan = -1;
        for (int i = 0; i < n; i++) {
            if (degree[i] < n - 1) {
                bacan = i;
                break;
            }
        }

        if (bacan != -1) {
            cout << "2\n";
            for (int i = 0; i < m; i++) {
                if (edges[i].first == bacan || edges[i].second == bacan) {
                    cout << "2 ";
                } else {
                    cout << "1 ";
                }
            }
            cout << "\n";
            continue;
        }

        cout << "3\n";
        for (int j = 0; j < m; j++) {
            bool a = edges[j].first == 0 || edges[j].second == 0;
            bool b = edges[j].first == 1 || edges[j].second == 1;
            if (a == b) {
                // amarillo
                cout << "1 ";
            } else {
                if (a) {
                    cout << "2 ";
                } else {
                    cout << "3 ";
                }
            }
        }
        cout << "\n";
    }
    return 0;
}