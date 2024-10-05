#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, n) cin >> a[i];

    multiset<pair<int,vector<int>>> s;

    rep(i, n){
        vector<int> v(1, a[i]);
        s.insert({a[i],v});
    }


    while(s.size() > 1){
        auto it1 = s.begin();
        auto [sum, nums] = *it1;
        if(sum > 1) break;

        s.erase(it1);
        auto it2 = s.begin();
        auto [sum2, nums2] = *it2;
        s.erase(it2);

        sum += sum2;
        for(int x : nums2) nums.push_back(x);
        s.insert({sum, nums});
    }

    int cnt = 0;
    for(auto [sum, nums] : s){
        cout << "(";
        rep(i, nums.size()){
            cout << nums[i];
            if(i < nums.size()-1) cout << "+";
        }
        cout << ")";
        cnt++;
        if(cnt < s.size()) cout << "*";
    }
    cout << endl;

}