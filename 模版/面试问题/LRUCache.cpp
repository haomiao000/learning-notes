#include<bits/stdc++.h>
using namespace std;

struct Node {
    int k, val;
    Node* prev;
    Node* next;
    Node(): k(0), val(0), prev(nullptr), next(nullptr) {}
    Node(int _k, int _val): k(_k), val(_val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, Node*> map;
    Node* dummyHead;
    Node* dummyTail;
    int currSize;
    int maxCapacity;

public:
    LRUCache(int capacity): maxCapacity(capacity), currSize(0) {
        dummyHead = new Node();
        dummyTail = new Node();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    
    int get(int key) {
        if (!map.count(key)) {
            return -1;
        }
        Node* node = map[key];
        bringToHead(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (!map.count(key)) {
            Node* newNode = new Node(key, value);
            map[key] = newNode;
            insertToHead(newNode);
            currSize++;
            if (currSize > maxCapacity) {
                Node* oldNode = removeFromTail();
                map.erase(oldNode->k);
                delete oldNode;
                currSize--;
            }
        } else {
            Node* existingNode = map[key];
            existingNode->val = value;
            bringToHead(existingNode);
        }
    }

    void insertToHead(Node* node) {
        node->prev = dummyHead;
        node->next = dummyHead->next;
        dummyHead->next->prev = node;
        dummyHead->next = node;
    }
    
    void detachNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void bringToHead(Node* node) {
        detachNode(node);
        insertToHead(node);
    }

    Node* removeFromTail() {
        Node* node = dummyTail->prev;
        detachNode(node);
        return node;
    }
};