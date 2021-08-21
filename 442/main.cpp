#include <cstdio>
using namespace std;

const int maxn = 26;
const int maxk = 100;

int mat[maxn][2], stk1[maxk], stk2[maxk];

int main() {
    char ch;
    int n, r, c;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        getchar();
        scanf("%c%d%d", &ch, &r, &c);
        mat[i][0] = r;
        mat[i][1] = c;
    }
    getchar();

    while (true) {
        if ((ch = getchar()) == EOF) break;
        int p1 = -1, p2 = -1;
        bool ok = true;
        int cnt = 0;
        stk2[++p2] = p1 + 1;
        while ((ch = getchar()) != '\n') {
            int idx = ch - 'A';
            if (ch == '(') {
                stk2[++p2] = p1 + 1;
            } else if (ch == ')') {
                int mul = stk1[stk2[p2]];
                for (int i = stk2[p2] + 1; i <= p1 - 2; i++) {
                    if (stk1[i] != stk1[i + 1]) {
                        ok = false;
                        break;
                    }
                    mul *= stk1[i];
                }
                if (!ok) break;
                mul *= stk1[p1];
                cnt += mul;
                stk1[stk2[p2] + 1] = stk1[p1];
                p1 = stk2[p2] + 1;
                p2--;
            } else {
                stk1[++p1] = mat[idx][0];
                stk1[++p1] = mat[idx][1];
            }
        }
        while (ch != '\n') ch = getchar();
        ok ? printf("%d\n", cnt) : printf("error\n");
    }

    return 0;
}
