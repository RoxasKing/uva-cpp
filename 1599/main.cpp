#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <vector>
using namespace std;

const int maxn = 1e5 + 1;
const int maxm = 2e6 + 1;

int d[maxn];
vector<int> G[maxn];
int q[maxm], head, tail;

struct Edge {
    int u, v, c;
    Edge(int u, int v, int w) : u(u), v(v), c(w) {}
};

vector<Edge> edges;

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        for (int i = 1; i <= n; i++) G[i].clear();
        edges.clear();
        while (m--) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            G[u].push_back(edges.size());
            edges.push_back(Edge(u, v, c));
            G[v].push_back(edges.size());
            edges.push_back(Edge(v, u, c));
        }
        for (int i = 1; i < n; i++) d[i] = 1e9 + 1;
        d[n] = 0;
        q[0] = n;
        head = tail = 0;
        while (head <= tail) {
            int v = q[head++];
            for (int i = 0; i < (int)G[v].size(); i++) {
                int e = G[v][i];
                int u = edges[e].v;
                if (d[u] <= d[v] + 1) continue;
                d[u] = d[v] + 1;
                q[++tail] = u;
            }
        }
        unordered_set<int> next;
        next.emplace(1);
        int first = 1;
        printf("%d\n", d[1]);
        for (int i = 0; i < d[1]; i++) {
            unordered_set<int> tmp;
            int min_color = 1e9 + 1;
            for (auto& u : next) {
                for (int k = 0; k < (int)G[u].size(); k++) {
                    int e = G[u][k];
                    int v = edges[e].v;
                    if (d[u] != d[v] + 1) continue;
                    if (edges[e].c == min_color) {
                        tmp.emplace(v);
                    } else if (edges[e].c < min_color) {
                        tmp = {v};
                        min_color = edges[e].c;
                    }
                }
            }
            first ? first = 0 : putchar(' ');
            printf("%d", min_color);
            next = tmp;
        }
        puts("");
    }
    return 0;
}
