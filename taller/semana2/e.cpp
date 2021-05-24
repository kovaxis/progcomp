#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

void bucket_fill(vector<bool>& img, int w, int h, int x, int y) {
    img[y * w + x] = false;
    if (x > 0 && img[y * w + x - 1]) {
        bucket_fill(img, w, h, x - 1, y);
    }
    if (x < w - 1 && img[y * w + x + 1]) {
        bucket_fill(img, w, h, x + 1, y);
    }
    if (y > 0 && img[(y - 1) * w + x]) {
        bucket_fill(img, w, h, x, y - 1);
    }
    if (y < h - 1 && img[(y + 1) * w + x]) {
        bucket_fill(img, w, h, x, y + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<bool> img;
    string line;
    for (int i = 0; true; i++) {
        int h, w;
        if (!(cin >> h)) {
            break;
        }
        cin >> w;
        img.clear();
        img.reserve(w * h);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                char c;
                cin >> c;
                img.push_back(c == '-');
            }
            getline(cin, line);
        }
        // Process image
        int idx = 0;
        int stars = 0;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (img[idx]) {
                    // Found star
                    bucket_fill(img, w, h, x, y);
                    stars += 1;
                }
                idx += 1;
            }
        }
        cout << "Case " << (i + 1) << ": " << stars << endl;
    }
}
