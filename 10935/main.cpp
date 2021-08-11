#include <cstdio>
using namespace std;

const int maxn = 200;

int arr[maxn];

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) arr[i] = i + 1;

        printf("Discarded cards:");
        int l = 0, r = n;
        while (r - l > 1) {
            if (l) printf(",");
            printf(" %d", arr[l++]);
            arr[r++] = arr[l++];
        }
        printf("\nRemaining card: %d\n", arr[l]);
    }

    return 0;
}
