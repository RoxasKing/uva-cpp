#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    int t, n, x, y;
    unordered_map<int, vector<int>> points;
    unordered_set<int> sset;
    scanf("%d", &t);

    while (t--) {
        points.clear();
        sset.clear();
        scanf("%d", &n);
        while (n--) {
            scanf("%d%d", &x, &y);
            points[y].push_back(x);
        }

        bool ok = true;
        for (auto& it : points) {
            auto& arr = it.second;
            sort(arr.begin(), arr.end());
            int n = arr.size();
            for (int i = 0; i <= n >> 1; i++) {
                int sum = arr[i] + arr[n - 1 - i];
                sset.emplace(sum);
                if (sset.size() > 1) {
                    ok = false;
                    break;
                }
            }
        }

        ok ? printf("YES\n") : printf("NO\n");
    }

    return 0;
}
