#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Array {
    int len;
    unordered_map<int, int> h;
    Array(int len = 0) : len(len) {}
};

unordered_map<char, Array> arrs;

int parse(const string& exp) {
    if ('0' <= exp[0] && exp[0] <= '9') {
        int val = 0;
        for (int i = 0; i < (int)exp.size(); i++) val = val * 10 + exp[i] - '0';
        return val;
    }

    char name = exp[0];
    int idx = parse(exp.substr(2, exp.size() - 3));
    if (idx == -1 || arrs[name].len <= idx || arrs[name].h.find(idx) == arrs[name].h.end()) return -1;

    return arrs[name].h[idx];
}

int main() {
    string s;
    while (getline(cin, s) && s != ".") {
        int cur = 1, err = -1;

        for (;;) {
            char name = s[0];
            int i = s.find("=");

            if (i == -1) {
                int len = parse(s.substr(2, s.size() - 3));
                if (len == -1) {
                    err = cur;
                    break;
                }
                arrs.emplace(name, Array(len));
            } else {
                if (arrs.find(name) == arrs.end()) {
                    err = cur;
                    break;
                }
                int idx = parse(s.substr(2, i - 3));
                if (idx == -1 || arrs[name].len <= idx) {
                    err = cur;
                    break;
                }
                int val = parse(s.substr(i + 1));
                if (val == -1) {
                    err = cur;
                    break;
                }
                arrs[name].h[idx] = val;
            }

            cur++;
            getline(cin, s);
            if (s == ".") break;
        }

        if (err == -1) {
            cout << "0\n";
        } else {
            while (getline(cin, s) && s != ".")
                ;
            cout << err << "\n";
        }
        arrs.clear();
    }

    return 0;
}
