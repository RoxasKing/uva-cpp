#include <cstdio>
using namespace std;

const int maxn = 1e4;

int a[maxn], top;

int main() {
    int n, x;
    while (scanf("%d", &n) == 1 && n) {
        while (scanf("%d", &x) == 1 && x) {
            top = -1;
            int i = 1, k = 0;
            while (i <= x) a[++top] = i++;
            --top;

            bool ok = true;
            while (++k < n) {
                scanf("%d", &x);
                while (i <= x) a[++top] = i++;
                if (a[top] == x) {
                    --top;
                } else {
                    ok = false;
                    break;
                }
            }
            while (++k < n) scanf("%d", &x);
            ok ? puts("Yes") : puts("No");
        }
        puts("");
    }

    return 0;
}
