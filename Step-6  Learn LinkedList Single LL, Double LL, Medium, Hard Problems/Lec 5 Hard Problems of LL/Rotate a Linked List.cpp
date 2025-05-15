#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(NULL) {}
};

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
/*
Problem: Rotate a singly-linked list to the right by k places.
- Given the head of a linked list, rotate the list to the right by k places, where k is non-negative.
- Each rotation moves the last node to the front, and the second-to-last node becomes the new tail.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Explanation: Rotate right by 1: [5,1,2,3,4], then by 1 again: [4,5,1,2,3]

Example 2:
Input: head = [0,1,2], k = 4
Output: [2,0,1]
Explanation: Effective rotation is k % length = 4 % 3 = 1, so rotate right by 1: [2,0,1]

Constraints:
- The number of nodes in the list is in the range [0, 500].
- -100 <= Node.val <= 100
- 0 <= k <= 10^9

Edge Cases:
- Empty list (head = nullptr)
- Single node (head->next = nullptr)
- k = 0 (no rotation)
- k >= length of list (effective rotation = k % length)
- k is very large (e.g., 10^9)
*/

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================
/*
Observations and Analytical Thought Process:
1. **Core Insight**: Rotating the list to the right by k places is equivalent to moving the last k nodes to the front, while the remaining nodes shift to the end. This can be visualized as splitting the list at the (length - k)-th node and reconnecting the second part to the start.
2. **Key Pattern**: The effective rotation is k % length, as rotating by the list length returns the original list. This reduces large k values to manageable ones.
3. **Intuitive Approach**: A single rotation to the right involves moving the last node to the front and adjusting the tail. Repeating this k times is intuitive but slow for large k.
4. **Optimization Insight**: Instead of k single rotations, we can compute the split point directly, split the list, and reconnect in one pass, leveraging the list's linear structure.
5. **Edge Cases to Handle**:
   - Empty or single-node lists require no rotation.
   - k = 0 or k = length means no change.
   - Large k requires modulo to avoid unnecessary work.
6. **Mental Roadmap**:
   - Compute list length to handle k % length.
   - Identify the new tail (length - k - 1) and new head (length - k).
   - Adjust pointers to split and reconnect the list.
   - Use pointers to avoid extra memory allocation.

Approach 1: Brute Force (Single Rotations)
a. Logic:
   - Perform k single rotations, where each rotation moves the last node to the front.
   - For each rotation, traverse to the second-to-last node, detach the last node, and attach it to the head.
b. Steps:
   1. Handle edge cases (empty, single node, k = 0).
   2. Compute list length and reduce k = k % length.
   3. For each of k iterations:
      - Traverse to the last node and second-to-last node.
      - Set last->next = head, second-to-last->next = nullptr, head = last.
   4. Return new head.
c. Complexity:
   - Time: O(n * k), where n is list length, as each rotation traverses the list O(n) times, and we repeat k times.
   - Space: O(1), only using a few pointers.
d. Limitations:
   - Inefficient for large k, as it repeats traversals unnecessarily.
   - Redundant work when k is close to or larger than n.

Approach 2: Optimal (Single Split and Reconnect)
a. Logic:
   - Instead of k rotations, compute the split point directly and reconnect the list.
   - The new tail is at position (length - k - 1), and the new head is the next node.
   - Connect the last node to the original head to complete the rotation.
b. Steps:
   1. Handle edge cases (empty, single node, k = 0).
   2. Compute list length and find the last node in one pass.
   3. Reduce k = k % length.
   4. Traverse to the (length - k - 1)-th node (new tail).
   5. Split the list: set new tail->next = nullptr, new head = new tail->next.
   6. Connect last node to original head.
   7. Return new head.
c. Complexity:
   - Time: O(n), one pass for length (O(n)), one partial pass to split point (O(n - k)).
   - Space: O(1), only using pointers.
d. Advantages:
   - Efficient for any k, as it avoids repeated traversals.
   - Single pass to find split point reduces redundant work.
e. Trade-offs:
   - Slightly more complex pointer manipulation than brute force.
   - Requires careful handling to avoid null pointer issues.
*/

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Helper function for Brute Force: Rotate list by 1 place to the right
Node* rotateOne(Node* head) {
    // Handle empty or single-node list
    if (!head || !head->next) {
        return head;
    }
    
    // Find last and second-to-last nodes
    Node* curr = head;
    Node* prev = nullptr;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    
    // Perform rotation:
    // - Last node points to head
    // - Second-to-last node becomes tail
    // - Last node becomes new head
    curr->next = head;
    prev->next = nullptr;
    head = curr;
    
    return head;
}

// Brute Force Approach: Perform k single rotations
Node* rotateRightBruteForce(Node* head, int k) {
    // Handle edge cases
    if (!head || !head->next || k == 0) {
        return head;
    }
    
    // Compute list length
    int length = 0;
    Node* temp = head;
    while (temp) {
        length++;
        temp = temp->next;
    }
    
    // Reduce k to effective rotation
    k = k % length;
    if (k == 0) {
        return head;
    }
    
    // Perform k single rotations
    while (k > 0) {
        head = rotateOne(head);
        k--;
    }
    
    return head;
}

// Optimal Approach: Split and reconnect list
Node* rotateRightOptimal(Node* head, int k) {
    // Handle edge cases
    if (!head || !head->next || k == 0) {
        return head;
    }
    
    // Compute list length and find last node
    int length = 0;
    Node* curr = head;
    Node* lastNode = nullptr;
    while (curr) {
        length++;
        lastNode = curr;
        curr = curr->next;
    }
    
    // Reduce k to effective rotation
    k = k % length;
    if (k == 0) {
        return head;
    }
    
    // Find new tail at position (length - k - 1)
    int splitPos = length - k - 1;
    curr = head;
    for (int i = 0; i < splitPos; i++) {
        curr = curr->next;
    }
    
    // Split and reconnect:
    // - New head is node after curr
    // - New tail (curr) points to nullptr
    // - Last node points to original head
    Node* newHead = curr->next;
    curr->next = nullptr;
    lastNode->next = head;
    head = newHead;
    
    return head;
}

int main() {
    // Create sample linked list: 1->2->3->4->5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    int k = 2;
    
    // Rotate the list using optimal approach
    Node* result = rotateRightOptimal(head, k);
    
    // Print the result
    Node* curr = result;
    while (curr != NULL) {
        cout << curr->val;
        if (curr->next != NULL) cout << " ";
        curr = curr->next;
    }
    cout << endl;
    
    // Clean up memory
    curr = result;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    
    return 0;
}