#include <algorithm>
#include <iostream>
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
vector<vector<int>> docs;
unordered_map<int, int> line_doc_map;
unordered_map<string, set<int>> word_line_map;
unordered_map<string, set<int>> word_doc_map;

int main() {
    int n, m;
    string s;
    stringstream ss;

    getline(cin, s);
    ss = stringstream(s);
    ss >> n;

    for (int doc_idx = 0; doc_idx < n; doc_idx++) {
        vector<int> line_idxs;
        while (getline(cin, s) && s != asterisk) {
            int row_idx = lines.size();
            lines.push_back(s);
            for (uint i = 0; i < s.size(); i++) {
                if ('a' <= s[i] && s[i] <= 'z') continue;
                ('A' <= s[i] && s[i] <= 'Z') ? (s[i] += 'a' - 'A') : (s[i] = ' ');
            }
            stringstream ss(s);
            string word;
            while (ss >> word) {
                word_line_map[word].emplace(row_idx);
                word_doc_map[word].emplace(doc_idx);
            }
            line_doc_map.emplace(row_idx, doc_idx);
            line_idxs.push_back(row_idx);
        }
        docs.push_back(line_idxs);
    }

    getline(cin, s);
    ss = stringstream(s);
    ss >> m;

    while (m--) {
        bool ok = true;
        getline(cin, s);
        int i = s.find_first_of(" ");
        int j = s.find_last_of(" ");
        if (i == -1) {
            auto& ids = word_line_map[s];
            int prev = -1;
            for (set<int>::iterator it = ids.begin(); it != ids.end(); it++) {
                if (it != ids.begin() && line_doc_map[*it] != prev) print_dashes();
                cout << lines[*it] << "\n";
                prev = line_doc_map[*it];
            }
            if (ids.size() == 0) ok = false;
        } else if (i != j) {
            string term1 = s.substr(0, i);
            string term2 = s.substr(j + 1);
            string op = s.substr(i + 1, j - 1 - i);

            unordered_set<int> doc_ids;
            auto& a = word_doc_map[term1];
            auto& b = word_doc_map[term2];
            (op == "AND") ? set_intersection(ALL(a), ALL(b), INS(doc_ids)) : set_union(ALL(a), ALL(b), INS(doc_ids));

            set<int> ids;
            auto& ids_a = word_line_map[term1];
            for (set<int>::iterator it = ids_a.begin(); it != ids_a.end(); it++)
                if (doc_ids.find(line_doc_map[*it]) != doc_ids.end()) ids.emplace(*it);
            auto& ids_b = word_line_map[term2];
            for (set<int>::iterator it = ids_b.begin(); it != ids_b.end(); it++)
                if (doc_ids.find(line_doc_map[*it]) != doc_ids.end()) ids.emplace(*it);

            int prev = -1;
            for (set<int>::iterator it = ids.begin(); it != ids.end(); it++) {
                if (it != ids.begin() && line_doc_map[*it] != prev) print_dashes();
                cout << lines[*it] << "\n";
                prev = line_doc_map[*it];
            }
            if (ids.size() == 0) ok = false;
        } else {
            unordered_set<int> skip;
            auto& ids = word_doc_map[s.substr(i + 1)];
            for (set<int>::iterator it = ids.begin(); it != ids.end(); it++)
                skip.emplace(*it);

            int cnt = 0;
            for (int i = 0; i < (int)docs.size(); i++) {
                if (skip.count(i)) continue;
                if (cnt) print_dashes();
                for (auto& j : docs[i]) cout << lines[j] << "\n";
                cnt++;
            }
            if (cnt == 0) ok = false;
        }
        if (!ok) print_found_nothing();
        print_signs();
    }

    return 0;
}
