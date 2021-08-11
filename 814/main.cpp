#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

void parse_addr(const string& addr, string& user, string& mta) {
    int i = addr.find('@');
    user = addr.substr(0, i);
    mta = addr.substr(i + 1);
}

int main() {
    int n;
    string buf, mta, user, from_addr, from_user, from_mta, to_user, to_mta;
    set<string> addr_set;

    while (cin >> buf && buf != "*") {
        cin >> mta >> n;
        while (n--) {
            cin >> user;
            addr_set.insert(user + "@" + mta);
        }
    }

    while (cin >> from_addr && from_addr != "*") {
        parse_addr(from_addr, from_user, from_mta);

        vector<string> mtas;
        map<string, vector<string>> dsts;
        set<string> has;
        while (cin >> buf && buf != "*") {
            if (has.count(buf)) continue;
            has.insert(buf);

            parse_addr(buf, to_user, to_mta);
            if (!dsts.count(to_mta)) {
                mtas.push_back(to_mta);
                dsts[to_mta] = vector<string>();
            }
            dsts[to_mta].push_back(buf);
        }
        getline(cin, buf);

        string content;
        while (getline(cin, buf) && buf[0] != '*') content += "     " + buf + "\n";

        for (auto& to_mta : mtas) {
            cout << "Connection between " << from_mta << " and " << to_mta << "\n";
            cout << "     HELO " << from_mta << "\n     250\n";
            cout << "     MAIL FROM:<" << from_addr << ">\n     250\n";
            bool send = false;
            for (auto& to_addr : dsts[to_mta]) {
                cout << "     RCPT TO:<" << to_addr << ">\n";
                if (addr_set.count(to_addr)) {
                    send = true;
                    cout << "     250\n";
                } else {
                    cout << "     550\n";
                }
            }
            if (send)
                cout << "     DATA\n     354\n"
                     << content << "     .\n     250\n";
            cout << "     QUIT\n     221\n";
        }
    }

    return 0;
}
