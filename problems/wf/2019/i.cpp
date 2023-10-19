#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

const char MOVE = 'm';
const char TURN = 'l';
const char IF = 'i';
const char UNTIL = 'u';
const char CALL = 'c';
const char BARRIER = 4;

const int UNKNOWN = -1;
const int INF_LOOP = -2;

struct Op {
    char t;
    int arg[3];
};

struct Program {
    int base, n;
    string name;
    vector<Op> ops;
};

int decode_dir(char d) {
    if (d == 'e') return 0;
    if (d == 's') return 1;
    if (d == 'w') return 2;
    if (d == 'n') return 3;
    assert(false);
}

int H, W, D, E;
vector<string> mp;
vector<Program> A;
int An;
int byname[26];

bool barrier_at(int i, int j) {
    if (i < 0 || i >= H || j < 0 || j >= W) return true;
    return mp[i][j] == '#';
}

struct State {
    int8_t i, j, d;

    int id() const {
        int id = 0;
        id *= H;
        id += i;
        id *= W;
        id += j;
        id *= 4;
        id += d;
        return id;
    }

    void move() {
        if (d == 0) j += 1;
        else if (d == 1) i += 1;
        else if (d == 2) j -= 1;
        else if (d == 3) i -= 1;
        else assert(false);
    }

    friend ostream &operator<<(ostream &s, State st) {
        if (st.i == UNKNOWN) return s << "unknown";
        if (st.i == INF_LOOP) return s << "inf";
        return s << st.i + 1 << " " << st.j + 1 << " "
                 << "eswn"[st.d];
    }
};

vector<pair<State, int>> to_exec;

struct FullState {
    State pos;
    int prog, op;

    int id() const {
        int id = pos.id();
        id *= An;
        id += A[prog].base + op;
        return id;
    }

    friend ostream &operator<<(ostream &s, FullState st) {
        return s << st.pos << " " << A[st.prog].name << "[" << st.prog << "]"
                 << "(" << st.op << "/" << A[st.prog].n << ")";
    }
};

bool eval_cond(State pos, int cond_type) {
    if (cond_type == BARRIER) {
        pos.move();
        return barrier_at(pos.i, pos.j);
    } else {
        return (pos.d == cond_type);
    }
}

vector<State> dp;
State run(FullState s);
State run_inner(FullState s) {
    const Op &op = A[s.prog].ops[s.op];
    if (op.t == MOVE) {
        State pos = s.pos;
        pos.move();
        if (!barrier_at(pos.i, pos.j)) s.pos = pos;
        s.op += 1;
        return run(s);
    } else if (op.t == TURN) {
        s.pos.d = (s.pos.d + 3) % 4;
        s.op += 1;
        return run(s);
    } else if (op.t == IF) {
        bool cond = eval_cond(s.pos, op.arg[0]);
        FullState substate = s;
        substate.prog = op.arg[1 + !cond];
        substate.op = 0;
        s.pos = run(substate);
        s.op += 1;
        return run(s);
    } else if (op.t == UNTIL) {
        bool cond = eval_cond(s.pos, op.arg[0]);
        if (cond) {
            s.op += 1;
            return run(s);
        } else {
            FullState substate = s;
            substate.prog = op.arg[1];
            substate.op = 0;
            s.pos = run(substate);
            return run(s);
        }
    } else if (op.t == CALL) {
        FullState substate = s;
        substate.prog = byname[op.arg[0]];
        substate.op = 0;
        s.pos = run(substate);
        s.op += 1;
        return run(s);
    }
    assert(false);
}
State run(FullState s) {
    if (s.pos.i == INF_LOOP) return {INF_LOOP, INF_LOOP, INF_LOOP};
    if (s.op == A[s.prog].n) return s.pos;

    State &out = dp[s.id()];
    if (out.i != UNKNOWN) return out;
    out = {INF_LOOP, INF_LOOP, INF_LOOP};
    out = run_inner(s);
    // cerr << "DP[" << s << "] = " << out << endl;
    return out;
}

int parse_program(char *&s, string name) {
    Program prog = {0, 0, name, {}};

    while (*s != ')') {
        Op op;
        op.t = *(s++);
        if ('A' <= op.t && op.t <= 'Z') {
            op.arg[0] = op.t - 'A';
            op.t = CALL;
        } else if (op.t == MOVE || op.t == TURN) {
        } else if (op.t == IF || op.t == UNTIL) {
            // read condition
            char cond = *(s++);
            if (cond == 'b') op.arg[0] = BARRIER;
            else op.arg[0] = decode_dir(cond);
            // read first program
            assert(*s == '(');
            s++;
            op.arg[1] = parse_program(s, name);
            assert(*s == ')');
            s++;
            // read second program (only for IF)
            if (op.t == IF) {
                assert(*s == '(');
                s++;
                op.arg[2] = parse_program(s, name);
                assert(*s == ')');
                s++;
            }
        } else {
            assert(false);
        }
        prog.ops.push_back(op);
    }

    int p_id = A.size();
    A.push_back(prog);
    return p_id;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> H >> W >> D >> E;
    mp.resize(H);
    rep(i, H) cin >> mp[i];
    rep(j, D) {
        char pname, eq;
        cin >> pname >> eq;
        string p;
        cin >> p;
        p.push_back(')');
        char *s = &p[0];
        string pname_str;
        pname_str.push_back(pname);
        byname[pname - 'A'] = parse_program(s, pname_str);
    }
    to_exec.resize(E);
    rep(k, E) {
        char dc;
        int8_t i, j, d;
        cin >> i >> j >> dc;
        i--, j--;
        d = decode_dir(dc);
        string p;
        cin >> p;
        p.push_back(')');
        char *s = &p[0];
        stringstream ss;
        ss << "exec" << k + 1;
        to_exec[k] = {{i, j, d}, parse_program(s, ss.str())};
    }

    // number program instructions
    An = 0;
    for (Program &prog : A) {
        prog.base = An;
        prog.n = prog.ops.size();
        An += prog.n;
    }

    // run the programs
    dp.assign(W * H * 4 * An, {UNKNOWN, UNKNOWN, UNKNOWN});
    for (auto [state, prog] : to_exec) {
        State f = run({state, prog, 0});
        cout << f << "\n";
    }
}
