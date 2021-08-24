#include <cstdio>
#include <cstring>

const int maxn = 1e4;
int sum[maxn], v;

void build(int p) {
    scanf("%d", &v);
    if (v == -1) return;
    sum[p] += v;
    build(p - 1);
    build(p + 1);
}

int main() {
    int kase = 0;
    while (scanf("%d", &v) == 1 && v != -1) {
        memset(sum, 0, sizeof(sum));
        int p = maxn >> 1;
        sum[p] += v;
        build(p - 1);
        build(p + 1);

        p = 0;
        while (!sum[p]) p++;
        printf("Case %d:\n%d", ++kase, sum[p++]);
        while (sum[p]) printf(" %d", sum[p++]);
        puts("\n");
    }

    return 0;
}
