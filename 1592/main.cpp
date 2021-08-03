#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long ll;

const int maxr = 10000 + 1;
const int maxc = 10 + 1;

int m, n, db[maxr][maxc], cnt;

unordered_map<string, int> id;
int ID(const string& s) {
    if (!id.count(s)) id[s] = ++cnt;
    return id[s];
}

void query() {
    for (int c1 = 0; c1 < m; c1++) {
        for (int c2 = c1 + 1; c2 < m; c2++) {
            unordered_map<ll, int> d;
            for (int i = 0; i < n; i++) {
                ll id = (ll)db[i][c1] * (ll)(n * m + 1) + (ll)db[i][c2];
                if (d.count(id)) {
                    printf("NO\n");
                    printf("%d %d\n", d[id] + 1, i + 1);
                    printf("%d %d\n", c1 + 1, c2 + 1);
                    return;
                }
                d[id] = i;
            }
        }
    }
    printf("YES\n");
}

int main() {
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        if (!(ss >> n >> m)) break;
        cnt = 0;
        id.clear();
        for (int i = 0; i < n; i++) {
            getline(cin, s);
            int lastpos = -1;
            for (int j = 0; j < m; j++) {
                int p = s.find(',', lastpos + 1);
                if (p == (int)string::npos) p = s.length();
                db[i][j] = ID(s.substr(lastpos + 1, p - (lastpos + 1)));
                lastpos = p;
            }
        }
        query();
    }

    return 0;
}
