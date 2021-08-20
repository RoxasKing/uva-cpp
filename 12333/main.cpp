#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e5;
const int BASE = 1e9;
const int W = 9;

struct Trie {
    vector<Trie*> child;
    int index;
    Trie(int index = -1) : index(index) { child = vector<Trie*>(10, nullptr); }
};

void insert(Trie* t, const vector<int>& x, int index) {
    for (int i = 0; i < (int)x.size(); i++) {
        int idx = x[i];
        if (t->child[idx] == nullptr) t->child[idx] = new Trie();
        t = t->child[idx];
        if (t->index == -1) t->index = index;
    }
}

int query(Trie* t, const vector<int>& x) {
    for (int i = 0; i < (int)x.size(); i++) {
        int idx = x[i];
        if (t->child[idx] == nullptr) return -1;
        t = t->child[idx];
    }
    return t->index;
}

int main() {
    Trie* root = new Trie();
    vector<int> a, b;
    a.push_back(1);
    b.push_back(1);
    insert(root, a, 0);
    for (int i = 2; i < MAXN; i++) {
        int len = max((int)a.size(), (int)b.size());
        vector<int> c(len);
        for (int i = 0; i < len; i++) {
            if (i < (int)a.size()) c[i] += a[i];
            if (i < (int)b.size()) c[i] += b[i];
            if (c[i] >= BASE) {
                if (i + 1 == (int)c.size()) c.push_back(0);
                c[i + 1] += 1;
                c[i] -= BASE;
            }
        }
        vector<int> x;
        for (int i = c.size() - 1; i >= 0 && x.size() < 40; i--) {
            vector<int> tmp;
            for (int num = c[i]; num; num /= 10) tmp.push_back(num % 10);
            if (i < (int)c.size() - 1)
                while (tmp.size() < W) tmp.push_back(0);
            for (int j = tmp.size() - 1; j >= 0 && x.size() < 40; j--) x.push_back(tmp[j]);
        }
        insert(root, x, i);
        a = b;
        b = c;
    }

    int n;
    char s[41];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        vector<int> x;
        for (int i = 0; s[i]; i++) x.push_back(s[i] - '0');
        printf("Case #%d: %d\n", i, query(root, x));
    }

    return 0;
}
