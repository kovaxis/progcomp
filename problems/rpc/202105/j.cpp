#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

struct Tap {
    int t;
    int min;
    int max;
};

struct Recipe {
    int t;
    int flow;
};

int k;
Tap taps[10];

int conf[10];

bool tap_lt_temp(const Tap& a, const Tap& b) { return a.t < b.t; }

void printconf() {
    double flow = 0.;
    double heat = 0.;
    rep(i, k) {
        flow += conf[i];
        heat += conf[i] * taps[i].t;
        cout << conf[i] << " ";
    }
    cout << "| flow = " << flow << ", temp = " << (heat / flow) << endl;
}

bool check(int ttemp, int tflow) {
    int flow, heat;

    flow = 0;
    rep(i, k) {
        conf[i] = taps[i].min;
        flow += taps[i].min;
    }
    cout << "minflow: ";
    printconf();
    if (flow > tflow) {
        cout << "too much forced flow" << endl;
        return false;
    }

    rep(i, k) {
        if (flow >= tflow) {
            break;
        }
        int addflow = min(taps[i].max - conf[i], tflow - flow);
        conf[i] += addflow;
        flow += addflow;
    }
    heat = 0;
    rep(i, k) { heat += conf[i] * taps[i].t; }
    cout << "exactflow: ";
    printconf();
    if (flow < tflow) {
        cout << "not enough potential flow" << endl;
        return false;
    }
    if (heat > flow * ttemp) {
        cout << "too much forced heat" << endl;
        return false;
    }

    int from = 0;
    int to = k - 1;
    while (heat < flow * ttemp && from < to) {
        // turn up heat
        int needed = flow * ttemp - heat;
        int maxmove = min(taps[to].max - conf[to], conf[from] - taps[from].min);
        int movetemp = taps[to].t - taps[from].t;
        conf[to] += maxmove;
        conf[from] -= maxmove;
        heat += maxmove * movetemp;
        cout << "moved " << maxmove << " from " << from << " to " << to << ": ";
        printconf();
        if (conf[to] == taps[to].max) {
            to -= 1;
        }
        if (conf[from] == taps[from].min) {
            from += 1;
        }
    }
    if (heat < flow * ttemp) {
        cout << "not enough temp" << endl;
        return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k;
    rep(i, k) { cin >> taps[i].t >> taps[i].min >> taps[i].max; }
    sort(&taps[0], &taps[k], tap_lt_temp);
    int rs;
    cin >> rs;
    rep(r, rs) {
        int ttemp, tflow;
        cin >> ttemp >> tflow;
        if (check(ttemp, tflow)) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
        cout << endl;
    }
}
