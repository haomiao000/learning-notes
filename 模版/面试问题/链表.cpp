#include<bits/stdc++.h>
using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) : val(val) , next(nullptr) {}
};

class LinkList {
public:
    ListNode *head;
    LinkList() : head(nullptr) {}
    void Insert(int val) {
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
    void Remove(int val) {
        while(this->head != nullptr && this->head->val == val) {
            ListNode *d = this->head;
            this->head = this->head->next;
            delete d;
            d = nullptr;
        }
        ListNode *tmp = this->head;
        while(tmp != nullptr && tmp->next != nullptr) {
            if(tmp->next->val == val) {
                ListNode *d = tmp->next;
                tmp->next = tmp->next->next;
                delete d;
                d = nullptr;
            }else {
                tmp = tmp->next;
            }
        }
    }
    void Modify(int x , int d) {
        if(this->head == nullptr) {
            cout << "head is empty" << endl;
        }else {
            ListNode *tmp = this->head;
            while(tmp != nullptr) {
                if(tmp->val == x) {
                    tmp->val = d;
                }
                tmp = tmp->next;
            }
        }
    }
    void Print() {
        if(this->head == nullptr) {
            cout << "head is empty" << endl;
        }else {
            ListNode *tmp = this->head;
            while(tmp != nullptr) {
                cout << tmp->val << " ";
                tmp=tmp->next;
            }
            cout<<endl;
        }
    }
    ~LinkList() {
        ListNode *tmp = head;
        while(tmp != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
            tmp = nullptr;
        }
    }
};
signed main() {
    LinkList list;
    list.Print();
    list.Insert(3);
    list.Insert(2);
    list.Insert(4);
    list.Print();
    list.Insert(1);
    list.Insert(1);
    list.Print();
    list.Insert(3);
    list.Insert(2);
    list.Modify(2 , 1);
    list.Insert(4);    
    list.Print();
    list.Remove(3);
    list.Print();
    list.Remove(1);
    list.Remove(4);
    list.Print();
    list.Remove(2);
    list.Print();
    return 0;
}