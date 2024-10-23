#include<bits/stdc++.h>

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

    // 打印原始链表
    list.print();

    // 翻转整个链表
    list.reverse();
    list.print();

    // 翻转从第 2 到第 4 个节点
    list.reverse(1, 4);
    list.print();

    // 翻转整个链表
    list.reverse();
    list.print();

    return 0;
}