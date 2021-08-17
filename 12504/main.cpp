#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

string s;
stringstream ss;
unordered_map<string, string> map_a, map_b;
set<string> set_a, set_b, set_c;

void read_data(unordered_map<string, string>& umap, set<string>& uset) {
    getline(cin, s);
    for (uint i = 0; i < s.size(); i++)
        if (s[i] == '{' || s[i] == '}' || s[i] == ',') s[i] = ' ';
    ss = stringstream(s);
    while (ss >> s) {
        int i = s.find(":");
        string key = s.substr(0, i);
        string val = s.substr(i + 1);
        umap.emplace(key, val);
        uset.emplace(key);
    }
}

int main() {
    int t;
    getline(cin, s);
    ss = stringstream(s);
    ss >> t;

    while (t--) {
        read_data(map_a, set_a);
        read_data(map_b, set_b);

        set_intersection(ALL(set_a), ALL(set_b), INS(set_c));

        bool ok = false;

        if (set_b.size() > set_c.size()) {
            ok = true;
            cout << "+";
            int cnt = 0;
            for (set<string>::iterator it = set_b.begin(); it != set_b.end(); it++) {
                if (set_c.find(*it) != set_c.end()) continue;
                if (cnt) cout << ",";
                cout << *it;
                cnt++;
            }
            cout << "\n";
        }

        if (set_a.size() > set_c.size()) {
            ok = true;
            cout << "-";
            int cnt = 0;
            for (set<string>::iterator it = set_a.begin(); it != set_a.end(); it++) {
                if (set_c.find(*it) != set_c.end()) continue;
                if (cnt) cout << ",";
                cout << *it;
                cnt++;
            }
            cout << "\n";
        }

        if (!set_c.empty()) {
            int cnt = 0;
            for (set<string>::iterator it = set_c.begin(); it != set_c.end(); it++) {
                if (map_a[*it] == map_b[*it]) continue;
                if (cnt == 0) {
                    cout << "*";
                    ok = true;
                } else {
                    cout << ",";
                }
                cout << *it;
                cnt++;
            }
            if (cnt) cout << "\n";
        }

        if (!ok) cout << "No changes\n";

        cout << "\n";
        if (t) {
            map_a.clear();
            map_b.clear();
            set_a.clear();
            set_b.clear();
            set_c.clear();
        }
    }

    return 0;
}
