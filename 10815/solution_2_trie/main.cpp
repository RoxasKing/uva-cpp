#include <cstdio>
#include <cstdlib>
#include <cstring>
#define maxn 10000

char s[maxn], buf[maxn];

struct Trie {
    Trie* child[127];
    bool isEnd;
};

void Insert(Trie* t, int n) {
    for (int i = 0; i < n; i++) {
        if (!t->child[(int)buf[i]]) t->child[(int)buf[i]] = new Trie();
        t = t->child[(int)buf[i]];
    }
    t->isEnd = true;
}

void Print(Trie* t, int n) {
    if (t->isEnd && n) {
        buf[n] = '\0';
        printf("%s\n", buf);
    }
    for (int i = 0; i < 127; i++) {
        if (!t->child[i]) continue;
        buf[n] = i;
        Print(t->child[i], n + 1);
    }
}

int main() {
    Trie* t = new Trie();

    while (scanf("%s", s) != EOF) {
        int i = 0, j = 0;
        for (; s[i]; i++) {
            if ('A' <= s[i] && s[i] <= 'Z')
                buf[j++] = s[i] - 'A' + 'a';
            else if ('a' <= s[i] && s[i] <= 'z')
                buf[j++] = s[i];
            else {
                buf[j] = '\0';
                Insert(t, j);
                j = 0;
            }
        }
        buf[j] = 0;
        Insert(t, j);
    }

    Print(t, 0);

    return 0;
}
