#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int num;
    while (cin >> num) {
        int sum = 0;
        do {
            sum += num;
        } while (cin.peek() == ' ' && (cin >> num));
        cout << (sum / 2) << endl;
    }
    return 0;
}