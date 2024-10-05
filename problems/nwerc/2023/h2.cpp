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

    vector<vector<int>> a;
    int one = 0;
    int two = 0;
    rep(i, n){
        int x;
        cin >> x;
        if(x == 1) one++;
        else if(x == 2) two++;
        else a.push_back({x});
    }

    if(one <= two){
        rep(_, one) a.push_back({2, 1});
        rep(_, two-one) a.push_back({2});
    }else{
        int total = one + two*2;
        rep(_, total/3){
            if(two) {
                a.push_back({1, 2}); two--; one--;
            }else{
                a.push_back({1,1,1}); one -= 3;
            }
        }
        if(total%3 == 2){
            if(two) {
                a.push_back({2}); two--;
            }else{
                a.push_back({1,1}); one -= 2;
            }
        }
        sort(a.begin(), a.end());
        if(total%3 == 1){
            if(a.size() > 0)
                a[0].push_back(1);
            else
                a.push_back({1});
        }
    }


    rep(j, (int)a.size()){
        cout << "(";
        rep(i, (int)a[j].size()){
            cout << a[j][i];
            if(i+1 < (int)a[j].size()) cout << "+";
        }
        cout << ")";
        if(j+1 < (int)a.size()) cout << "*";
    }
    cout << endl;

}