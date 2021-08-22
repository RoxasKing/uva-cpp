#include <algorithm>
#include <cstdio>

const int maxn = 1e5 + 1;

int prev[maxn], next[maxn], forward;

void init(int n) {
    for (int i = 1; i <= n; i++) {
        prev[i] = i - 1;
        next[i] = (i + 1) % (n + 1);
    }
    next[0] = 1;
    prev[0] = n;
    forward = 1;
}

void link(int l, int r) { next[l] = r, prev[r] = l; }

int main() {
    int n, m, t, x, y, kase = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        init(n);

        while (m--) {
            scanf("%d", &t);
            t == 4 ? forward ^= 1 : scanf("%d%d", &x, &y);
            if (t == 3 && next[y] == x) std::swap(x, y);                        /* x and y linked,  y before x */
            if (t != 3 && !forward) t = 3 - t;                                  /* change 1 to 2, and 2 to 1 */
            if ((t == 1 && x == prev[y]) || (t == 2 && x == next[y])) continue; /* no change, skip */

            int px = prev[x], nx = next[x], py = prev[y], ny = next[y];
            if (t == 1) {
                link(px, nx);
                link(py, x);
                link(x, y);
            } else if (t == 2) {
                link(px, nx);
                link(y, x);
                link(x, ny);
            } else if (t == 3) {
                if (next[x] == y) {
                    link(px, y);
                    link(y, x);
                    link(x, ny);
                } else {
                    link(px, y);
                    link(y, nx);
                    link(py, x);
                    link(x, ny);
                }
            }
        }

        long long sum = 0, idx = 1;
        for (int i = next[0]; i != 0; i = next[i], idx++)
            if ((idx & 1) == 1) sum += i;
        if (!forward && (n & 1) == 0) sum = 1ll * n * (n + 1) / 2 - sum;
        printf("Case %d: %lld\n", ++kase, sum);
    }

    return 0;
}
