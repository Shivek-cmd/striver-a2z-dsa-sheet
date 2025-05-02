#include <bits/stdc++.h>
using namespace std;

// Definition for doubly-linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int x) : data(x), prev(nullptr), next(nullptr) {}
};

// Problem: Implement functions to perform insertions and deletions in a doubly linked list.
// 1. Insert a node at the head, at the last position, and between nodes at a given position.
// 2. Delete a node from the head, from the last position, and from a given position.

// Function to insert a node at the head of the doubly linked list
Node* insertHead(Node* head, int val) {
    Node* newnode = new Node(val);
    if (head != nullptr) {
        newnode->next = head;
        head->prev = newnode;
    }
    return newnode;
}

// Function to insert a node at the end of the doubly linked list
Node* insertLast(Node* head, int val) {
    Node* newnode = new Node(val);
    if (head == nullptr) {
        return newnode;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
    return head;
}

// Function to insert a node at a given position (1-based index)
Node* insertBetween(Node* head, int val, int position) {
    if (position <= 0) {
        return head;
    }
    if (position == 1) {
        return insertHead(head, val);
    }
    Node* newnode = new Node(val);
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        delete newnode;
        return head;
    }
    newnode->next = temp->next;
    newnode->prev = temp;
    if (temp->next != nullptr) {
        temp->next->prev = newnode;
    }
    temp->next = newnode;
    return head;
}

// Function to delete the head node of the doubly linked list
Node* deleteHead(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
    return head;
}

// Function to delete the last node of the doubly linked list
Node* deleteLast(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->prev->next = nullptr;
    delete temp;
    return head;
}

// Function to delete a node at a given position (1-based index)
Node* deleteBetween(Node* head, int position) {
    if (head == nullptr || position <= 0) {
        return head;
    }
    if (position == 1) {
        return deleteHead(head);
    }
    Node* temp = head;
    for (int i = 1; i < position && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        return head;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    delete temp;
    return head;
}

// Function to print the doubly linked list (forward traversal)
void printLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << "<->";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Sample array to initialize the doubly linked list
    vector<int> arr = {12, 8, 5, 7};
    
    // Creating a doubly linked list with initial elements from the array
    Node* head = new Node(arr[0]);
    Node* node1 = head;
    Node* node2 = new Node(arr[1]);
    Node* node3 = new Node(arr[2]);
    Node* node4 = new Node(arr[3]);
    
    // Linking nodes
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;

    cout << "Original List: ";
    printLL(head);

    // Insert at head
    head = insertHead(head, 100);
    cout << "After inserting 100 at head: ";
    printLL(head);

    // Insert at last
    head = insertLast(head, 200);
    cout << "After inserting 200 at last: ";
    printLL(head);

    // Insert between (at position 3)
    head = insertBetween(head, 300, 3);
    cout << "After inserting 300 at position 3: ";
    printLL(head);

    // Delete head
    head = deleteHead(head);
    cout << "After deleting head: ";
    printLL(head);

    // Delete last
    head = deleteLast(head);
    cout << "After deleting last: ";
    printLL(head);

    // Delete between (at position 2)
    head = deleteBetween(head, 2);
    cout << "After deleting at position 2: ";
    printLL(head);

    return 0;
}