#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        if (t > 0) {
            cout << endl;
        }

        int n;
        cin >> n;
        unordered_map<string, int> foreign_to_int;
        vector<string> int_to_foreign;
        unordered_map<string, int> native_to_int;
        vector<string> int_to_native;
        vector<pair<unordered_set<int>, unordered_set<int>>> pizzas;
        pizzas.reserve(n);
        for (int i = 0; i < n; i++) {
            string word;
            int count;
            cin >> word;
            // Foreign
            cin >> count;
            unordered_set<int> pizza_foreign;
            for (int j = 0; j < count; j++) {
                cin >> word;
                int id;
                if (foreign_to_int.count(word) == 0) {
                    id = int_to_foreign.size();
                    foreign_to_int[word] = id;
                    int_to_foreign.push_back(word);
                } else {
                    id = foreign_to_int[word];
                }
                pizza_foreign.insert(id);
            }
            // Native
            cin >> count;
            unordered_set<int> pizza_native;
            for (int j = 0; j < count; j++) {
                cin >> word;
                int id;
                if (native_to_int.count(word) == 0) {
                    id = int_to_native.size();
                    native_to_int[word] = id;
                    int_to_native.push_back(word);
                } else {
                    id = native_to_int[word];
                }
                pizza_native.insert(id);
            }
            pizzas.push_back(pair<unordered_set<int>, unordered_set<int>>(
                pizza_foreign, pizza_native));
        }

        // For each ingredient, intersect all of their possible analogues
        // Both native -> foreign and foreign -> native
        unordered_map<int, unordered_set<int>> foreign_to_native;
        unordered_map<int, unordered_set<int>> native_to_foreign;
        for (int i = 0; i < n; i++) {
            for (auto& foreign : pizzas[i].first) {
                if (foreign_to_native.count(foreign) == 0) {
                    // New mapping
                    foreign_to_native.insert({foreign, pizzas[i].second});
                } else {
                    // Intersect this mapping
                    unordered_set<int>& mapping = foreign_to_native[foreign];
                    auto next = mapping.begin();
                    while (next != mapping.end()) {
                        if (pizzas[i].second.count(*next) == 0) {
                            // Remove
                            next = mapping.erase(next);
                        } else {
                            // Keep
                            ++next;
                        }
                    }
                }
            }
            for (auto& native : pizzas[i].second) {
                if (native_to_foreign.count(native) == 0) {
                    // New mapping
                    native_to_foreign.insert({native, pizzas[i].first});
                } else {
                    // Intersect this mapping
                    unordered_set<int>& mapping = native_to_foreign[native];
                    auto next = mapping.begin();
                    while (next != mapping.end()) {
                        if (pizzas[i].first.count(*next) == 0) {
                            // Remove
                            next = mapping.erase(next);
                        } else {
                            // Keep
                            ++next;
                        }
                    }
                }
            }
        }

        // Now make sure that all foreign -> native mappings have an equivalent
        // native -> foreign mapping
        for (auto& item : foreign_to_native) {
            int foreign = item.first;
            auto native = item.second.begin();
            while (native != item.second.end()) {
                if (native_to_foreign[*native].count(foreign) == 0) {
                    // Remove it
                    native = item.second.erase(native);
                } else {
                    // Keep it
                    ++native;
                }
            }
        }

        vector<pair<string, string>> out;
        for (auto& item : foreign_to_native) {
            int foreign = item.first;
            for (auto& native : item.second) {
                out.push_back({int_to_foreign[foreign], int_to_native[native]});
            }
        }
        sort(out.begin(), out.end());
        for (auto& p : out) {
            cout << "(" << p.first << ", " << p.second << ")" << endl;
        }
    }
}
