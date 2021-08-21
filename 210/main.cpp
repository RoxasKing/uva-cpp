#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const int maxp = 30;
const int maxq = 1e3;

struct Program {
    string q[maxp];
    int t[maxp], l, r;
} ps[maxq];

int wait_q[maxq], wait_l, wait_r;
int block_q[maxq], block_l, block_r;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, t[5], Q;
        scanf("%d%d%d%d%d%d%d", &n, &t[0], &t[1], &t[2], &t[3], &t[4], &Q);
        getchar();

        wait_l = 0, wait_r = -1;
        block_l = 0, block_r = -1;
        for (int i = 0; i < n; i++) {
            wait_q[++wait_r] = i;

            Program& p = ps[i];
            int &l = p.l, &r = p.r;
            l = 0, r = -1;
            while (getline(cin, p.q[++r])) {
                if ((int)p.q[r].find("=") != -1) { /* assignment */
                    p.t[r] = 0;
                } else if (p.q[r][0] == 'p') { /* output */
                    p.t[r] = 1;
                } else if (p.q[r][0] == 'l') { /* begin mutual execlusion */
                    p.t[r] = 2;
                } else if (p.q[r][0] == 'u') { /* end mutual execlusion */
                    p.t[r] = 3;
                } else { /* stop execution */
                    p.t[r] = 4;
                    break;
                }
            }
        }

        vector<int> dict(26);
        bool locking = false;

        while (wait_l <= wait_r) {
            int id = wait_q[wait_l++];
            Program& p = ps[id];
            int in_wait_q = true;
            int remain = Q;
            while (remain > 0) {
                int& l = p.l;
                int typ = p.t[l];
                remain -= t[typ];
                string& exp = p.q[l];
                if (typ == 0) {
                    int key = exp[0] - 'a', val = 0;
                    for (int i = 4; i < (int)exp.size(); i++) val = val * 10 + exp[i] - '0';
                    dict[key] = val;
                } else if (typ == 1) {
                    int key = exp[6] - 'a';
                    printf("%d: %d\n", id + 1, dict[key]);
                } else if (typ == 2) {
                    if (locking) {
                        block_q[++block_r] = id;
                        in_wait_q = false;
                        break;
                    }
                    locking = true;
                } else if (typ == 3) {
                    locking = false;
                    if (block_l <= block_r) wait_q[--wait_l] = block_q[block_l++];
                } else {
                    in_wait_q = false;
                    break;
                }
                l++;
            }
            if (in_wait_q) wait_q[++wait_r] = id;
        }

        if (T) puts("");
    }

    return 0;
}
