#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

const string delimiter = " by ";

struct bookInfo {
    string author;
    int idx;
    bool borrowed;
    bookInfo() : author(), idx(), borrowed() {}
    bookInfo(string author, int idx = -1, bool borrowed = false) : author(author), idx(idx), borrowed(borrowed) {}
};

unordered_map<string, bookInfo> infos;
vector<string> books;

int main() {
    string s;

    while (getline(cin, s) && s[0] != 'E') {
        int idx = s.find(delimiter);
        string title = s.substr(0, idx);
        string author = s.substr(idx + 4);
        // cout << "title: " << title << ", name: " << name << "\n";
        infos.emplace(title, bookInfo(author));
        books.push_back(title);
    }

    auto cmp = [](const string& a, const string& b) -> bool {
        if (infos[a].author != infos[b].author) return infos[a].author < infos[b].author;
        return a < b;
    };

    sort(books.begin(), books.end(), cmp);

    // for (auto& book : books) {
    //     cout << "title: " << book << ", name: " << infos[book].author << "\n";
    // }

    for (uint i = 0; i < books.size(); i++) {
        infos[books[i]].idx = i;
    }

    vector<string> q;
    unordered_set<string> inq;

    while (getline(cin, s) && s[0] != 'E') {
        int idx = s.find(" ");
        string op = s.substr(0, idx);
        string title = s.substr(idx + 1);

        if (op[0] == 'B') {
            infos[title].borrowed = true;
        } else if (op[0] == 'R') {
            if (!inq.count(title)) {
                inq.emplace(title);
                q.push_back(title);
            }
        } else {
            sort(q.begin(), q.end(), cmp);
            for (auto& title : q) {
                int idx = infos[title].idx - 1;
                for (; idx >= 0 && infos[books[idx]].borrowed; idx--)
                    ;

                if (idx < 0)
                    cout << "Put " << title << " first\n";
                else
                    cout << "Put " << title << " after " << books[idx] << "\n";
                infos[title].borrowed = false;
            }
            q.clear();
            inq.clear();
            cout << "END\n";
        }
    }

    return 0;
}
