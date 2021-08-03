#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define PLACES 70
#define MAX_PLAYERS 144
#define NAME_LEN 20

double purse, pct[PLACES];

struct Player {
    char name[NAME_LEN + 1];
    int sc[4], h36, h72;
    bool r2, r3, r4;
    bool amateur;
} ps[MAX_PLAYERS];

bool cmp1(const Player& p1, const Player& p2) {
    return p1.h36 < p2.h36;
}

bool cmp2(const Player& p1, const Player& p2) {
    if (p1.r3 != p2.r3) return p1.r3 > p2.r3;
    if (p1.r4 != p2.r4) return p1.r4 > p2.r4;
    if (p1.h72 != p2.h72) return p1.h72 < p2.h72;
    return strcmp(p1.name, p2.name) < 0;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%lf", &purse);
        for (int i = 0; i < PLACES; i++) scanf("%lf", &pct[i]);

        int n, len = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            memset(ps[len].sc, 0, sizeof(ps[len].sc));
            ps[len].name[NAME_LEN] = '\0';
            ps[len].h36 = ps[len].h72 = 0;
            ps[len].r2 = ps[len].r3 = ps[len].r4 = false;
            ps[len].amateur = false;

            char ch, buf[4];
            buf[3] = '\0';

            while ((ch = getchar()) == '\n' || ch == '\t' || ch == ' ')
                ;
            ps[len].name[0] = ch;
            for (int j = 1; j < NAME_LEN; j++) {
                ps[len].name[j] = getchar();
                if (ps[len].name[j] == '*')
                    ps[len].amateur = true;
            }

            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 3; k++) buf[k] = getchar();
                if (strcmp(buf, " DQ") == 0) break;
                ps[len].sc[j] = atoi(buf);
                if (j < 2) ps[len].h36 += ps[len].sc[j];
                ps[len].h72 += ps[len].sc[j];
                if (j == 1) ps[len].r2 = true;
                if (j == 2) ps[len].r3 = true;
                if (j == 3) ps[len].r4 = true;
            }

            if (ps[len].r2) len++;
        }

        sort(ps, ps + len, cmp1);

        if (len > 70) {
            int idx = 69;
            while (idx + 1 < len && ps[idx].h36 == ps[idx + 1].h36) idx++;
            len = idx + 1;
        }

        sort(ps, ps + len, cmp2);

        printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
        printf("-----------------------------------------------------------------------\n");

        int i = 0, j = 0;
        while (i < len) {
            bool have_prize = false;
            int k = i, cnt = 0, total = ps[i].h72;
            double pcts = 0.0;
            while (k < len && ps[k].h72 == total) {
                if (!ps[k].amateur) {
                    cnt++;
                    if (j < PLACES) {
                        pcts += pct[j++];
                        have_prize = true;
                    }
                }
                k++;
            }

            char prize[10];
            sprintf(prize, "%6.2lf", purse * pcts / cnt / 100);
            int plc = i + 1;

            char buf[10];
            for (; i < k; i++) {
                printf("%-21s", ps[i].name);
                if (!ps[i].r4) {
                    printf("          ");
                } else if (ps[i].amateur || cnt == 1 || !have_prize) {
                    printf("%-10d", plc);
                } else {
                    sprintf(buf, "%dT", plc);
                    printf("%-10s", buf);
                }
                for (int j = 0; j < 2; j++) printf("%-5d", ps[i].sc[j]);
                ps[i].r3 ? printf("%-5d", ps[i].sc[2]) : printf("     ");
                ps[i].r4 ? printf("%-5d", ps[i].sc[3]) : printf("     ");
                if (!ps[i].r4) {
                    printf("DQ");
                } else if (ps[i].amateur || !have_prize) {
                    printf("%d", ps[i].h72);
                } else {
                    printf("%-10d", ps[i].h72);
                    printf("$%9s", prize);
                }
                printf("\n");
            }
        }
        if (t) printf("\n");
    }

    return 0;
}
