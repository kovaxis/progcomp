#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    int rem = 0;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        rem += n % 3;
        rem %= 3;
    }
    if (rem == 0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}
