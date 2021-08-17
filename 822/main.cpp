#include <algorithm>
#include <cstdio>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Topic {
    int num, t0, t, dt;
    int remain;
    Topic() {}
    Topic(int num, int t0, int t, int dt) : num(num), t0(t0), t(t), dt(dt) { remain = 0; }
};

struct Staff {
    int pid, st, et;
    Staff() {}
    Staff(int pid, int st, int et) : pid(pid), st(st), et(et) {}
};

auto cmp1 = [](const Staff& a, const Staff& b) -> bool {
    return a.et > b.et;
};

auto cmp2 = [](const Staff& a, const Staff& b) -> bool {
    if (a.st != b.st) return a.st > b.st;
    return a.pid > b.pid;
};

int main() {
    int n, kase = 0;
    while (scanf("%d", &n) == 1 && n) {
        unordered_map<int, Topic> topic_map;
        unordered_map<int, vector<int>> pid_tid_map;
        priority_queue<Staff, vector<Staff>, decltype(cmp1)> work_q(cmp1);
        priority_queue<Staff, vector<Staff>, decltype(cmp2)> free_q(cmp2);

        int tid, num, t0, t, dt;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d%d", &tid, &num, &t0, &t, &dt);
            topic_map.emplace(tid, Topic(num, t0, t, dt));
        }

        int m, pid, k;
        scanf("%d", &m);
        while (m--) {
            scanf("%d%d", &pid, &k);
            vector<int> tids;
            while (k--) {
                scanf("%d", &tid);
                tids.push_back(tid);
            }
            pid_tid_map.emplace(pid, tids);
            free_q.push(Staff(pid, 0, 0));
        }

        int time = 0;
        while (true) {
            int next = 2000000009;

            for (auto& it : topic_map) {
                auto& topic = it.second;
                if (topic.t0 == time && topic.num) {
                    topic.num--;
                    topic.remain++;
                    if (topic.num) topic.t0 += topic.dt;
                }
                if (topic.t0 > time) next = min(next, topic.t0);
            }

            while (!work_q.empty() && work_q.top().et == time) {
                auto staff = work_q.top();
                work_q.pop();
                free_q.push(staff);
            }

            vector<Staff> tmp;
            while (!free_q.empty()) {
                auto staff = free_q.top();
                int pid = staff.pid;
                bool work = false;
                for (auto tid : pid_tid_map[pid]) {
                    auto& topic = topic_map[tid];
                    if (topic.remain) {
                        topic.remain--;
                        work_q.push(Staff(pid, time, time + topic.t));
                        work = true;
                        break;
                    }
                }
                free_q.pop();
                if (!work) tmp.push_back(staff);
            }
            for (auto& staff : tmp) free_q.push(staff);

            if (!work_q.empty()) next = min(next, work_q.top().et);

            if (next == 2000000009) break;
            time = next;
        }

        printf("Scenario %d: All requests are serviced within %d minutes.\n", ++kase, time);
    }

    return 0;
}
