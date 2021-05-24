#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l;
    cin >> n;
    cin >> l;
    vector<int> lants;
    lants.reserve(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        lants.push_back(x);
    }
    sort(lants.begin(), lants.end());
    int last = 0;
    double max_dist = 0;
    for (int i = 0; i < n; i++) {
        double dist = lants[i] - last;
        if (i > 0) {
            dist *= 0.5;
        }
        max_dist = max(max_dist, dist);
        last = lants[i];
    }
    max_dist = max(max_dist, (double)(l - last));
    cout << fixed << setw(10) << setprecision(10) << max_dist << endl;
}
