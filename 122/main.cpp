#include <cstdio>
#include <cstring>

const int maxn = 1e4;
char s[maxn];

struct Node {
    int exist, value;
    Node *left, *right;
    Node() : exist(false), left(nullptr), right(nullptr) {}
};

Node *root, *q[maxn];
int head, tail, vals[maxn], size;

bool add(int val, char *s) {
    int n = strlen(s);
    Node *p = root;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'L') {
            if (p->left == nullptr) p->left = new Node();
            p = p->left;
        } else {
            if (p->right == nullptr) p->right = new Node();
            p = p->right;
        }
    }
    if (p->exist) return false;
    p->exist = true;
    p->value = val;
    return true;
}

void rm_tree(Node *p) {
    if (p == nullptr) return;
    rm_tree(p->left);
    rm_tree(p->right);
    delete p;
}

bool bfs() {
    head = tail = size = 0;
    q[tail] = root;
    while (head <= tail) {
        Node *p = q[head++];
        if (!p->exist) return false;
        vals[size++] = p->value;
        if (p->left) q[++tail] = p->left;
        if (p->right) q[++tail] = p->right;
    }
    return true;
}

int main() {
    while (1) {
        rm_tree(root);
        root = new Node();
        int valid = true;
        while (1) {
            if (scanf("%s", s) != 1) goto END;
            if (!strcmp(s, "()")) break;
            int val;
            sscanf(&s[1], "%d", &val);
            int ok = add(val, strchr(s, ',') + 1);
            if (!ok) {
                valid = false;
                break;
            }
        }
        if (!valid)
            while (scanf("%s", s) && strcmp(s, "()"))
                ;
        if (valid && bfs()) {
            for (int i = 0; i < size; i++) {
                if (i) putchar(' ');
                printf("%d", vals[i]);
            }
        } else {
            printf("not complete");
        }
        puts("");
    }
END:
    return 0;
}
