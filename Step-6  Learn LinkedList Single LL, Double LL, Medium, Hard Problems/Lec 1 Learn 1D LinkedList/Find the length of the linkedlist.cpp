#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

// Problem: Implement a function to find the length of a singly linked list.

// Function to find the length of the linked list
int lengthLL(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
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
    
    // Find and print the length of the linked list
    cout << "Length of Linked List: " << lengthLL(head) << endl;

    return 0;
}