#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

bool grid[501][501][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    rep(i, 501) rep(j, 501) rep(k, 2) grid[i][j][k] = false;

    queue<pair<pair<int,int>,int>> q;
    q.push({{0,0},0});
    q.push({{0,0},1});
    while(!q.empty()){
        auto [coord, t] = q.front();
        auto [x, y] = coord;
        q.pop();
        if(x < 0 || x >= n) continue;
        if(y < 0 || y >= n) continue;

        if(grid[x][y][t]) continue;
        grid[x][y][t] = true;

        if(t == 0){
            q.push({{x+a,y+b}, 1});
            q.push({{x-a,y+b}, 1});
            q.push({{x+a,y-b}, 1});
            q.push({{x-a,y-b}, 1});
            q.push({{x+b,y+a}, 1});
            q.push({{x-b,y+a}, 1});
            q.push({{x+b,y-a}, 1});
            q.push({{x-b,y-a}, 1});
        }else{
            q.push({{x+c,y+d}, 0});
            q.push({{x-c,y+d}, 0});
            q.push({{x+c,y-d}, 0});
            q.push({{x-c,y-d}, 0});
            q.push({{x+d,y+c}, 0});
            q.push({{x-d,y+c}, 0});
            q.push({{x+d,y-c}, 0});
            q.push({{x-d,y-c}, 0});
        }

    }

    int cnt = 0;
    rep(i, n){ 
        rep(j, n){
            if(grid[i][j][0] || grid[i][j][1])
                cnt++;
        }
    }
    cout << cnt << endl;

}