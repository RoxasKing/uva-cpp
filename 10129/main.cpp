#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxw = 1e3 + 1;
char s[maxw];
int g[26][26], seen[26], indeg[26], outdeg[26];

void dfs(int u) {
    seen[u] = 0;
    for (int i = 0; i < 26; i++)
        if (g[u][i] && seen[i]) dfs(i);
}

int main() {
    int T, N;
    scanf("%d", &T);
    while (T--) {
        memset(g, 0, sizeof(g));
        memset(indeg, 0, sizeof(indeg));
        memset(outdeg, 0, sizeof(outdeg));
        memset(seen, 0, sizeof(seen));
        scanf("%d", &N);
        char ch;
        int u, v;
        while (N--) {
            while ((ch = getchar()) == '\n')
                ;
            u = v = ch - 'a';
            while ((ch = getchar()) != '\n') v = ch - 'a';
            g[u][v]++;
            g[v][u]++;
            indeg[u]++;
            outdeg[v]++;
            seen[u] = seen[v] = 1;
        }
        dfs(u);
        bool ok = true;
        int deg = 0;
        for (int i = 0; i < 26; i++) {
            if (seen[i] || abs(indeg[i] - outdeg[i]) > 1) {
                ok = false;
                break;
            }
            if (abs(indeg[i] - outdeg[i]) == 1) deg += indeg[i] - outdeg[i];
        }
        (ok && abs(deg) <= 1) ? puts("Ordering is possible.") : puts("The door cannot be opened.");
    }
    return 0;
}
