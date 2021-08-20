#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct Patient {
    char name[9];     /* Last name of patient */
    int su_t, re_t;   /* times required for surgery , times required in the recovery room */
    int r_id, b_id;   /* room id, bed id */
    int op_st, op_ed; /* operating begin and end */
    int re_st, re_ed; /* recovery begin and end */
} ps[100];

auto cmp_op = [](Patient* a, Patient* b) -> bool {
    return a->op_ed != b->op_ed ? a->op_ed > b->op_ed : a->r_id > b->r_id;
};

auto cmp_re = [](Patient* a, Patient* b) -> bool { return a->re_ed > b->re_ed; };

int main() {
    int n, m, T, t1, t2, t3, k;
    while (scanf("%d%d%d%d%d%d%d", &n, &m, &T, &t1, &t2, &t3, &k) == 7) {
        for (int i = 0; i < k; i++) scanf("%s%d%d", ps[i].name, &ps[i].su_t, &ps[i].re_t);
        /* room's next free time | room's used time | bed's next free time | bed's use time */
        vector<int> r(n), r_c(n), b(m), b_c(m);
        priority_queue<Patient*, vector<Patient*>, decltype(cmp_op)> op_q(cmp_op); /* oprating queue */
        priority_queue<Patient*, vector<Patient*>, decltype(cmp_re)> re_q(cmp_re); /* recovery queue */
        int idx = 0, last = T * 60;

        while (last != 1e9 && (!re_q.empty() || !op_q.empty() || idx < k)) {
            while (!re_q.empty() && re_q.top()->re_ed == last) re_q.pop();
            while (!op_q.empty() && op_q.top()->op_ed == last) {
                int i = 0;
                while (i < m && b[i] > last) i++;
                Patient* p = op_q.top();
                op_q.pop();
                p->b_id = i;
                p->re_st = last + t1;
                p->re_ed = p->re_st + p->re_t;
                re_q.push(p);
                b[i] = p->re_ed + t3;
                b_c[i] += p->re_t;
            }
            while (idx < k) {
                int i = 0;
                while (i < n && r[i] > last) i++;
                if (i == n) break;
                Patient* p = &ps[idx++];
                p->r_id = i;
                p->op_st = last;
                p->op_ed = last + p->su_t;
                op_q.push(p);
                r[i] = p->op_ed + t2;
                r_c[i] += p->su_t;
            }
            int next = 1e9;
            if (!op_q.empty()) next = min(next, op_q.top()->op_ed);
            if (!re_q.empty()) next = min(next, re_q.top()->re_ed);
            for (int i = 0; i < n; i++) r[i] > last ? next = min(next, r[i]) : 0;
            for (int i = 0; i < m; i++) b[i] > last ? next = min(next, b[i]) : 0;
            last = next;
        }

        puts(" Patient          Operating Room          Recovery Room");
        puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
        puts(" ------------------------------------------------------");
        int st = 1e9, ed = 0;
        for (int i = 0; i < k; i++) {
            printf("%2d  %-8s", i + 1, ps[i].name);
            printf("%4d", ps[i].r_id + 1);
            printf("%5d:%02d", ps[i].op_st / 60, ps[i].op_st % 60);
            printf("%5d:%02d", ps[i].op_ed / 60, ps[i].op_ed % 60);
            printf("%7d", ps[i].b_id + 1);
            printf("%5d:%02d", ps[i].re_st / 60, ps[i].re_st % 60);
            printf("%5d:%02d", ps[i].re_ed / 60, ps[i].re_ed % 60);
            puts("");
            st = min(st, ps[i].op_st);
            ed = max(ed, ps[i].re_ed);
        }
        puts("\nFacility Utilization\nType  # Minutes  % Used\n-------------------------");
        for (int i = 0; i < n; i++)
            printf("Room %2d%8d%8.2f\n", i + 1, r_c[i], fabs((double)(r_c[i] * 100) / (ed - st)));
        for (int i = 0; i < m; i++)
            printf("Bed  %2d%8d%8.2f\n", i + 1, b_c[i], fabs((double)(b_c[i] * 100) / (ed - st)));
        puts("");
    }

    return 0;
}
