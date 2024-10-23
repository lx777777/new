#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class LinkedList {
public:
    struct Node {
        Node(int x = 0) : val(x), next(nullptr) {}
        int val;
        Node* next;
    };
    // 构造函数
    LinkedList();
    // 析构函数
    ~LinkedList();
    // 链表的尾部插入
    void insertTail(const initializer_list<int>& values);
    // 在链表的任意位置插入节点
    void insert(int pos, int val);
    // 在链表的头部插入
    void insertHead(int val);
    // 打印链表的各个元素
    void show();
private:
    void insertTail(int val) {
        Node* curNode = head;
        while(curNode->next != nullptr) {
            curNode = curNode->next;
        }
        // 此时curNode指向链表的最后一个节点，创建一个新的节点，插入到curNode的后面
        Node* newNode = new Node(val);
        curNode->next = newNode;
        size_++;
    }
private:
    Node* head; // 定义头节点
    int size_;  // 记录链表中元素的个数

    friend void reverseLinkedList(LinkedList& list);
    friend void mergeLinkedList(LinkedList& list1, LinkedList& list2);
    friend void removeRk(LinkedList& list, int index);
    friend void sortLinkedList(LinkedList& list);
};

LinkedList::LinkedList() 
    : head(new Node()), size_(0)
{}

LinkedList::~LinkedList() {
    Node* curNode = head;
    while(curNode != nullptr) {
        head = head->next;
        delete curNode;
        curNode = head;
    }
}

void LinkedList::insertTail(const initializer_list<int>& values) {
    for(const int num : values) {
        insertTail(num);
    }
}

void LinkedList::insert(int pos, int val) {
    if(pos < 0 || pos > size_) {
        cout << "insert pos error." << endl;
        return;
    }
    Node* curNode = head;
    while(pos--) {
        curNode = curNode->next;
    }
    Node* newNode = new Node(val);
    newNode->next = curNode->next;
    curNode->next = newNode;
    size_++;
}

void LinkedList::insertHead(int val) {
    Node* newNode = new Node(val);
    newNode->next = head->next;
    head->next = newNode;
    size_++;
}

void LinkedList::show() {
    Node* curNode = head->next;
    while(curNode !=  nullptr) {
        cout << curNode->val << " ";
        curNode = curNode->next;
    }
    cout << endl;
}

// 反转链表 头插法
void reverseLinkedList(LinkedList& list) {
    LinkedList::Node* curNode = list.head->next;
    list.head->next = nullptr;
    while(curNode != nullptr) {
        LinkedList::Node* nextNode = curNode->next;
        curNode->next = list.head->next;
        list.head->next = curNode;
        curNode = nextNode;
    }
}

// 合并两个有序链表，合并后的链表保存在list1中
void mergeLinkedList(LinkedList& list1, LinkedList& list2) {
    LinkedList::Node* last = list1.head;
    LinkedList::Node* p = list1.head->next;
    LinkedList::Node* q = list2.head->next;
    while(p != nullptr && q != nullptr) {
        if(p->val >= q->val) {
            last->next = q;
            q = q->next;
            last = last->next;
        } else if(p->val < q->val) {
            last->next = p;
            p = p->next;
            last = last->next;
        }
    }
    // 如果list1的长度小于list2的长度
    if(p == nullptr) {
        last->next = q;
    }
    // 如果list2的长度小于list1的长度
    if(q == nullptr) {
        last->next = p;
    }
    list2.head = nullptr;
}

// 删除链表的倒数第k个节点
void removeRk(LinkedList& list, int index) {
    LinkedList::Node* p = list.head;
    LinkedList::Node* q = list.head;
    while(index--) {
        q = q->next;
    }
    while(q->next != nullptr) {
        p = p->next;
        q = q->next;
    }
    p->next = p->next->next;
}

// 排序链表
void sortLinkedList(LinkedList& list) {
    vector<int> vec;
    LinkedList::Node* curNode = list.head->next;
    while(curNode != nullptr) {
        vec.push_back(curNode->val);
        curNode = curNode->next;
    }
    list.head->next = nullptr;
    sort(vec.begin(), vec.end());
    for(const int num : vec) {
        list.insertTail(num);
    }
}
int main() {
    LinkedList list1, list2;
    list1.insertTail({1, 3, 5, 7, 9});
    list2.insertTail({2, 4, 6, 8, 9, 10});
    mergeLinkedList(list1, list2);
    list1.show();
    removeRk(list1, 3);
    list1.show();
    reverseLinkedList(list1);
    list1.show();
    sortLinkedList(list1);
    list1.show();

    delete list1;
}
