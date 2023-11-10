#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Term {
    string main_alias;
    vector<string> lowercase_aliases, broader_s, narrower_s;
    set<int> broader, narrower;
};

string S;
int i;
vector<Term> terms;
unordered_map<string, int> term_map;
vector<int> collected;
vector<int> matches;

void skipspace() {
    while (isspace(S[i])) i++;
}

void assertstr(const string &s) {
    assert(S.substr(i, s.size()) == s);
}

void readstr(const string &s) {
    assertstr(s);
    i += s.size();
}

string parse_tag() {
    skipspace();
    readstr("<");
    skipspace();
    bool closes = false;
    if (S[i] == '/') {
        closes = true;
        i++;
        skipspace();
    }
    int l = i;
    while (isalpha(S[i])) i++;
    int r = i;
    skipspace();
    readstr(">");
    string s = S.substr(l, r - l);
    if (closes) s.insert(s.begin(), '/');
    return s;
}

void parse_close(string tag) {
    string s = parse_tag();
    tag.insert(tag.begin(), '/');
    assert(s == tag);
}

void parse_terminfo() {
    int term_id = terms.size();
    terms.push_back({});
    Term &t = terms.back();
    while (true) {
        string tag = parse_tag();
        if (tag == "/TermInfo") {
            // end terminfo
            break;
        } else if (tag == "T" || tag == "UF" || tag == "NT" || tag == "BT") {
            // term
            int l = i;
            while (S[i] != '<') i++;
            string term = S.substr(l, i - l);
            parse_close(tag);
            if (tag == "T") {
                t.main_alias = term;
            }
            for (char &c : term) c = tolower(c);
            if (tag == "T" || tag == "UF") {
                t.lowercase_aliases.push_back(term);
                term_map[term] = term_id;
            } else if (tag == "NT") {
                t.narrower_s.push_back(term);
            } else if (tag == "BT") {
                t.broader_s.push_back(term);
            }
        } else assert(false);
    }
}

void parse_thesaurus() {
    string thesau = parse_tag();
    assert(thesau == "Thesaurus");

    while (true) {
        string tag = parse_tag();
        if (tag == "/Thesaurus") {
            // end thesaurus
            break;
        } else if (tag == "TermInfo") {
            // term
            parse_terminfo();
        }
    }
}

struct Vertex {
    int next[256], go[256];
    int p, link = -1, exit = -1, cnt = -1;
    vector<int> leaf;
    char pch;
    Vertex(int p = -1, char ch = 0) : p(p), pch(ch) {
        rep(i, 256) next[i] = -1, go[i] = -1;
    }
};
vector<Vertex> t(1);
void add(string s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = ch;
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].leaf.push_back(id);
}
int go(int v, char ch);
int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0) t[v].link = 0;
        else t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}
int go(int v, char ch) {
    int c = ch;
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
        else t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}
int next_match(int v) { // Optional
    if (t[v].exit == -1) {
        if (t[get_link(v)].leaf.size()) t[v].exit = get_link(v);
        else t[v].exit = v == 0 ? 0 : next_match(get_link(v));
    }
    return t[v].exit;
}
int cnt_matches(int v) { // Optional
    if (t[v].cnt == -1)
        t[v].cnt = v == 0 ? 0 : t[v].leaf.size() + cnt_matches(get_link(v));
    return t[v].cnt;
}

vector<bool> visited;
void visit(int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (int v : terms[u].narrower) visit(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string ins(istreambuf_iterator<char>(cin), {});
    S = ins;

    parse_thesaurus();

    rep(u, terms.size()) {
        for (string &broad : terms[u].broader_s) {
            int v = term_map[broad];
            terms[u].broader.insert(v);
            terms[v].narrower.insert(u);
        }
        // for (string &narrow : terms[u].narrower_s) {
        //     int v = term_map[narrow];
        //     terms[u].narrower.insert(v);
        //     terms[v].broader.insert(u);
        // }
    }

    string prototxt = S.substr(i);
    string txt;
    rep(i, prototxt.size()) {
        if (prototxt[i] == ',' || prototxt[i] == '.' || prototxt[i] == '?' || prototxt[i] == '!') {
            txt.push_back(' ');
            txt.push_back(prototxt[i]);
            txt.push_back(' ');
        } else if (prototxt[i] == '\n') {
            txt.push_back(' ');
            txt.push_back('\n');
            txt.push_back(' ');
        } else {
            txt.push_back(tolower(prototxt[i]));
        }
    }
    txt.insert(txt.begin(), ' ');
    txt.push_back(' ');

    /*cerr << "terms:" << endl;
    for (Term &t : terms) {
        cerr << '"' << t.main_alias << '"' << " (alias";
        for (string &al : t.lowercase_aliases) {
            cerr << " \"" << al << "\"";
        }
        cerr << ")" << endl;
        cerr << "  broader:";
        for (int b : t.broader) {
            cerr << " \"" << terms[b].main_alias << "\"";
        }
        cerr << endl;
        cerr << "  narrower:";
        for (int b : t.narrower) {
            cerr << " \"" << terms[b].main_alias << "\"";
        }
        cerr << endl;
    }

    cerr << "text:" << endl
         << "```" << endl;
    cerr << txt << "```" << endl;*/

    rep(id, terms.size()) {
        for (string &al : terms[id].lowercase_aliases) {
            add(string(" ") + al + string(" "), id);
        }
    }

    matches.assign(terms.size(), 0);
    int state = go(0, ' ');
    for (char c : txt) {
        state = go(state, c);

        int st = state;
        while (st) {
            for (int id : t[st].leaf) {
                matches[id]++;
            }
            st = next_match(st);
        }
    }

    vector<pair<int, string>> output;
    rep(id, terms.size()) {
        if (terms[id].broader.size()) continue;
        visited.assign(terms.size(), false);
        visit(id);
        int ans = 0;
        rep(id2, terms.size()) if (visited[id2]) ans += matches[id2];
        output.push_back({-ans, terms[id].main_alias});
    }

    sort(output.begin(), output.end());
    for (auto [cnt, name] : output)
        cout << name << " = " << -cnt << "\n";
}
