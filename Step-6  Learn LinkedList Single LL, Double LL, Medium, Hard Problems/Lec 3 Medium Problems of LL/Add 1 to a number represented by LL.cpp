#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
// Problem: Given a number represented as a linked list where each node contains a single digit,
// add 1 to the number and return the resulting linked list. The digits are stored such that the
// most significant digit is at the head of the list.
//
// Example 1:
// Input: 1 -> 2 -> 3 (represents 123)
// Output: 1 -> 2 -> 4 (represents 124)
//
// Example 2:
// Input: 9 -> 9
// Output: 1 -> 0 -> 0
//
// Constraints:
// - The linked list contains at least one node.
// - Each node's value is a digit between 0 and 9.
// - The number does not have leading zeros, except for the number 0 itself.
//
// Edge Cases:
// - Single digit (e.g., 9 -> 1 -> 0)
// - All 9s (e.g., 9 -> 9 -> 1 -> 0 -> 0)
// - Typical case (e.g., 1 -> 2 -> 3 -> 1 -> 2 -> 4)

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

/*


// ==============================================================================
Approach 1: Iterative with Reverse
// ==============================================================================


- Logic: Reverse the list to process digits from least to most significant, add 1, and reverse back.
- Thought Process:
  - Adding 1 to a number is easiest from the least significant digit due to carry propagation.
  - Reversing the list allows processing digits in reverse order without recursion.
  - After adding 1 and handling carries, reverse the list back to maintain original order.
  - Key pattern: Carry propagation stops when a digit < 9 is encountered or a new node is added.
- Steps:
  1. Reverse the linked list.
  2. Add 1 to the first node (least significant digit) and propagate carry.
  3. If carry remains, append a new node with value 1.
  4. Reverse the list back.
  5. Return the result.
- Time Complexity: O(3N) = O(N)
  - Reverse list: O(N)
  - Process digits: O(N)
  - Reverse back: O(N)
  - N is the number of nodes.
- Space Complexity: O(1)
  - Only uses a constant amount of extra space (pointers and carry variable).
- Limitations:
  - Requires two list reversals, which may be unnecessary if we can process digits directly.
  - Not intuitive for cases where carry propagation is minimal.


  
// ==============================================================================
Approach 2: Recursive
// ==============================================================================

- Logic: Use recursion to process digits from the least significant to the most significant.
- Thought Process:
  - Recursion naturally processes the list from the end (least significant digit) to the start.
  - A helper function can return the carry to propagate backwards.
  - Key pattern: Each node adds the carry; if the result is 10, set digit to 0 and propagate carry.
  - If a carry remains after processing, add a new node with value 1 at the head.
- Steps:
  1. Recursively traverse to the last node.
  2. Add carry (initially 1) to each node's value, propagating carry if value becomes 10.
  3. If carry remains after recursion, add a new node with value 1 at the head.
  4. Return the result.
- Time Complexity: O(N)
  - Single pass through the list via recursion.
- Space Complexity: O(N)
  - Recursive call stack uses O(N) space.
- Limitations:
  - Recursive stack space may be a concern for very large lists.
  - Slightly less intuitive than iterative for some developers.

Optimal Approach: Recursive (Approach 2)
- Why Optimal:
  - Single pass through the list (O(N) time) versus three passes in Approach 1 (O(3N)).
  - No need for reversing the list, reducing unnecessary operations.
  - Clean and concise code, leveraging recursion to handle carry propagation naturally.
  - Trade-off of O(N) space is acceptable for most practical list sizes, as linked lists are
    typically not extremely long.
*/

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Helper function for Approach 1: Reverse the linked list
Node* reverse(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node* newHead = reverse(head->next); // Recurse to end
    Node* front = head->next;           // Next node links back
    front->next = head;
    head->next = nullptr;
    return newHead;
}

// Approach 1: Iterative with Reverse
Node* plusOneIterative(Node* head) {
    if (!head) return new Node(1); // Edge case: empty list

    // Reverse list to process least significant digit first
    Node* reversed = reverse(head);
    Node* temp = reversed;
    int carry = 1; // Initial carry to add 1

    // Process each digit
    while (temp) {
        temp->val += carry;      // Add carry
        if (temp->val < 10) {    // If no carry, stop
            carry = 0;
            break;
        }
        temp->val = 0;           // Set digit to 0 if 10
        carry = 1;               // Propagate carry
        temp = temp->next;
    }

    // If carry remains, append new node
    if (carry) {
        Node* newNode = new Node(1);
        reversed = reverse(reversed); // Reverse back
        newNode->next = reversed;
        return newNode;
    }

    // Reverse back and return
    return reverse(reversed);
}

// Helper function for Approach 2: Recursive carry propagation
int helper(Node* head) {
    if (!head) return 1; // Base case: return carry of 1

    int carry = helper(head->next); // Recurse to next node
    head->val += carry;             // Add carry to current digit

    if (head->val < 10) {           // If no carry, return 0
        return 0;
    }
    head->val = 0;                  // Set digit to 0 if 10
    return 1;                       // Propagate carry
}

// Approach 2: Recursive (Optimal)
Node* plusOneRecursion(Node* head) {
    if (!head) return new Node(1); // Edge case: empty list

    int carry = helper(head);      // Process list recursively

    if (carry) {                   // If carry remains, add new node
        Node* newNode = new Node(1);
        newNode->next = head;
        return newNode;
    }
    return head;                   // Return modified list
}

int main() {
    // Sample input: 9 -> 9
    Node* head = new Node(9);
    head->next = new Node(9);

    // Test recursive approach (optimal)
    Node* result = plusOneRecursion(head);

    // Print result
    while (result) {
        cout << result->val;
        if (result->next) cout << " -> ";
        result = result->next;
    }
    cout << endl;

    return 0;
}