#include <cstdio>
#include <map>
#include <queue>
using namespace std;

const int maxt = 1000 + 10;

int main() {
    int t, kase = 0;
    while (scanf("%d", &t) == 1 && t) {
        map<int, int> team;
        for (int i = 1; i <= t; i++) {
            int n, x;
            scanf("%d", &n);
            while (n--) {
                scanf("%d", &x);
                team[x] = i;
            }
        }

        printf("Scenario #%d\n", ++kase);

        queue<int> q, team_q[maxt];
        while (true) {
            char cmd[10];
            scanf("%s", cmd);

            if (cmd[0] == 'S') break;

            if (cmd[0] == 'D') {
                int t = q.front();
                printf("%d\n", team_q[t].front());
                team_q[t].pop();
                if (team_q[t].empty()) q.pop();
            } else if (cmd[0] == 'E') {
                int x;
                scanf("%d", &x);
                int t = team[x];
                if (team_q[t].empty()) q.push(t);
                team_q[t].push(x);
            }
        }

        printf("\n");
    }

    return 0;
}
