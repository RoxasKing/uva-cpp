#include <cstdio>
#include <cstring>

const int maxn = 1e5;
const int maxw = 32;

char s[maxn];
int image[maxw][maxw], cnt, p;

void draw(int r, int c, int w) {
    char ch = s[p++];
    if (ch == 'p') {
        draw(r, c + w / 2, w / 2);         /* 1 */
        draw(r, c, w / 2);                 /* 2 */
        draw(r + w / 2, c, w / 2);         /* 3 */
        draw(r + w / 2, c + w / 2, w / 2); /* 4 */
    } else if (ch == 'f') {
        for (int i = r; i < r + w; i++) {
            for (int j = c; j < c + w; j++) {
                if (image[i][j] == 0) {
                    image[i][j] = 1;
                    cnt++;
                }
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(image, 0, sizeof(image));
        cnt = 0;
        for (int i = 0; i < 2; i++) {
            scanf("%s", s);
            p = 0;
            draw(0, 0, maxw);
        }
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}
