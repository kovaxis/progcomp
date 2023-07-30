#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    stack<int> s;
    vector<pair<int, int>> resp;
    rep(i, n) {
        int x;
        cin >> x;
        s.push(x);
    }
    stack<int> s3;
    while (!s.empty()) {
        int x = s.top();
        s.pop();
        resp.push_back({1, 2});
        int cnt = 0;
        while (!s3.empty() && s3.top() < x) {
            s.push(s3.top());
            s3.pop();
            resp.push_back({3, 1});
            cnt++;
        }
        resp.push_back({2, 3});
        s3.push(x);
        while (cnt--) {
            s3.push(s.top());
            s.pop();
            resp.push_back({1, 3});
        }
    }

    cout << resp.size() << endl;
    for (pair<int, int> p : resp)
        cout << p.first << " " << p.second << endl;
}