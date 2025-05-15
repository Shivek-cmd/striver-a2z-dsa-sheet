#include <bits/stdc++.h>
using namespace std;

// Problem Statement:
/*
Clone Linked List with Random and Next Pointer
- Given a linked list where each node contains two pointers:
  - 'next': points to the next node in the list.
  - 'random': points to a random node in the list or null.
- Create a deep copy of the linked list and return the head of the copied list.
- The copied list should have new nodes with the same values, and the 'next' and 'random' pointers should point to corresponding nodes in the copied list.

Example 1:
Input:
1 -> 2 -> 3
|    |    |
3    1   null
(random pointers: 1->3, 2->1, 3->null)
Output: A deep copy with the same structure and values.

Example 2:
Input:
7 -> 14 -> 21
|     |     |
14   null   7
(random pointers: 7->14, 14->null, 21->7)
Output: A deep copy with the same structure and values.

Constraints:
- 0 <= Number of nodes <= 1000
- -10000 <= Node.val <= 10000
- Random pointer may be null or point to any node in the list.
*/

// Definition for the linked list node
struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int x) : val(x), next(NULL), random(NULL) {}
};

// Function to clone the linked list
Node* copyRandomList(Node* head) {
    // Logic to create a deep copy of the linked list
    return nullptr;
}

int main() {
    // Create sample linked list
    Node* head = new Node(7);
    head->next = new Node(14);
    head->next->next = new Node(21);
    
    // Set random pointers
    head->random = head->next;          // 7 -> 14
    head->next->random = nullptr;       // 14 -> null
    head->next->next->random = head;    // 21 -> 7
    
    // Clone the linked list
    Node* result = copyRandomList(head);
    
    // Print the result
    Node* curr = result;
    while (curr != NULL) {
        cout << "Node " << curr->val << ": ";
        cout << "Next = " << (curr->next ? curr->next->val : -1);
        cout << ", Random = " << (curr->random ? curr->random->val : -1);
        cout << endl;
        curr = curr->next;
    }
    
    // Clean up memory
    curr = result;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    
    // Clean up original list
    curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    
    return 0;
}