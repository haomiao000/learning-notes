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
        }else {
            ListNode *tmp = this->head;
            while(tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
    }
    bool Check() {
        if(this->head == nullptr || this->head->next == nullptr) {
            return false;
        } 
        ListNode *slow = this->head;
        ListNode *fast = this->head;
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
                return true;
            }
        }
        return fast;
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

    // 手动制造环，4->2
    list.head->next->next->next->next = list.head->next;

    if (list.Check()) {
        cout << "The linked list has a cycle." << endl;
    } else {
        cout << "The linked list has no cycle." << endl;
    }


    return 0;
}