#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    pair<signed char, signed char> char_pos[128] = {};
    {
        const string rows[3] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < rows[i].size(); j++) {
                char_pos[(int)rows[i][j]] = pair<int, int>(j, i);
            }
        }
    }

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        string reference;
        int count;
        vector<pair<int, string>> words;

        cin >> reference;
        cin >> count;
        words.reserve(count);
        for (int i = 0; i < count; i++) {
            string word;
            cin >> word;
            int dist = 0;
            for (int j = 0; j < reference.size(); j++) {
                dist +=
                    abs(char_pos[reference[j]].first - char_pos[word[j]].first);
                dist += abs(char_pos[reference[j]].second -
                            char_pos[word[j]].second);
            }
            words.push_back(pair<int, string>(dist, word));
        }
        sort(words.begin(), words.end());
        for (int i = 0; i < count; i++) {
            cout << words[i].second << ' ' << words[i].first << endl;
        }
    }
}
