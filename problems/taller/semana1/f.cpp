#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<string> lines;
    int max_len = 0;
    while (true) {
        string line;
        if (!getline(cin, line)) {
            break;
        }
        if (line.size() > max_len) {
            max_len = line.size();
        }
        lines.push_back(line);
    }

    for (int i = 0; i < max_len + 2; i++) {
        cout << '*';
    }
    cout << endl;
    bool bring_right = false;
    for (int i = 0; i < lines.size(); i++) {
        int leftover = max_len - lines[i].size();
        int align_left = (leftover + bring_right) / 2;
        if (leftover % 2 == 1) {
            bring_right = !bring_right;
        }
        cout << '*';
        for (int j = 0; j < align_left; j++) {
            cout << ' ';
        }
        cout << lines[i];
        for (int j = 0; j < leftover - align_left; j++) {
            cout << ' ';
        }
        cout << '*' << endl;
    }
    for (int i = 0; i < max_len + 2; i++) {
        cout << '*';
    }
    cout << endl;
}
