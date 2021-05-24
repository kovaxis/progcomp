#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int count;
    string stones;
    cin >> count;
    stones.reserve(count);
    cin >> stones;

    char last = ' ';
    int conc = 0;
    int to_remove = 0;
    for (int i = 0; i < stones.length(); i++) {
        if (stones[i] == last) {
            conc += 1;
        } else {
            if (conc > 1) {
                to_remove += conc - 1;
            }
            conc = 1;
            last = stones[i];
        }
    }
    if (conc > 1) {
        to_remove += conc - 1;
    }

    cout << to_remove;
}
