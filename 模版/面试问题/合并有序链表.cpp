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
    LinkList(ListNode *node) : head(node) {}
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
        while(head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};
ListNode *Merge(LinkList &list1, LinkList &list2) {
    ListNode *tmp1 = list1.head;
    ListNode *tmp2 = list2.head;
    ListNode *head = nullptr;
    ListNode *tmp3 = nullptr;
    
    while (tmp1 != nullptr || tmp2 != nullptr) {
        ListNode *newNode = nullptr;
        
        if (tmp1 == nullptr) {
            newNode = new ListNode(tmp2->val);
            tmp2 = tmp2->next;
        } else if (tmp2 == nullptr) {
            newNode = new ListNode(tmp1->val); 
            tmp1 = tmp1->next;
        } else {
            if (tmp1->val <= tmp2->val) {
                newNode = new ListNode(tmp1->val);
                tmp1 = tmp1->next;
            } else {
                newNode = new ListNode(tmp2->val); 
                tmp2 = tmp2->next;
            }
        }
        if (tmp3 == nullptr) {
            head = newNode;
            tmp3 = newNode;
        } else {
            tmp3->next = newNode;
            tmp3 = tmp3->next;
        }
    }
    return head;
}
signed main() {
    LinkList list1;
    LinkList list2;
    list1.Insert(1);
    list1.Insert(3);
    list1.Insert(4);
    list1.Insert(7);
    list2.Insert(2);
    list2.Insert(3);
    list2.Insert(5);
    list2.Insert(6);
    list2.Insert(8);
    // list2.Print();
    
    LinkList list3(Merge(list1 , list2));
    list3.Print();
    return 0;
}