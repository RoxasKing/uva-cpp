#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int maxn = 1e5 + 1;

int inorder[maxn], postorder[maxn];
int inorder_map[maxn], post_idx;
int l_sub[maxn], r_sub[maxn];
int best_sum, best;

int build(int l, int r) {
    if (l > r) return 0;
    int root = postorder[post_idx--];
    int mid = inorder_map[root];
    r_sub[root] = build(mid + 1, r);
    l_sub[root] = build(l, mid - 1);
    return root;
}

void dfs(int node, int cur_sum) {
    cur_sum += node;
    if (!l_sub[node] && !r_sub[node] && (cur_sum < best_sum || (cur_sum == best_sum && node < best)))
        best_sum = cur_sum, best = node;
    if (l_sub[node]) dfs(l_sub[node], cur_sum);
    if (r_sub[node]) dfs(r_sub[node], cur_sum);
}

int main() {
    string s;
    stringstream ss;

    while (getline(cin, s)) {
        int n = 0, x;
        ss = stringstream(s);
        while (ss >> x) {
            inorder_map[x] = ++n;
            inorder[n] = x;
        }
        getline(cin, s);
        ss = stringstream(s);
        for (int i = 1; i <= n; i++) ss >> postorder[i];
        post_idx = n;
        int root = build(1, n);
        best_sum = 1e9, best = -1;
        dfs(root, 0);
        cout << best << "\n";
    }

    return 0;
}
