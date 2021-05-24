#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    getline(cin, line);
    vector<int> stack;
    vector<pair<int, int>> pairs;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '(') {
            stack.push_back(i);
        } else if (line[i] == ')') {
            if (stack.size() > 0) {
                int opening = stack[stack.size() - 1];
                stack.pop_back();
                pairs.push_back({opening, i});
            }
        }
    }
    sort(pairs.begin(), pairs.end());
    vector<bool> keep_chars(line.size(), true);
    string out;
    for (int i = 1; i < (1 << pairs.size()); i++) {
        for (int j = 0; j < line.size(); j++) {
            keep_chars[j] = true;
        }
        for (int j = 0; j < pairs.size(); j++) {
            if ((i & (1 << j)) != 0) {
                // Remove
                pair<int, int>& p = pairs[pairs.size() - j - 1];
                keep_chars[p.first] = false;
                keep_chars[p.second] = false;
            }
        }
        out.clear();
        for (int j = 0; j < line.size(); j++) {
            if (keep_chars[j]) {
                out.push_back(line[j]);
            }
        }
        cout << out << endl;
    }
}
