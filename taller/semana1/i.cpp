#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    unordered_map<string, int> word_to_num;
    unordered_map<int, string> num_to_word;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "def") {
            string name;
            int val;
            cin >> name;
            cin >> val;
            if (word_to_num.count(name) != 0) {
                num_to_word.erase(word_to_num[name]);
            }
            word_to_num[name] = val;
            num_to_word[val] = name;
        } else if (cmd == "calc") {
            string word;
            string op;
            int sum = 0;
            bool unknown = false;
            int sign = 1;
            while (true) {
                word.clear();
                cin >> word;
                cout << word << " ";
                if (word_to_num.count(word) != 0) {
                    sum += sign * word_to_num[word];
                } else {
                    unknown = true;
                }
                op.clear();
                cin >> op;
                cout << op << " ";
                if (op == "+") {
                    sign = 1;
                } else if (op == "-") {
                    sign = -1;
                } else if (op == "=") {
                    break;
                }
            }
            if (num_to_word.count(sum) == 0) {
                unknown = true;
            }
            if (unknown) {
                cout << "unknown" << endl;
            } else {
                cout << num_to_word[sum] << endl;
            }
        } else if (cmd == "clear") {
            word_to_num.clear();
            num_to_word.clear();
        }
    }
}
