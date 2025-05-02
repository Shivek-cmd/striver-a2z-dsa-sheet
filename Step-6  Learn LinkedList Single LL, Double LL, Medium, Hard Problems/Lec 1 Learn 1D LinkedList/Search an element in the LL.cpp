#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

// Problem: Implement a function to search for an element in a singly linked list and return its 1-based position (or -1 if not found).

// Function to search for an element in the linked list
int searchLL(Node* head, int val) {
    Node* temp = head;
    int position = 1;
    while (temp != nullptr) {
        if (temp->data == val) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

// Function to print the linked list
void printLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << "->";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Sample array to initialize the linked list
    vector<int> arr = {12, 8, 5, 7};
    
    // Creating a linked list with initial elements from the array
    Node* head = new Node(arr[0]);
    head->next = new Node(arr[1]);
    head->next->next = new Node(arr[2]);
    head->next->next->next = new Node(arr[3]);

    cout << "Linked List: ";
    printLL(head);
    
    // Search for elements
    int val1 = 5;  // Should be found at position 3
    int val2 = 10; // Should not be found
    cout << "Position of " << val1 << ": " << searchLL(head, val1) << endl;
    cout << "Position of " << val2 << ": " << searchLL(head, val2) << endl;

    return 0;
}