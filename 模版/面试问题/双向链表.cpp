#include<bits/stdc++.h>
using namespace std;
class ListNode {
public:
    int val;
    ListNode *next , *pre;
    ListNode(int x) : val(x) , next(nullptr) , pre(nullptr) {}
};
class DoublyLinkList{
public:
    ListNode *head , *tail;
    DoublyLinkList() : head(nullptr) , tail(nullptr) {}
    void append(int val) {
        ListNode *newNode = new ListNode(val);
        if(this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        }else {
            this->tail->next = newNode;
            newNode->pre = this->tail;
            this->tail = newNode;
        }
    }
    void preAppend(int val) {
        ListNode *newNode = new ListNode(val);
        if(this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        }else {
            newNode->next = this->head;
            this->head->pre = newNode;
            this->head = newNode;
        }
    }
    void deleteNode(int val) {
        while(this->head != nullptr && this->head->val == val) {
            ListNode *tmp = this->head;
            this->head = this->head->next;
            delete tmp;
            tmp = nullptr;
        }
        if(this->head == nullptr) {
            this->tail = nullptr;
            return; 
        }
        this->head->pre = nullptr;
        if(this->head->next == nullptr) {
            this->tail = this->head;
            return;
        }
        ListNode *tmp = this->head;
        while(tmp->next != nullptr) {
            if(tmp->next->val == val) {
                ListNode *d = tmp->next;
                tmp->next = tmp->next->next;
                if(d == this->tail) {
                    this->tail = tmp;
                }else {
                    tmp->next->pre = tmp;
                }
                delete d;
                d = nullptr;
            }else {
                tmp = tmp->next;
            }
        }
    }
    void modify(int val , int d) {
        ListNode *tmp = this->head;
        while(tmp != nullptr) {
            if(tmp->val == val) {
                tmp->val = d;
            }
            tmp = tmp->next;
        }
    }
    void Print() {
        ListNode *tmp = this->head;
        while(tmp != nullptr) {
            cout << tmp->val << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void RePrint() {
        ListNode *tmp = this->tail;
        while(tmp != nullptr) {
            cout << tmp->val << " ";
            tmp = tmp->pre;
        }
        cout << endl;
    }
    
    ~DoublyLinkList() {
        ListNode *tmp = this->head;
        while(this->head != nullptr) {
            this->head = head->next;
            delete tmp;
            tmp = this->head;
        }
    }
};
signed main() {
    DoublyLinkList list;
    list.append(2);
    list.append(1);
    list.append(3);
    list.append(4);
    list.append(2);
    list.Print();
    list.RePrint();
    list.deleteNode(1);
    list.Print();
    list.RePrint();
    list.append(3);
    list.preAppend(1);
    list.Print();
    list.RePrint();
    list.deleteNode(1);
    list.deleteNode(2);
    list.deleteNode(3);
    list.deleteNode(4);
    list.Print();
    list.RePrint();    
    list.append(1);
    list.Print();
    list.RePrint();  
    list.modify(1 , 2);
    list.Print();
    list.RePrint();        
    return 0;
}