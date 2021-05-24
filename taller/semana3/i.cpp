#include <bits/stdc++.h>
using namespace std;

struct Discount {
    long long pos;
    long long base;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> tunings;
    tunings.reserve(n);
    for (int i = 0; i < n; i++) {
        long long t;
        cin >> t;
        tunings.push_back(t);
    }

    // Process tunings
    sort(tunings.begin(), tunings.end());
    vector<long long> diffs;
    diffs.reserve(n);
    for (int i = 1; i < n; i++) {
        diffs.push_back(tunings[i] - tunings[i - 1]);
        // cout << "tuning " << (i - 1) << " to " << i << ": "
        //     << (tunings[i] - tunings[i - 1]) << "diff" << endl;
    }
    sort(diffs.begin(), diffs.end());
    vector<Discount> discounts;
    discounts.reserve(n);
    Discount last = {0, 0};
    for (int i = 0; i < diffs.size(); i++) {
        long long ddiff = diffs[i] - last.pos;
        Discount disc = {
            diffs[i],
            last.base + ddiff * i,
        };
        // cout << "discount for diff " << i << ": " << disc.base << " + (x - "
        //     << disc.pos << ") * " << (i + 1) << endl;
        discounts.push_back(disc);
        last = disc;
    }

    int qs;
    cin >> qs;
    for (int q = 0; q < qs; q++) {
        long long l, r;
        cin >> l;
        cin >> r;
        // Answer question
        long long offset = l;
        long long range = r - l + 1;
        // cout << "question " << q << ": " << range << " pitches" << endl;
        long long pitches = n * range;
        // cout << "  base answer: " << pitches << " pitches" << endl;
        int idx = upper_bound(discounts.begin(), discounts.end(), range,
                              [](long long range, Discount& d) {
                                  return range < d.pos;
                              }) -
                  discounts.begin();
        if (idx != 0) {
            Discount& disc = discounts[idx - 1];
            pitches -= disc.base + (range - disc.pos) * idx;
            // cout << "  using discount " << (idx - 1) << ": " << disc.base
            //     << " + (x - " << disc.pos << ") * " << idx << endl;
            // cout << "  discounting " << (disc.base + (range - disc.pos) *
            // idx)
            //     << "pitches" << endl;
        }
        cout << pitches << endl;
    }
}
