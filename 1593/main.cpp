#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s;
    vector<vector<string>> line;
    vector<int> colLen;

    while (getline(cin, s)) {
        stringstream ss(s);
        int i = 0;
        vector<string> a;
        while (ss >> s) {
            if (i == (int)colLen.size()) colLen.push_back(0);
            colLen[i] = max(colLen[i], (int)s.size());
            i++;
            a.push_back(s);
        }
        line.push_back(a);
    }

    for (auto& a : line) {
        for (int i = 0; i < (int)a.size(); i++) {
            if (i) cout << " ";
            cout << a[i];
            if (i < (int)(a.size() - 1))
                for (int j = 0; j < colLen[i] - (int)a[i].size(); j++) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
