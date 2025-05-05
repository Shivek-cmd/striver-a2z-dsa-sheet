#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
// Problem: Segregate even and odd nodes in a singly linked list such that all even-valued nodes appear before all odd-valued nodes.
// The relative order of even and odd nodes should be preserved.
// Input: Head of a singly linked list (Node* head).
// Output: Head of the modified linked list with even nodes followed by odd nodes.
// Examples:
//   1. Input: 1->2->3->4->5->6->Null  Output: 2->4->6->1->3->5->Null
//   2. Input: 1->3->5->Null  Output: 1->3->5->Null
//   3. Input: 2->4->6->8->Null  Output: 2->4->6->8->Null
// Constraints:
//   - Number of nodes: 0 <= n <= 10^5
//   - Node values: -10^4 <= val <= 10^4
// Edge Cases:
//   - Empty list (return nullptr)
//   - Single node (return as is)
//   - All even or all odd nodes (return as is)

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================



// ==============================================================================
// Approach 1: Brute Force (Using Two Lists)
// ==============================================================================

// Logic:
//   - Traverse the list and separate even and odd nodes into two separate lists.
//   - Maintain two dummy nodes for even and odd lists to simplify linking.
//   - Append each node to the appropriate list based on its value (even or odd).
//   - Finally, connect the even list's tail to the odd list's head.
// Thought Process:
//   - Segregating nodes into two groups preserves their relative order naturally.
//   - Dummy nodes avoid edge cases when lists are empty.
//   - Reconnecting lists at the end ensures the final structure is correct.
// Steps:
//   1. Initialize two dummy nodes for even and odd lists.
//   2. Traverse the input list, detaching each node.
//   3. Append node to even list if value is even, else to odd list.
//   4. Connect even list's tail to odd list's head.
//   5. Return the head of the combined list.
// Time Complexity: O(n) for single traversal of the list
// Space Complexity: O(1) excluding dummy nodes (constant extra pointers)
// Limitations:
//   - Requires careful pointer manipulation to avoid losing nodes.
//   - Involves creating temporary dummy nodes, though minimal.



// ==============================================================================
// Approach 2: Optimal (In-Place Segregation)
// ==============================================================================


// Logic:
//   - Similar to brute force but avoids creating new lists by rearranging nodes in-place.
//   - Use two pointers to track the last node of even and odd segments.
//   - Move nodes to their respective segments while preserving order.
//   - Ensure the even segment connects to the odd segment at the end.
// Thought Process:
//   - In-place rearrangement reduces space usage to constant.
//   - Tracking segment tails allows efficient node insertion.
//   - Preserving order requires careful linking during traversal.
// Steps:
//   1. Initialize pointers for even and odd segments.
//   2. Traverse the list, classifying nodes as even or odd.
//   3. Link even nodes together and odd nodes together separately.
//   4. Connect the even segment’s tail to the odd segment’s head.
//   5. Handle edge cases (empty or single node).
// Time Complexity: O(n) for single traversal
// Space Complexity: O(1) as only pointers are used
// Why Optimal:
//   - Minimizes space by avoiding extra list structures.
//   - Maintains same time complexity as brute force but with cleaner memory usage.
// Trade-offs:
//   - Slightly more complex pointer manipulation.
//   - Requires careful handling to maintain list integrity.

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Definition for singly-linked list
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

// Brute Force: Using Two Lists
Node* segregateEvenOddBrute(Node* head) {
    // Handle edge cases: empty or single node
    if (!head || !head->next) {
        return head;
    }
    
      // creating Heads of Odd and Even LinkedLists
      Node *oddHead = new Node(-1), *oddTail = oddHead;
      Node *evenHead = new Node(-1), *evenTail = evenHead;
      Node *curr = head, *temp;
      while (curr)
      {
          // Breaking the Link of the curr Node.
          temp = curr;
          curr = curr->next;
          temp->next = nullptr;
  
          if (temp->val & 1) // If odd Node,append to odd LinkedList
          {
              oddTail->next = temp;
              oddTail = temp;
          }
          else // If Even Node,append to even LinkedList
          {
              evenTail->next = temp;
              evenTail = temp;
          }
      }
      evenTail->next = oddHead->next; 
      // Appending Odd LinkedList at end of EvenLinkedList
      return evenHead->next;
}


// Optimal: In-Place Segregation
Node* segregateEvenOddOptimal(Node* head) {
    // Handle edge cases: empty or single node
    if (!head || !head->next) {
        return head;
    }
    
    // Initialize pointers for even and odd segments
    Node* evenHead = nullptr;
    Node* evenTail = nullptr;
    Node* oddHead = nullptr;
    Node* oddTail = nullptr;
    Node* curr = head;
    
    // Traverse and segregate nodes
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        temp->next = nullptr; // Detach node
        
        // Append to even segment
        if (temp->val % 2 == 0) {
            if (!evenHead) {
                evenHead = temp;
                evenTail = temp;
            } else {
                evenTail->next = temp;
                evenTail = temp;
            }
        }
        // Append to odd segment
        else {
            if (!oddHead) {
                oddHead = temp;
                oddTail = temp;
            } else {
                oddTail->next = temp;
                oddTail = temp;
            }
        }
    }
    
    // Connect even segment to odd segment
    if (evenTail) {
        evenTail->next = oddHead;
        return evenHead;
    }
    
    // If no even nodes, return odd list
    return oddHead;
}

int main() {
    // Create sample linked list: 1->2->3->4->5->6
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    
    // Test Brute Force
    cout << "Brute Force: ";
    Node* resultBrute = segregateEvenOddBrute(head);
    Node* temp = resultBrute;
    while (temp) {
        cout << temp->val;
        if (temp->next) cout << "->";
        temp = temp->next;
    }
    cout << "->Null" << endl;
    
    // Clean up brute force result
    while (resultBrute) {
        Node* temp = resultBrute;
        resultBrute = resultBrute->next;
        delete temp;
    }
    
    // Recreate list for Optimal test
    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    
    // Test Optimal
    cout << "Optimal: ";
    Node* resultOptimal = segregateEvenOddOptimal(head);
    temp = resultOptimal;
    while (temp) {
        cout << temp->val;
        if (temp->next) cout << "->";
        temp = temp->next;
    }
    cout << "->Null" << endl;
    
    // Clean up optimal result
    while (resultOptimal) {
        Node* temp = resultOptimal;
        resultOptimal = resultOptimal->next;
        delete temp;
    }
    
    return 0;
}
