#include <cstdio>

int main() {
    int T, D, I;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &D, &I);
        int k = 1;
        for (int i = 1; i < D; i++) {
            if (I & 1) {
                k <<= 1;
                I = (I + 1) >> 1;
            } else {
                k = (k << 1) + 1;
                I >>= 1;
            }
        }
        printf("%d\n", k);
    }

    return 0;
}
