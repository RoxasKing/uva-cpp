#include <cstdio>

bool valid(int& w) {
    int w1, d1, w2, d2;
    bool l = true, r = true;
    scanf("%d%d%d%d", &w1, &d1, &w2, &d2);
    if (!w1) l = valid(w1);
    if (!w2) r = valid(w2);
    w = w1 + w2;
    return l && r && (w1 * d1 == w2 * d2);
}

int main() {
    int T, w;
    scanf("%d", &T);
    while (T--) {
        valid(w) ? puts("YES") : puts("NO");
        if (T) puts("");
    }

    return 0;
}
