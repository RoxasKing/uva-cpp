#include <cstdio>
#include <cstring>

const int maxn = 52;

int g[maxn][maxn];

int ID(char a, char b) { return (a - 'A') * 2 + (b == '+' ? 0 : 1); }

void connect(char a1, char b1, char a2, char b2) {
    if (a1 != '0' && a2 != '0')
        g[ID(a1, b1) ^ 1][ID(a2, b2)] = 1;
}

int c[maxn];

bool dfs(int u) {
    c[u] = -1;
    for (int v = 0; v < maxn; v++)
        if (g[u][v] && (c[v] < 0 || (c[v] == 0 && dfs(v)))) return true;
    c[u] = 1;
    return false;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        memset(g, 0, sizeof(g));
        while (n--) {
            char s[9];
            scanf("%s", s);
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (i != j) connect(s[i * 2], s[i * 2 + 1], s[j * 2], s[j * 2 + 1]);
        }
        bool ok = false;
        memset(c, 0, sizeof(c));
        for (int i = 0; i < maxn; i++)
            if (!c[i] && dfs(i)) {
                ok = true;
                break;
            }
        ok ? printf("unbounded\n") : printf("bounded\n");
    }
    return 0;
}
