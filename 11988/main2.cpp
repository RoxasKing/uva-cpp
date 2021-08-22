#include <cstdio>
#include <cstring>

const int maxn = 1e5 + 1;

int next[maxn], ptr, tail;

char s[maxn];

int main() {
    while (scanf("%s", s + 1) == 1 && s[0] != EOF) {
        int n = strlen(s + 1);
        next[0] = 0;
        ptr = tail = 0;

        for (int i = 1; i <= n; i++) {
            char ch = s[i];
            if (ch == '[') {
                ptr = 0;
            } else if (ch == ']') {
                ptr = tail;
            } else {
                next[i] = next[ptr];
                next[ptr] = i;
                if (ptr == tail) tail = i;
                ptr = i;
            }
        }

        for (int i = next[0]; i != 0; i = next[i]) putchar(s[i]);
        puts("");
    }

    return 0;
}
