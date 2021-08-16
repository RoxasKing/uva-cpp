#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

const string asterisk = "**********";
void print_found_nothing() { cout << "Sorry, I found nothing.\n"; }
void print_dashes() { cout << "----------\n"; }
void print_signs() { cout << "==========\n"; }

vector<string> lines;
vector<vector<int>> doc_row_ids;

struct DocRef {
    int doc_id;
    vector<int> row_ids;
    unordered_set<int> has;
    DocRef(int doc_id = 0) : doc_id(doc_id), row_ids() {}
    void push(int row_id) {
        if (has.find(row_id) != has.end()) return;
        row_ids.push_back(row_id);
        has.emplace(row_id);
    }
};

struct Trie {
    vector<Trie*> child;
    unordered_map<int, int> ref_map;
    vector<DocRef*> refs;
    vector<DocRef*> empty_ref;
    Trie() : child(), ref_map(), refs() { child = vector<Trie*>(26, nullptr); }

    void Insert(const string& word, int doc_id, int row_id) {
        auto t = this;
        for (auto& ch : word) {
            int i = ch - 'a';
            if (t->child[i] == nullptr)
                t->child[i] = new Trie();
            t = t->child[i];
        }
        if (t->ref_map.find(doc_id) == t->ref_map.end()) {
            t->ref_map.emplace(doc_id, t->refs.size());
            t->refs.push_back(new DocRef(doc_id));
        }
        t->refs[t->ref_map[doc_id]]->push(row_id);
    }

    vector<DocRef*>& Query(const string& word) {
        Trie* t = this;
        for (auto& ch : word) {
            int i = ch - 'a';
            if (t->child[i] == nullptr) return empty_ref;
            t = t->child[i];
        }
        return t->refs;
    }
};

int main() {
    Trie* t = new Trie();
    string s, word;
    stringstream ss;

    int n, m;
    getline(cin, s);
    ss = stringstream(s);
    ss >> n;

    for (int doc_id = 0; doc_id < n; doc_id++) {
        vector<int> ids;
        while (getline(cin, s) && s != asterisk) {
            int row_id = lines.size();
            ids.push_back(row_id);
            lines.push_back(s);
            for (uint i = 0; i < s.size(); i++) {
                if ('a' <= s[i] && s[i] <= 'z') continue;
                ('A' <= s[i] && s[i] <= 'Z') ? (s[i] += ('a' - 'A')) : (s[i] = ' ');
            }
            ss.clear();
            ss = stringstream(s);
            while (ss >> word) t->Insert(word, doc_id, row_id);
        }
        doc_row_ids.push_back(ids);
    }

    getline(cin, s);
    ss.clear();
    ss = stringstream(s);
    ss >> m;
    while (m--) {
        bool ok = true;
        getline(cin, s);
        int i = s.find_first_of(" ");
        int j = s.find_last_of(" ");
        if (i == -1) {
            auto& refs = t->Query(s);
            if (refs.empty()) ok = false;
            for (uint i = 0; i < refs.size(); i++) {
                if (i) print_dashes();
                for (auto& id : refs[i]->row_ids) cout << lines[id] << "\n";
            }
        } else if (i != j) {
            string term1 = s.substr(0, i);
            string term2 = s.substr(j + 1);
            auto& refs1 = t->Query(term1);
            auto& refs2 = t->Query(term2);
            set<int> a, b;
            for (auto& ref : refs1) a.emplace(ref->doc_id);
            for (auto& ref : refs2) b.emplace(ref->doc_id);
            string op = s.substr(i + 1, j - 1 - i);
            unordered_set<int> doc_ids;
            (op == "AND") ? set_intersection(ALL(a), ALL(b), INS(doc_ids)) : set_union(ALL(a), ALL(b), INS(doc_ids));
            map<int, set<int>> row_ids;
            for (auto& ref : refs1) {
                int doc_id = ref->doc_id;
                if (doc_ids.find(doc_id) == doc_ids.end()) continue;
                for (auto& row_id : ref->row_ids) row_ids[doc_id].emplace(row_id);
            }
            for (auto& ref : refs2) {
                int doc_id = ref->doc_id;
                if (doc_ids.find(doc_id) == doc_ids.end()) continue;
                for (auto& row_id : ref->row_ids) row_ids[doc_id].emplace(row_id);
            }
            if (row_ids.empty()) ok = false;
            for (map<int, set<int>>::iterator it = row_ids.begin(); it != row_ids.end(); it++) {
                if (it != row_ids.begin()) print_dashes();
                set<int> ids = it->second;
                for (set<int>::iterator id = ids.begin(); id != ids.end(); id++) cout << lines[*id] << "\n";
            }
        } else {
            string term = s.substr(i + 1);
            auto& refs = t->Query(term);
            unordered_set<int> skip;
            for (auto& ref : refs) skip.emplace(ref->doc_id);
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (skip.find(i) != skip.end()) continue;
                if (cnt) print_dashes();
                for (auto& row_id : doc_row_ids[i]) cout << lines[row_id] << "\n";
                cnt++;
            }
            if (cnt == 0) ok = false;
        }
        if (!ok) print_found_nothing();
        print_signs();
    }

    return 0;
}
