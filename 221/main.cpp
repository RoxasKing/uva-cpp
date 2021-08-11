#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100 + 1;

int n;
double x[maxn * 2];

struct Building {
    int id;
    double x, y, w, d, h;
    bool operator<(const Building& b) const { return x < b.x || (x == b.x && y < b.y); }
} bs[maxn];

bool cover(int i, double mx) { return bs[i].x <= mx && bs[i].x + bs[i].w >= mx; }

bool visible(int i, double mx) {
    if (!cover(i, mx)) return false;
    for (int k = 0; k < n; k++)
        if (bs[k].y < bs[i].y && bs[k].h >= bs[i].h && cover(k, mx)) return false;
    return true;
}

int main() {
    int kase = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf%lf%lf%lf", &bs[i].x, &bs[i].y, &bs[i].w, &bs[i].d, &bs[i].h);
            x[i * 2] = bs[i].x;
            x[i * 2 + 1] = bs[i].x + bs[i].w;
            bs[i].id = i + 1;
        }

        sort(bs, bs + n);
        sort(x, x + n * 2);
        int m = unique(x, x + n * 2) - x;

        if (kase) printf("\n");
        printf("For map #%d, the visible buildings are numbered as follows:\n%d", ++kase, bs[0].id);
        for (int i = 1; i < n; i++) {
            bool ok = false;
            for (int j = 0; j < m - 1; j++) {
                if (visible(i, (x[j] + x[j + 1]) / 2)) {
                    ok = true;
                    break;
                }
            }
            if (ok) printf(" %d", bs[i].id);
        }
        printf("\n");
    }

    return 0;
}
