// Tags:
// Dynamic Programming

#include <algorithm>
#include <cstdio>
#define target 1500

using namespace std;

typedef long long LL;

int f[target + 1];

int main() {
    f[1] = 1;

    int mul2, mul3, mul5;
    mul2 = mul3 = mul5 = 1;

    for (int i = 2; i <= 1500; i++) {
        f[i] = min(f[mul2] * 2, min(f[mul3] * 3, f[mul5] * 5));
        if (f[mul2] * 2 <= f[i]) mul2++;
        if (f[mul3] * 3 <= f[i]) mul3++;
        if (f[mul5] * 5 <= f[i]) mul5++;
    }

    printf("The 1500'th ugly number is %d.\n", f[target]);

    return 0;
}
