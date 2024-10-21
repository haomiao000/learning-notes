#include <iostream>
#include <memory>

using namespace std;

class ListNode {
public:
    int val;
    shared_ptr<ListNode> next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class CircleList {
public:    
    shared_ptr<ListNode> head;
    CircleList() : head(nullptr) {}

    void insert(int val) {
        auto newNode = make_shared<ListNode>(val); 
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            return;
        }
        auto tmp = head;
        while (tmp->next != head) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->next = head;
    }

    void remove(int val) {
        while (head != nullptr && head->val == val) {
            auto d = this->head;
            if (head->next == head) {
                head = nullptr;
                return;
            }
            auto tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            head = head->next;
            tail->next = head;
        }

        auto tmp = head;
        while (tmp != nullptr && tmp->next != head) {
            if (tmp->next->val == val) {
                tmp->next = tmp->next->next;
            } else {
                tmp = tmp->next;
            }
        }
    }
    void modify(int val , int d) {
        if(this->head == nullptr) {
            return;
        }
        auto tmp = this->head;
        if(tmp->val == val) tmp->val = d;
        while(tmp->next != this->head) {
            if(tmp->next->val == val) {tmp->next->val = d;}
            tmp = tmp->next;
        }
    }

    void print() {
        if (head == nullptr) {
            cout << "list is empty" << endl;
            return;
        }
        auto tmp = head;
        do {
            cout << tmp->val << " ";
            tmp = tmp->next;
        } while (tmp != head);
        cout << endl;
    }
};

signed main() {
    CircleList list;
    list.insert(1);
    list.insert(1);
    list.insert(4);
    list.remove(1);
    list.print();
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.modify(2 , 3);
    list.print();
    return 0;
}