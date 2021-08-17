#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const double eps = 1e-9;

struct Map {
    string name;
    double x1, y1, x2, y2;
    double area, x0, y0, aspect_ratio;
    Map() {}
    Map(const string& name, int x1, int y1, int x2, int y2) : name(name), x1(x1), y1(y1), x2(x2), y2(y2) {
        double height = y2 - y1;
        double width = x2 - x1;
        area = height * width;
        x0 = (x1 + x2) / 2.0;
        y0 = (y1 + y2) / 2.0;
        aspect_ratio = height / width;
    }
};

vector<Map> maps;
unordered_map<string, vector<int>> locs;

int main() {
    string s;
    stringstream ss;
    getline(cin, s);

    while (getline(cin, s) && s != "LOCATIONS") {
        ss.clear();
        ss = stringstream(s);

        string name;
        double x1, y1, x2, y2;
        ss >> name >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        maps.push_back(Map(name, x1, y1, x2, y2));
    }

    auto cmp = [](const int& i, const int& j) -> bool { return maps[i].area > maps[j].area; };

    while (getline(cin, s) && s != "REQUESTS") {
        ss.clear();
        ss = stringstream(s);

        string location;
        double x, y;
        ss >> location >> x >> y;

        vector<int> ids;
        for (uint i = 0; i < maps.size(); i++) {
            auto& map = maps[i];
            if (map.x1 <= x && x <= map.x2 && map.y1 <= y && y <= map.y2) ids.push_back(i);
        }

        if (ids.empty()) {
            locs.emplace(location, ids);
            continue;
        }

        sort(ids.begin(), ids.end(), cmp);

        int i = 0;
        for (uint j = 1; j < ids.size(); j++) {
            int a = ids[i], b = ids[j];
            if (abs(maps[a].area - maps[b].area) > eps) {
                ids[++i] = b;
                continue;
            }
            int ax = abs(maps[a].x0 - x);
            int ay = abs(maps[a].y0 - y);
            int bx = abs(maps[b].x0 - x);
            int by = abs(maps[b].y0 - y);
            int da = ax * ax + ay * ay;
            int db = bx * bx + by * by;
            if (abs(da - db) > eps) {
                if (da > db) ids[i] = b;
                continue;
            }
            int ra = abs(maps[a].aspect_ratio - 0.75);
            int rb = abs(maps[b].aspect_ratio - 0.75);
            if (abs(ra - rb) > eps) {
                if (ra > rb) ids[i] = b;
                continue;
            }
            int ax2 = abs(maps[a].x2 - x);
            int ay2 = abs(maps[a].y1 - y);
            int bx2 = abs(maps[b].x2 - x);
            int by2 = abs(maps[b].y1 - y);
            int da2 = ax2 * ax2 + ay2 * ay2;
            int db2 = bx2 * bx2 + by2 * by2;
            if (abs(da2 - db2) > eps) {
                if (da2 < db2) ids[i] = b;
                continue;
            }
            if (maps[a].x1 > maps[b].x1) {
                ids[i] = b;
            }
        }
        ids.resize(i + 1);
        locs.emplace(location, ids);
    }

    while (getline(cin, s) && s != "END") {
        ss.clear();
        ss = stringstream(s);

        string location;
        uint level;
        ss >> location >> level;

        cout << location << " at detail level " << level;
        if (locs.find(location) != locs.end()) {
            if (locs[location].empty()) {
                cout << " no map contains that location\n";
            } else if (level - 1 < locs[location].size()) {
                int i = locs[location][level - 1];
                cout << " using " << maps[i].name << "\n";
            } else {
                int i = locs[location][locs[location].size() - 1];
                cout << " no map at that detail level; using " << maps[i].name << "\n";
            }
        } else {
            cout << " unknown location\n";
        }
    }

    return 0;
}
