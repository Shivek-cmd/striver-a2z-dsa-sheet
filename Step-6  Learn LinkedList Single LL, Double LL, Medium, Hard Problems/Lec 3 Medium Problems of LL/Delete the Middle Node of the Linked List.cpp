#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list
struct Node {
    int val;
    Node *next;
    Node(int x) : val(x), next(nullptr) {}
};

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
// Problem: Given the head of a singly linked list of integers, delete the middle node
// and return the modified head. For even-length lists, delete the second middle node.
//
// Examples:
//   Input: 1 -> 2 -> 3 -> 4 -> 5
//   Output: 1 -> 2 -> 4 -> 5
//   Explanation: Middle node (3) is deleted.
//   Input: 1 -> 2 -> 3 -> 4
//   Output: 1 -> 2 -> 4
//   Explanation: Second middle node (3) is deleted.
//
// Constraints:
//   - Number of nodes: [1, 10^5]
//   - Node values: [-10^4, 10^4]
//   - Linked list is singly linked and non-circular.
//
// Edge Cases:
//   - Single node (delete the only node, return nullptr).
//   - Two nodes (delete second node).
//   - Empty list (return nullptr).
//   - Even vs. odd number of nodes (handle second middle node for even case).

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================

// Observations and Thought Process:
// 1. **Key Pattern**: The middle node for odd-length lists is at index floor(n/2),
//    while for even-length lists, the second middle node is at index n/2 (0-based).
// 2. **Intuitive Insight**: To delete a node, we need the pointer to the node before
//    it to update its next pointer. This requires either counting nodes or using a
//    two-pointer technique to find the middle.
// 3. **Edge Cases**: Single node (delete and return nullptr), two nodes (delete
//    second), and ensuring no null pointer dereferences.
// 4. **Mental Roadmap**:
//    - Brute Force: Count nodes, traverse to node before middle, delete.
//    - Optimal: Use fast-slow pointers to find middle in one pass, delete.



// ==============================================================================
// Approach 1: Brute Force
// ==============================================================================


// Logic:
//   - Compute the length of the list by traversing it.
//   - Calculate middle index as floor(length/2).
//   - Traverse to the node before the middle (length/2 - 1 steps).
//   - Delete the next node by updating pointers and freeing memory.
// Steps:
//   1. If list is empty, return nullptr.
//   2. If length == 1, delete head, return nullptr.
//   3. Compute length (n).
//   4. Set mid = n/2.
//   5. Traverse mid-1 steps to reach node before middle.
//   6. Update next pointer to skip middle node, delete it.
//   7. Return head.
// Complexity:
//   - Time: O(n) for length + O(n/2) for traversal = O(n).
//   - Space: O(1), only uses a few pointers.
// Limitations:
//   - Requires two passes (one for length, one for deletion).
//   - Extra traversal increases runtime slightly.


// ==============================================================================
// Approach 2: Optimal (Fast-Slow Pointers)
// ==============================================================================



// Logic:
//   - Use two pointers: fast moves twice as fast as slow.
//   - When fast reaches the end, slow is at the middle (or second middle for even).
//   - Keep a prev pointer to track the node before slow for deletion.
//   - Adjust for even-length lists to ensure second middle is deleted.
// Steps:
//   1. If list is empty or single node, delete head, return nullptr.
//   2. Initialize slow = head, fast = head, prev = nullptr.
//   3. Move fast by 2, slow by 1 until fast reaches end or null.
//   4. For even-length lists (fast != nullptr), advance slow and prev once more.
//   5. Delete slow node by updating prev->next, free memory.
//   6. Return head.
// Complexity:
//   - Time: O(n/2) = O(n), single pass to find middle.
//   - Space: O(1), only uses three pointers.
// Why Optimal:
//   - Single pass reduces traversal compared to brute force.
//   - No need to compute length explicitly, leveraging pointer movement.
// Trade-offs:
//   - Slightly more complex logic due to pointer management.
//   - Must carefully handle even/odd cases to delete correct node.

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Helper function to compute length of linked list
int findLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Helper function to delete the node after temp
void deleteNode(Node* temp) {
    // Safety check to avoid null pointer dereference
    if (temp == nullptr || temp->next == nullptr) return;
    Node* front = temp->next;
    temp->next = temp->next->next;
    delete front;
}

// Brute Force Approach
Node* deleteMiddleBrute(Node* head) {
    // Handle empty list
    if (head == nullptr) return nullptr;
    
    // Compute length
    int length = findLength(head);
    
    // Single node case
    if (length == 1) {
        delete head;
        return nullptr;
    }
    
    // Calculate middle index
    int mid = length / 2;
    Node* curr = head;
    
    // Traverse to node before middle (mid-1 steps)
    for (int i = 0; i < mid - 1; i++) {
        curr = curr->next;
    }
    
    // Delete the middle node
    deleteNode(curr);
    
    return head;
}

// Optimal Approach (Fast-Slow Pointers)
Node* deleteMiddleOptimal(Node* head) {
    // Handle empty or single node
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    
    // Initialize pointers
    Node* slow = head;
    Node* fast = head;
    Node* prev = nullptr;
    
    // Move fast by 2, slow by 1
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    
    // For even-length lists, advance to second middle
    if (fast != nullptr) {
        prev = slow;
        slow = slow->next;
    }
    
    // Delete the middle node
    prev->next = slow->next;
    delete slow;
    
    return head;
}

// Main function to test the solution
int main() {
    // Create sample linked list: 1->2->3->4->5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    // Test Brute Force
    Node* result = deleteMiddleBrute(head);
    
    // Print the updated linked list
    Node* temp = result;
    while (temp) {
        cout << temp->val;
        if (temp->next) cout << "->";
        temp = temp->next;
    }
    cout << endl;
    
    // Clean up memory
    while (result) {
        Node* temp = result;
        result = result->next;
        delete temp;
    }
    
    // Recreate list for Optimal approach test
    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    // Test Optimal
    result = deleteMiddleOptimal(head);
    
    // Print the updated linked list
    temp = result;
    while (temp) {
        cout << temp->val;
        if (temp->next) cout << "->";
        temp = temp->next;
    }
    cout << endl;
    
    // Clean up memory
    while (result) {
        Node* temp = result;
        result = result->next;
        delete temp;
    }
    
    return 0;
}
