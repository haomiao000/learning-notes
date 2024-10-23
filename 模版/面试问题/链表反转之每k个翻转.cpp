#include <bits/stdc++.h>

using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkList {
public:
    ListNode *head;
    LinkList() : head(nullptr) {}

    void insert(int val) {
        if (this->head == nullptr) {
            this->head = new ListNode(val);
            return;
        }
        ListNode *tmp = this->head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new ListNode(val);
    }

    // 翻转整个链表或者指定区间
    void reverse(int l = -1, int r = -1) {
        if (l == -1 && r == -1) { // 没有传入参数，翻转整个链表
            ListNode *now = this->head;
            ListNode *o = nullptr;
            while (now != nullptr) {
                ListNode *tmp = now;
                now = now->next;
                tmp->next = o;
                o = tmp;
            }
            this->head = o;
        } else { // 翻转指定区间 l 到 r
            if (l >= r || l < 1) return; // 参数无效，直接返回

            ListNode *prev = nullptr, *curr = this->head;
            int position = 1;
            
            // 找到起始节点 l 前的节点
            while (curr != nullptr && position < l) {
                prev = curr;
                curr = curr->next;
                position++;
            }
            
            ListNode *start = prev;    // l-1 节点
            ListNode *tail = curr;     // l 节点（将变成翻转后的尾节点）

            // 翻转从 l 到 r 的节点
            ListNode *next = nullptr;
            while (curr != nullptr && position <= r) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
                position++;
            }

            // 连接前后部分
            if (start != nullptr) {
                start->next = prev;    // l-1 节点指向 r 节点
            } else {
                this->head = prev;     // l 为 1 时，更新 head
            }
            tail->next = curr;         // l 节点指向 r+1 节点
        }
    }

    // 每 K 个节点进行反转
    void reverseEveryK(int k) {
        if (k <= 1 || this->head == nullptr) return;

        ListNode *prevTail = nullptr, *curr = this->head, *newHead = nullptr;

        while (curr != nullptr) {
            int count = 0;
            ListNode *prev = nullptr, *start = curr;

            // 翻转 K 个节点
            while (curr != nullptr && count < k) {
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
                count++;
            }

            // 如果是第一次翻转，需要更新链表头
            if (newHead == nullptr) {
                newHead = prev;
            }

            // 连接上一次翻转后的尾部
            if (prevTail != nullptr) {
                prevTail->next = prev;
            }

            // 保存当前段的尾部，用于下一段的连接
            prevTail = start;
        }

        // 更新链表头
        this->head = newHead;
    }

    void print() {
        if (this->head == nullptr) {
            cout << "list is empty" << endl;
            return;
        }
        ListNode *tmp = this->head;
        while (tmp != nullptr) {
            cout << tmp->val << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    ~LinkList() {
        ListNode *tmp = head;
        while(head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};


int main() {
    LinkList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.insert(7);

    // 打印原始链表
    cout << "Original List: ";
    list.print();

    // 翻转整个链表
    list.reverse();
    cout << "Reversed Entire List: ";
    list.print();

    // 每 3 个节点翻转一次
    list.reverseEveryK(3);
    cout << "Reversed Every 3 Nodes: ";
    list.print();

    return 0;
}