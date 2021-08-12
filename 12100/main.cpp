#include <cstdio>
#include <queue>
using namespace std;

int main() {
    int t, n, m, x;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        queue<pair<int, int>> q;
        vector<int> freq(10);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            q.push(make_pair(i, x));
            freq[x]++;
        }

        int idx = 0;
        for (;;) {
            auto& p = q.front();
            q.pop();

            bool ok = true;
            for (int i = p.second + 1; i <= 9; i++)
                if (freq[i]) {
                    ok = false;
                    break;
                }

            if (!ok) {
                q.push(p);
                continue;
            }

            freq[p.second]--;
            idx++;

            if (p.first == m) {
                printf("%d\n", idx);
                break;
            }
        }
    }

    return 0;
}
