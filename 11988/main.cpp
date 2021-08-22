#include <cstdio>
#include <cstdlib>
#include <cstring>

struct ListNode {
    char* text;
    ListNode *prev, *next;
};

const int maxn = 1e5;
char buf[maxn];

int main() {
    while (scanf("%s", buf) == 1 && buf[0] != EOF) {
        ListNode* head = new ListNode();
        ListNode* tail = new ListNode();
        head->next = tail;
        tail->prev = head;

        int i = 0, j = 0, n = strlen(buf), flg = 0;
        while (i < n) {
            if (buf[i] == '[') {
                flg = 1;
                i++;
            } else if (buf[i] == ']') {
                flg = 0;
                i++;
            } else {
                for (j = i; j < n && buf[j] != '[' && buf[j] != ']'; j++)
                    ;
                ListNode* node = new ListNode();
                node->text = (char*)malloc(sizeof(char) * (j - i + 1));
                memcpy(node->text, buf + i, sizeof(char) * (j - i));
                node->text[j - i] = '\0';
                if (flg) {
                    node->next = head->next;
                    head->next->prev = node;
                    node->prev = head;
                    head->next = node;
                } else {
                    node->prev = tail->prev;
                    tail->prev->next = node;
                    node->next = tail;
                    tail->prev = node;
                }
                i = j;
            }
        }

        for (ListNode* ptr = head->next; ptr != tail; ptr = ptr->next) {
            printf("%s", ptr->text);
            // ListNode* pre = ptr->prev;
            // if (pre->text != nullptr) free(pre->text);
            // free(pre);
        }
        // free(tail);
        puts("");
    }

    return 0;
}
