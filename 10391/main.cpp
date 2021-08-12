#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    set<string> word_set;
    string s;
    while (cin >> s) {
        word_set.emplace(s);
    }

    unordered_set<string> has;
    for (auto& word : word_set) {
        if (word.size() < 2 || has.count(word)) continue;
        has.emplace(word);
        for (uint i = 0; i < word.size() - 1; i++) {
            string l = word.substr(0, i + 1), r = word.substr(i + 1);
            if (!word_set.count(l) || !word_set.count(r)) continue;
            cout << word << "\n";
            break;
        }
    }

    return 0;
}
