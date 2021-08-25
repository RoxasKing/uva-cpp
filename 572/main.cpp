#include <cstdio>
#include <cstring>

const int maxn = 100 + 1;

char grid[maxn][maxn];
int m, n, vis[maxn][maxn];

void dfs(int r, int c) {
    if (r < 0 || m - 1 < r || c < 0 || n - 1 < c || vis[r][c] || grid[r][c] != '@') return;
    vis[r][c] = true;
    dfs(r - 1, c - 1);
    dfs(r - 1, c);
    dfs(r - 1, c + 1);
    dfs(r, c - 1);
    dfs(r, c + 1);
    dfs(r + 1, c - 1);
    dfs(r + 1, c);
    dfs(r + 1, c + 1);
}

int main() {
    while (scanf("%d%d", &m, &n) == 2 && m && n) {
        for (int i = 0; i < m; i++) scanf("%s", grid[i]);
        memset(vis, 0, sizeof(vis));
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!vis[i][j] && grid[i][j] == '@') {
                    ++cnt;
                    dfs(i, j);
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
