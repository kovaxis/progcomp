#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    cin >> m;

    long long total = 0;
    vector<int> songs;
    for (int i = 0; i < n; i++) {
        int orig, comp;
        cin >> orig;
        cin >> comp;
        total += (long long)orig;
        songs.push_back(comp - orig);
    }
    sort(songs.begin(), songs.end());

    int song_count = 0;
    for (int dec : songs) {
        if (total <= m) {
            break;
        }
        song_count += 1;
        total += (long long)dec;
    }
    if (total <= m) {
        cout << song_count << endl;
    } else {
        cout << "-1" << endl;
    }
}
