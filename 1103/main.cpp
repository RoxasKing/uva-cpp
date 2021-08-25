#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 200 + 1;

char s[maxn], res[maxn];
int H, W, graph[maxn][maxn], vis[maxn][maxn];

void walk_blank(int r, int c) {
    if (r < 0 || H - 1 < r || c < 0 || W - 1 < c || graph[r][c]) return;
    graph[r][c] = 2;
    walk_blank(r - 1, c);
    walk_blank(r + 1, c);
    walk_blank(r, c - 1);
    walk_blank(r, c + 1);
}

void walk_hollow(int r, int c) {
    if (r < 0 || H - 1 < r || c < 0 || W - 1 < c || graph[r][c] || vis[r][c]) return;
    vis[r][c] = true;
    walk_hollow(r - 1, c);
    walk_hollow(r + 1, c);
    walk_hollow(r, c - 1);
    walk_hollow(r, c + 1);
}

void walk_image(int r, int c, int& cnt) {
    if (r < 0 || H - 1 < r || c < 0 || W - 1 < c || graph[r][c] == 2 || vis[r][c]) return;
    if (graph[r][c] == 0) {
        cnt++;
        walk_hollow(r, c);
        return;
    }
    vis[r][c] = true;
    walk_image(r - 1, c, cnt);
    walk_image(r + 1, c, cnt);
    walk_image(r, c - 1, cnt);
    walk_image(r, c + 1, cnt);
}

int main() {
    int kase = 0;
    while (scanf("%d%d", &H, &W) == 2 && H && W) {
        for (int i = 0; i < H; i++) {
            scanf("%s", s);
            for (int k = 0; k < W; k++) {
                int num = ('0' <= s[k] && s[k] <= '9') ? s[k] - '0' : 10 + s[k] - 'a';
                for (int j = k * 4; j < k * 4 + 4; j++)
                    graph[i][j] = (num >> (k * 4 + 3 - j)) & 1;
            }
        }
        W *= 4;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if ((i == 0 || i == H - 1 || j == 0 || j == W - 1) && graph[i][j] == 0)
                    walk_blank(i, j);
            }
        }
        memset(vis, 0, sizeof(vis));
        int size = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (graph[i][j] != 1 || vis[i][j]) continue;
                int cnt = 0;
                walk_image(i, j, cnt);
                if (cnt == 0)
                    res[size++] = 'W';
                else if (cnt == 1)
                    res[size++] = 'A';
                else if (cnt == 2)
                    res[size++] = 'K';
                else if (cnt == 3)
                    res[size++] = 'J';
                else if (cnt == 4)
                    res[size++] = 'S';
                else if (cnt == 5)
                    res[size++] = 'D';
            }
        }
        res[size] = '\0';
        std::sort(res, res + size);
        printf("Case %d: %s\n", ++kase, res);
    }
    return 0;
}
