// incomplete (wrong answer)

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

uint64_t splitmix64(uint64_t* x) {
    uint64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

struct Hash {
    size_t operator()(const string& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t s = RAND;
        for (char c : x) {
            s ^= c;
            splitmix64(&s);
        }
        return s;
    }
};

template <class T, class U>
using umap = unordered_map<T, U, Hash>;

umap<string, int> namemap;
int next_name;

using algoset = bitset<1024>;

struct Teacher {
    vector<int> list;
    algoset mask;
};

int N;
vector<Teacher> teachers;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string tmps;
    cin >> N;
    teachers.resize(N);
    rep(i, N) {
        int A;
        cin >> A;
        teachers[i].list.resize(A);
        rep(j, A) {
            cin >> tmps;
            int k = next_name;
            if (namemap.count(tmps)) {
                k = namemap[tmps];
            } else {
                namemap[tmps] = next_name++;
            }
            teachers[i].list[j] = k;
            teachers[i].mask.set(k);
        }
        // cerr << "teacher " << i + 1 << ": " << teachers[i].mask << endl;
    }

    sort(teachers.begin(), teachers.end(),
         [](Teacher& a, Teacher& b) { return a.list.size() > b.list.size(); });

    vector<int> perm;
    int ans = 0;
    rep(i, N) {
        Teacher& teacher = teachers[i];
        int m = (teacher.list.size() + 1) / 2;
        perm.resize(m + 1);
        rep(j, m) perm[j] = j;
        perm[m] = teacher.list.size();
        while (true) {
            algoset submask;
            rep(j, m) submask.set(teacher.list[perm[j]]);

            bool wrong = false;
            rep(j, i) wrong = wrong || (teachers[j].mask & submask) == submask;
            ans += !wrong;

            // advance to the next submask
            int j = 0;
            while (j < m) {
                perm[j] += 1;
                if (perm[j] >= perm[j + 1])
                    perm[j] = 0;
                else
                    break;
                j += 1;
            }
            if (j >= m) break;
        }
    }
    cout << ans << endl;
}
