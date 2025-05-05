#include <bits/stdc++.h>
using namespace std;

// Section 1: Problem Statement
// Given a singly linked list and an integer N, delete the Nth node from the end of the linked list and return the head of the updated list.
// Examples:
//   1. Input: 5->1->2, N=2  Output: 5->2
//   2. Input: 1->2->3->4->5, N=3  Output: 1->2->4->5
// Constraints:
//   - 1 <= N <= length of linked list
//   - Linked list contains at least 1 node
//   - Node values are integers
// Edge Cases:
//   - Empty list (return nullptr)
//   - N equals length of list (remove head)
//   - N equals 1 (remove last node)
//   - Single node list

// Definition for singly-linked list
struct Node {
    int val;
    Node *next;
    Node(int x) : val(x), next(NULL) {}
};

// Section 2: Observations and Solution Approaches
/*
Observations:
1. **Problem Nature**: The task involves manipulating a singly linked list to remove a node based on its position from the end, requiring traversal and pointer manipulation.
2. **Key Patterns**:
   - To find the Nth node from the end, we need to relate positions from the end to positions from the start.
   - A brute force approach involves calculating the list length to convert the position from the end to a position from the front.
   - An optimal approach can use two pointers to avoid calculating the length, leveraging the distance between pointers.
3. **Intuitive Insight**:
   - For brute force, the length of the list minus N gives the position from the front (1-based indexing).
   - For optimal, maintaining a gap of N nodes between two pointers allows us to find the node to delete in one pass.
4. **Mental Roadmap**:
   - Brute Force: Compute list length, calculate position from front, traverse to that position, and delete the node.
   - Optimal: Use two pointers (slow and fast) with a gap of N nodes, move them together until fast reaches the end, then delete the node after slow.
   - Edge cases like empty lists, single nodes, or invalid N must be handled explicitly.
*/

// Section 2: Solution Approaches




// ==============================================================================
// // Approach 1: Brute Force
// ==============================================================================


/*
Logic:
- Compute the length of the linked list by traversing it.
- Calculate the position from the front as (length - N + 1) to target the Nth node from the end.
- Traverse to the (pos-1)th node, adjust pointers to skip the pos-th node, and delete it.
Steps:
1. If list is empty, return nullptr.
2. Compute length using a helper function.
3. Validate N (1 <= N <= length).
4. Compute pos = length - N + 1.
5. If pos == 1, delete head and return new head.
6. Traverse to (pos-1)th node, update next pointer to skip pos-th node, and delete it.
Time Complexity: O(L) to compute length + O(L) to traverse to pos = O(L), where L is the list length.
Space Complexity: O(1), as we only use a few pointers.
Limitations:
- Requires two passes through the list (one for length, one for deletion).
- Less efficient than a single-pass approach.
*/


// ==============================================================================
// Approach 2: Optimal (Two-Pointer Technique)
// ==============================================================================


/*
Logic:
    - Use two pointers (slow and fast) to find the Nth node from the end in one pass.
    - Move fast pointer N steps ahead to create a gap.
    - Move both pointers until fast reaches the end; slow will be at the node before the one to delete.
    - Adjust pointers to delete the target node.

Mathematical Verification:
    Let's confirm the positions mathematically:
        List Length: L nodes, positions 1 to L (1-based indexing).
        Node to Delete: Nth from the end is the (L - N + 1)th node.
        Goal: Position slow at the (L - N)th node so slow->next is the (L - N + 1)th node.
        Steps:
            - fast moves N steps to position N + 1.
            - If N = L, fast = nullptr, and we return head->next (correct for deleting the head).
            - Otherwise, move both L - N - 1 steps:
                - fast: N + 1 + (L - N - 1) = L (last node).
                - slow: 1 + (L - N - 1) = L - N.
            - slow is at L - N, and slow->next is at L - N + 1, the node to delete.
        The gap of N steps ensures:
            Position of fast - Position of slow = N
            When fast is at L:
                L - Position of slow = N
                Position of slow = L - N
            This positions slow correctly before the node to delete.

Steps:
    1. If list is empty, return nullptr.
    2. Create a dummy node pointing to head to handle edge cases (e.g., deleting head).
    3. Initialize slow and fast pointers at dummy.
    4. Move fast N+1 steps to create a gap of N nodes.
    5. Move slow and fast together until fast reaches the end.
    6. Delete the node after slow by adjusting pointers.
    7. Return dummy->next as the new head.

Time Complexity: O(L), where L is the list length (single pass).
Space Complexity: O(1), as we only use a few pointers.
Why Optimal:
    - Eliminates the need for a second pass to compute length.
    - Handles all edge cases (e.g., deleting head) cleanly with a dummy node.
Trade-offs:
    - Slightly more complex to implement due to dummy node and pointer management.
    - Requires careful handling of edge cases like N == length.
*/

// Section 3: Code Implementation

// Helper function to compute list length
int findLength(Node* temp) {
    int cnt = 0;
    while (temp) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

// Helper function to delete node at given position (1-based index)
Node* deleteNthNode(Node* temp, int pos) {
    if (!temp) return nullptr; // Empty list
    if (pos == 1) { // Delete head
        Node* newHead = temp->next;
        delete temp;
        return newHead;
    }
    Node* curr = temp;
    for (int i = 1; i < pos - 1; i++) {
        if (!curr) return temp; // Invalid position
        curr = curr->next;
    }
    if (curr && curr->next) { // Delete node at pos
        Node* toDelete = curr->next;
        curr->next = curr->next->next;
        delete toDelete;
    }
    return temp;
}

// Brute Force: Compute length and delete node at (length - N + 1)
Node* removeNthFromEndBrute(Node* head, int n) {
    if (!head) return nullptr; // Handle empty list
    Node* fast = head;
    Node* slow = head;

    // Move fast N steps ahead
    for (int i = 0; i < n; i++) {
        if (!fast) return head; // Handle invalid N
        fast = fast->next;
    }

    // Special case: N equals list length, delete head
    if (fast == nullptr) {
        Node* newHead = head->next;
        delete head;
        return newHead;
    }

    // Move both until fast reaches nullptr
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    // slow is at (L-N)th node, slow->next is (L-N+1)th node
    Node* delNode = slow->next;
    slow->next = slow->next->next;
    delete delNode;
    return head;
}
