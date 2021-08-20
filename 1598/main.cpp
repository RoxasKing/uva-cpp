#include <cstdio>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Price {
    int price, idx;
    Price(int price = 0, int idx = 0) : price(price), idx(idx) {}
};

auto cmp_bid = [](const Price& a, const Price& b) -> bool {
    return (a.price != b.price) ? a.price < b.price : a.idx > b.idx;
};

auto cmp_ask = [](const Price& a, const Price& b) -> bool {
    return (a.price != b.price) ? a.price > b.price : a.idx > b.idx;
};

struct Order {
    char type;
    int size, price;
    Order(char type = 'C', int size = 0, int price = 0) : type(type), size(size), price(price) {}
};

const int maxn = 10001;
Order orders[maxn];
unordered_map<int, int> bid_n, ask_n;

int main() {
    int n, kase = 0;
    while (scanf("%d", &n) == 1) {
        if (kase++) {
            printf("\n");
            bid_n.clear();
            ask_n.clear();
        }

        int q, p, x;
        char type[10];
        priority_queue<Price, vector<Price>, decltype(cmp_bid)> bid_q(cmp_bid);
        priority_queue<Price, vector<Price>, decltype(cmp_ask)> ask_q(cmp_ask);

        for (int i = 1; i <= n; i++) {
            scanf("%s", type);
            type[0] != 'C' ? scanf("%d%d", &q, &p) : scanf("%d", &x);

            if (type[0] == 'B') {
                while (q && !ask_q.empty() && ask_q.top().price <= p) {
                    Price ask = ask_q.top();
                    if (orders[ask.idx].size == 0) {
                        ask_q.pop();
                        continue;
                    }
                    int size = min(q, orders[ask.idx].size);
                    q -= size;
                    orders[ask.idx].size -= size;
                    ask_n[ask.price] -= size;
                    if (orders[ask.idx].size == 0) ask_q.pop();
                    printf("TRADE %d %d\n", size, ask.price);
                }
                orders[i] = Order('B', q, p);
                if (q) {
                    bid_q.push(Price(p, i));
                    bid_n[p] += q;
                }
            } else if (type[0] == 'S') {
                while (q && !bid_q.empty() && bid_q.top().price >= p) {
                    Price bid = bid_q.top();
                    if (orders[bid.idx].size == 0) {
                        bid_q.pop();
                        continue;
                    }
                    int size = min(q, orders[bid.idx].size);
                    q -= size;
                    orders[bid.idx].size -= size;
                    bid_n[bid.price] -= size;
                    if (orders[bid.idx].size == 0) bid_q.pop();
                    printf("TRADE %d %d\n", size, bid.price);
                }
                orders[i] = Order('S', q, p);
                if (q) {
                    ask_q.push(Price(p, i));
                    ask_n[p] += q;
                }
            } else {
                int size = orders[x].size;
                orders[x].size -= size;
                if (orders[x].type == 'B')
                    bid_n[orders[x].price] -= size;
                else if (orders[x].type == 'S')
                    ask_n[orders[x].price] -= size;
            }

            int bid_size = 0, bid_price = 0, ask_size = 0, ask_price = 99999;
            while (!bid_q.empty()) {
                Price bid = bid_q.top();
                if (orders[bid.idx].size) {
                    bid_size = bid_n[bid.price];
                    bid_price = bid.price;
                    break;
                }
                bid_q.pop();
            }
            while (!ask_q.empty()) {
                Price ask = ask_q.top();
                if (orders[ask.idx].size) {
                    ask_size = ask_n[ask.price];
                    ask_price = ask.price;
                    break;
                }
                ask_q.pop();
            }
            printf("QUOTE %d %d - %d %d\n", bid_size, bid_price, ask_size, ask_price);
        }
    }

    return 0;
}
