#include <iostream>

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode *prev;
    
    ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    ListNode *head;

public:
    CircularDoublyLinkedList() : head(nullptr) {}

    // 插入节点到链表末尾
    void insert(int val) {
        ListNode *newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            ListNode *tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    // 删除节点
    void remove(int val) {
        if (head == nullptr) return;

        ListNode *current = head;
        do {
            if (current->val == val) {
                if (current == head && current->next == head) { // 链表中只有一个节点
                    delete current;
                    head = nullptr;
                    return;
                } else {
                    ListNode *prevNode = current->prev;
                    ListNode *nextNode = current->next;

                    prevNode->next = nextNode;
                    nextNode->prev = prevNode;

                    if (current == head) {
                        head = nextNode;
                    }

                    delete current;
                    return;
                }
            }
            current = current->next;
        } while (current != head);
    }

    // 打印链表
    void print() {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        ListNode *current = head;
        do {
            std::cout << current->val << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }
};

int main() {
    CircularDoublyLinkedList list;
    
    // 插入元素
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    std::cout << "Original list: ";
    list.print();

    // 删除元素
    list.remove(2);
    std::cout << "After removing 2: ";
    list.print();

    list.remove(1);
    std::cout << "After removing 1: ";
    list.print();

    return 0;
}