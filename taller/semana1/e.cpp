#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> planks;
    for (int i = 0; i < n; i++) {
        int len;
        cin >> len;
        planks.push_back(len);
    }
    sort(planks.begin(), planks.end());
    int max = 0;
    for (int i = planks.size() - 1; i >= 0; i--) {
        int size = planks.size() - i;
        if (planks[i] < size) {
            size = planks[i];
        }
        if (size > max) {
            max = size;
        }
    }
    cout << max << endl;
}
