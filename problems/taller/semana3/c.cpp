#include <bits/stdc++.h>
using namespace std;

struct part {
    double pos;
    double vel;
};

int check_crashes(const vector<part>& parts, double time) {
    double rightmost = -INFINITY;
    for (const part& p : parts) {
        double new_pos = p.pos + time * p.vel;
        if (p.vel > 0.) {
            if (new_pos > rightmost) {
                rightmost = new_pos;
            }
        } else {
            if (new_pos < rightmost) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<part> parts;
    parts.reserve(n);
    for (int i = 0; i < n; i++) {
        int p, v;
        cin >> p;
        cin >> v;
        parts.push_back({(double)p, (double)v});
    }

    double begin = 0.;
    double end = 0.;
    {
        double first_r_pos = 0.;
        double first_r_vel = 0.;
        for (int i = 0; i < n; i++) {
            if (parts[i].vel > 0.) {
                first_r_pos = parts[i].pos;
                first_r_vel = parts[i].vel;
                break;
            }
        }
        double first_l_pos = 0.;
        double first_l_vel = 0.;
        for (int i = n - 1; i >= 0; i--) {
            if (parts[i].vel < 0.) {
                first_l_pos = parts[i].pos;
                first_l_vel = parts[i].vel;
                break;
            }
        }
        if (first_r_vel == 0. || first_l_vel == 0. ||
            first_r_pos > first_l_pos) {
            cout << "-1" << endl;
            return 0;
        }
        end = (first_l_pos - first_r_pos) / (first_r_vel - first_l_vel);
    }

    for (int iter = 0; iter < 50; iter++) {
        double mid = (begin + end) / 2;
        if (check_crashes(parts, mid) > 0) {
            end = mid;
        } else {
            begin = mid;
        }
    }
    cout << setprecision(19) << ((begin + end) / 2) << endl;
}
