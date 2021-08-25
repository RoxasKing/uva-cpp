#include <cstdio>
#include <cstring>

const int maxn = 100 + 1;

int g[maxn][maxn], d[maxn], q[maxn];

int main() {
    int n, m, u, v;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        while (m--) {
            scanf("%d%d", &u, &v);
            g[u][v] = 1;
            d[v]++;
        }
        int l = 0, r = -1;
        for (int i = 1; i <= n; i++)
            if (d[i] == 0) q[++r] = i;
        int first = 1;
        while (l <= r) {
            first ? first = 0 : putchar(' ');
            int u = q[l++];
            printf("%d", u);
            for (int v = 1; v <= n; v++) {
                if (!g[u][v]) continue;
                d[v]--;
                if (!d[v]) q[++r] = v;
            }
        }
        puts("");
    }
    return 0;
}
