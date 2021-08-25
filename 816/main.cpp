#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const char* dirs = "NESW";
const char* turns = "FLR";
int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

struct Node {
    int r, c, dir, turn;
    Node(int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
};

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(const Node& u, int turn) {
    int dir = u.dir;
    if (turn == 1) dir = (dir + 3) % 4;
    if (turn == 2) dir = (dir + 1) % 4;
    return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

const int maxn = 9 + 1;
int ok[maxn][maxn][4][3], d[maxn][maxn][4];
Node p[maxn][maxn][4];

bool inside(int r, int c) { return 1 <= r && r <= 9 && 1 <= c && c <= 9; }

int main() {
    char name[21], s[5];
    int r0, c0, r2, c2;
    while (scanf("%s%d%d%s%d%d", name, &r0, &c0, s, &r2, &c2) == 6) {
        memset(ok, 0, sizeof(ok));
        memset(d, -1, sizeof(d));
        int dir = dir_id(s[0]);
        int r1 = r0 + dr[dir], c1 = c0 + dc[dir];
        d[r1][c1][dir] = 0;
        for (;;) {
            int r, c;
            scanf("%d", &r);
            if (r == 0) break;
            scanf("%d", &c);
            while (scanf("%s", s) == 1 && s[0] != '*')
                for (int i = 1; s[i]; i++) ok[r][c][dir_id(s[0])][turn_id(s[i])] = 1;
        }
        vector<Node> nodes;
        queue<Node> q;
        q.push(Node(r1, c1, dir));
        while (!q.empty()) {
            Node u = q.front();
            q.pop();
            if (u.r == r2 && u.c == c2) {
                nodes.push_back(u);
                break;
            }
            for (int i = 0; i < 3; i++) {
                Node v = walk(u, i);
                if (ok[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) {
                    d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
                    p[v.r][v.c][v.dir] = u;
                    q.push(v);
                }
            }
        }
        puts(name);
        if (nodes.empty()) {
            puts("  No Solution Possible");
            continue;
        }
        for (;;) {
            Node& u = nodes[nodes.size() - 1];
            if (d[u.r][u.c][u.dir] == 0) break;
            nodes.push_back(p[u.r][u.c][u.dir]);
        }
        nodes.push_back(Node(r0, c0));
        int cnt = 0;
        for (int i = nodes.size() - 1; i >= 0; i--) {
            if (cnt % 10 == 0) putchar(' ');
            printf(" (%d,%d)", nodes[i].r, nodes[i].c);
            if (++cnt % 10 == 0 || i == 0) puts("");
        }
    }
    return 0;
}
