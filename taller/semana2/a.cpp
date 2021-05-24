#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int num;
    cin >> num;
    int out = 0;
    while (num != 0) {
        out <<= 1;
        out |= num & 1;
        num >>= 1;
    }
    cout << out << endl;
}
