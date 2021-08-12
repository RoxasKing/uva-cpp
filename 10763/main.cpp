#include <cstdio>
#include <unordered_map>
using namespace std;

const int sed = 1e5 + 1;

int main() {
    int n, a, b;
    unordered_map<long long, int> freq;
    while (scanf("%d", &n) == 1 && n) {
        freq.clear();
        while (n--) {
            scanf("%d%d", &a, &b);
            if (a < b) {
                long long key = 1LL * a * sed + b;
                freq[key]++;
            } else {
                long long key = 1LL * b * sed + a;
                freq[key]--;
            }
        }
        bool ok = true;
        for (auto& it : freq) {
            if (it.second != 0) {
                ok = false;
                break;
            }
        }
        ok ? printf("YES\n") : printf("NO\n");
    }

    return 0;
}
