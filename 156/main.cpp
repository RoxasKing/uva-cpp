#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string, int> cnt;
vector<string> words;

string repr(const string& s) {
    string ans = s;
    for (unsigned int i = 0; i < ans.length(); i++) ans[i] = towlower(ans[i]);
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    string s;
    while (cin >> s) {
        if (s[0] == '#') break;
        words.push_back(s);
        cnt[repr(s)]++;
    }

    vector<string> ans;
    for (unsigned int i = 0; i < words.size(); i++)
        if (cnt[repr(words[i])] == 1) ans.push_back(words[i]);

    sort(ans.begin(), ans.end());
    for (unsigned int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";

    return 0;
}
