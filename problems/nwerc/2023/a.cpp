#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, s;
    cin >> n >> s;

    vector<ll> A(n);
    for(int i = 0; i<n; i++){
        cin>>A[i];
    }

    if(s <= 2){
        cout<<min(n, s)<<"\n";
        return 0;
    }

    vector<ll> Acc(n, 0);
    vector<ll> uno(n, 0);
    vector<ll> dos(n, 0);

    sort(A.begin(), A.end());

    Acc[0] = A[0]/3;
    if(A[0]%3 == 1){
        uno[0]++;
    }
    if(A[0]%3 == 2){
        dos[0]++;
    }

    for(int i = 1; i<n; i++){
        Acc[i] = Acc[i-1] + A[i]/3;
        uno[i] = uno[i-1];
        dos[i] = dos[i-1];
        if(A[i]%3 == 1){
            uno[i]++;
        }
        if(A[i]%3 == 2){
            dos[i]++;
        }
    }

    int inf = 0;
    int sup = n;

    while(inf != sup){
        int mid = (inf + sup + 1)/2;
        int hasta = mid - 3;
        if(hasta < 0){
            inf = mid;
            continue;
        }
        ll accx = Acc[hasta];
        ll unox = uno[hasta];
        ll dosx = dos[hasta];

        ll x = min(unox, dosx);
        accx = accx + x;
        unox = unox - x;
        dosx = dosx - x;
        accx = accx + dosx + (unox + 1LL)/2LL;
        if(accx <= s - 2LL){
            inf = mid;
        }
        else{
            sup = mid - 1;
        }
    }

    cout<<inf<<"\n";

    return 0;
}