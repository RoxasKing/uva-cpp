#include <cstdio>
#include <cstring>

const int maxn = 200 + 1;

char ch, ss[maxn][maxn];

void dfs(int r, int c) {
    if (ss[r][c] == '#') return;
    printf("%c", ss[r][c]);
    putchar('(');
    if (r + 1 < maxn && ss[r + 1][c] == '|') {
        int j = c;
        while (j - 1 >= 0 && ss[r + 2][j - 1] == '-') j--;
        for (; j < maxn && ss[r + 2][j] == '-'; j++)
            if (ss[r + 3][j] && ss[r + 3][j] != ' ') dfs(r + 3, j);
    }
    putchar(')');
}

int main() {
    int T;
    scanf("%d", &T);
    getchar();
    while (T--) {
        memset(ss, 0, sizeof(ss));
        for (int i = 0;; i++) {
            int j = 0;
            while ((ch = getchar()) != '\n') ss[i][j++] = ch;
            if (ss[i][0] == '#') break;
        }
        int c = 0;
        while (ss[0][c] == ' ') c++;
        putchar('(');
        dfs(0, c);
        puts(")");
    }
    return 0;
}
