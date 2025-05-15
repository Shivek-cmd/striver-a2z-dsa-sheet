#include <bits/stdc++.h>
using namespace std;

// Problem Statement: Given the head of a singly linked list of n nodes and an integer k,
// where k is less than or equal to n. Your task is to reverse the order of each group of k
// consecutive nodes, if n is not divisible by k, then the last group of remaining nodes
// should remain unchanged.

// Definition for singly-linked list.
struct Node {
    int val;
    Node *next;
    Node(int x) : val(x), next(NULL) {}
};

// Helper function to get the kth node from the current node
Node* getKthNode(Node* head, int k) {
    Node* temp = head;
    k -= 1;
    while (temp && k > 0) {
        temp = temp->next;
        k--;
    }
    return temp;
}

// Helper function to reverse a linked list segment
void reverseLinkedList(Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

Node* reverseKGroup(Node* head, int k) {
    if (head == nullptr || k == 1) {
        return head;
    }

    Node* prevLast = nullptr;
    Node* curr = head;
    Node* newHead = head;

    while (curr) {
        // Get the kth node of the current group
        Node* kthNode = getKthNode(curr, k);
        
        // If kthNode is null, less than k nodes remain, so connect and break
        if (!kthNode) {
            if (prevLast) {
                prevLast->next = curr;
            }
            break;
        }

        // Store the next node after the kth node
        Node* nextNode = kthNode->next;
        
        // Disconnect the kth node to reverse the current group
        kthNode->next = nullptr;
        
        // Reverse the current group
        reverseLinkedList(curr);
        
        // After reversal, curr is the last node of the reversed group
        // and kthNode is the first node of the reversed group
        if (curr == head) {
            // If this is the first group, update the head
            newHead = kthNode;
        } else {
            // Connect the previous group's last node to the current group's head
            prevLast->next = kthNode;
        }
        
        // Update prevLast to the last node of the current reversed group
        prevLast = curr;
        
        // Move to the next group
        curr = nextNode;
    }
    
    return newHead;
}

int main() {
    // Sample linked list: 1->2->3->4->5->6->7->8->9->10
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    head->next->next->next->next->next->next = new Node(7);
    head->next->next->next->next->next->next->next = new Node(8);
    head->next->next->next->next->next->next->next->next = new Node(9);
    head->next->next->next->next->next->next->next->next->next = new Node(10);
    
    int k = 3;
    
    // Call the function
    Node* result = reverseKGroup(head, k);
    
    // Print the result
    Node* curr = result;
    while (curr != NULL) {
        cout << curr->val;
        if (curr->next != NULL) cout << " ";
        curr = curr->next;
    }
    cout << endl;
    
    return 0;
}