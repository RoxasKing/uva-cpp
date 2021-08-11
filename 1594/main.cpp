#include <cmath>
#include <cstdio>
using namespace std;

const int limit = 1000;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);

        bool ok = false;
        for (int i = 0; i < limit; i++) {
            int cnt = 0, tmp = a[0];
            for (int j = 0; j < n - 1; j++) {
                a[j] = abs(a[j] - a[j + 1]);
                if (a[j] == 0) cnt++;
            }
            a[n - 1] = abs(a[n - 1] - tmp);
            if (a[n - 1] == 0) cnt++;
            if (cnt == n) {
                ok = true;
                break;
            }
        }
        ok ? printf("ZERO\n") : printf("LOOP\n");
    }

    return 0;
}
