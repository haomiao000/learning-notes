#include<bits/stdc++.h>

using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x) , next(nullptr) {}
};
class LinkList {
public:
    ListNode *head;
    LinkList() : head(nullptr) {}
    void insert(int val) {
        ListNode *newNode = new ListNode(val);
        if(this->head == nullptr) {
            this->head = newNode;
            return;
        }
        ListNode *tmp = this->head;
        while(tmp->next != nullptr) {
            tmp = tmp->next;
        }        
        tmp->next = newNode;
    }
    void reverse(int k) {
        ListNode *nowPos = this->head;
        ListNode *prev = nullptr;
        while(nowPos != nullptr && nowPos->next != nullptr) {
            int cnt = 1;
            ListNode *start = nowPos , *end = nowPos;
            while(cnt < k && end->next != nullptr) {
                end = end->next;
                cnt++;
            }
            ListNode *o = end->next;
            ListNode *now = start;
            ListNode *e = end->next;
            while(now != e) {
                ListNode *m = now;
                now = now->next;
                m->next = o;
                o = m;
            }
            if(prev == nullptr) {
                this->head = o;
            }else {
                prev->next = o;
            }
            nowPos = now;
            cnt = 1;
            prev = start;
        }
    }
    void print() {
        if(this->head == nullptr) {
            cout << "list is empty" << endl;
            return;
        }
        ListNode *tmp = this->head;
        while(tmp != nullptr) {
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


signed main() {
    LinkList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.print();
    list.reverse(3);
    list.print();
    return 0;
}