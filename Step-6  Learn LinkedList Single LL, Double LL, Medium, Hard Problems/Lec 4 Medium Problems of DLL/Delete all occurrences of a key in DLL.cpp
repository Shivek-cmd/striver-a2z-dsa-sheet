/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Delete all occurrences of a key in a doubly linked list
Given the head of a doubly linked list and an integer target, delete all nodes with the value 
target and return the head of the modified linked list.

Examples:
Input: head -> 1 <-> 2 <-> 3 <-> 1 <-> 4, target = 1
Output: head -> 2 <-> 3 <-> 4
Explanation: All nodes with value 1 were removed.

Input: head -> 2 <-> 3 <-> -1 <-> 4 <-> 2, target = 2
Output: head -> 3 <-> -1 <-> 4
Explanation: All nodes with value 2 were removed.

Constraints:
- The number of nodes in the list is in the range [0, 10^5].
- -10^9 <= Node.val, target <= 10^9.
- The list is a valid doubly linked list with proper prev/next pointers.

Edge Cases:
- Empty list (head = nullptr).
- List with all nodes having the target value.
- List with no nodes having the target value.
- Single node list with/without target value.
- Target value at head, middle, or tail.

==============================================================================
Section 2: Solution Approaches
==============================================================================
Observations and Analytical Thought Process:
- The problem involves modifying a doubly linked list by removing nodes with a specific value.
- Key patterns:
  - Doubly linked list allows traversal and modification using prev/next pointers.
  - Deleting a node requires updating the prev pointer of the next node and the next pointer 
    of the previous node.
  - Special handling is needed for the head node, as it has no previous node.
  - Multiple occurrences of the target may appear consecutively or scattered.
- Intuitive insights:
  - Iterate through the list, checking each node’s value against the target.
  - Handle head separately to update the returned pointer if head nodes are deleted.
  - Use a helper function to delete a single node to reduce code redundancy.
  - Track the previous node to correctly update pointers during deletion.
- Mental roadmap:
  1. Check for empty list.
  2. Remove target nodes at the head to establish the new head.
  3. Traverse the list, deleting target nodes while maintaining prev/next pointers.
  4. Use a helper function for node deletion to handle pointer updates.

----------------------------------------
Approach 1: Brute Force (Using Map to Track Targets)
----------------------------------------
Logic:
- Traverse the list to identify all nodes with the target value and store them in a map.
- Traverse again, deleting nodes identified in the map using a helper function.
- Handle head separately if it’s a target node.

Steps:
1. If head is nullptr, return nullptr.
2. Use an unordered_map to store nodes with value equal to target.
3. Traverse the list again, calling deleteKthNode for each mapped node.
4. Update head if the original head was a target node.

Complexity:
- Time: O(n) for two passes (one to build map, one to delete).
- Space: O(n) for the unordered_map in worst case (all nodes are target).
- Justification: Map stores at most n nodes; each traversal is linear.

Limitations:
- Unnecessary space usage due to map.
- Two passes increase constant factor in time complexity.
- Complex logic for maintaining pointers during deletion.

----------------------------------------
Approach 2: Better (Single Pass with Helper Function)
----------------------------------------
Logic:
- Use a single pass to delete nodes as they are encountered.
- Handle head nodes separately to update the head pointer.
- Use a helper function (deleteKthNode) to delete a node and return the next node.
- Track the previous node to pass to deleteKthNode for correct pointer updates.

Steps:
1. If head is nullptr, return nullptr.
2. While head’s value is target, delete head and update head.
3. Traverse the list with curr and prev pointers.
4. If curr->val == target, call deleteKthNode(prev, curr) and update curr.
5. Otherwise, advance prev and curr.
6. Return the modified head.

Complexity:
- Time: O(n) for single pass through the list.
- Space: O(1) as only pointers are used.
- Justification: Each node is visited once; no additional data structures.

Advantages:
- More efficient than brute force due to single pass and no extra space.
- Cleaner logic with helper function handling deletion.

Limitations:
- Still requires careful pointer management to avoid dangling pointers.
- Head handling adds slight complexity.

----------------------------------------
Approach 3: Optimal (Direct Single Pass)
----------------------------------------
Logic:
- Similar to the better approach but eliminates the need for a separate helper function.
- Directly manipulate prev/next pointers during traversal.
- Handle head and non-head cases in a unified loop for simplicity.

Steps:
1. If head is nullptr, return nullptr.
2. While head’s value is target, delete head and update head.
3. Traverse with curr and prev, directly updating pointers for target nodes:
   - If curr->val == target, link prev->next to curr->next and curr->next->prev to prev, then delete curr.
   - Update curr to next node.
4. Return the modified head.

Complexity:
- Time: O(n) for single pass.
- Space: O(1) as only pointers are used.
- Justification: Same as better approach but with fewer function calls.

Why Optimal:
- Minimizes function call overhead by inlining deletion logic.
- Simplest pointer manipulation with no external dependencies.
- Handles all edge cases efficiently in a single pass.

Trade-offs:
- Slightly less modular due to no helper function.
- Deletion logic is embedded in the main function, which may reduce reusability.

==============================================================================
Section 3: Code Implementation
==============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for doubly-linked list node
struct Node {
    int val;
    Node *next;
    Node *prev;
    Node(int x) : val(x), next(nullptr), prev(nullptr) {}
};

// Helper function for deleting a node (used in Brute Force and Better approaches)
Node* deleteKthNode(Node* prev, Node* front) {
    if (front == nullptr) {
        return nullptr;
    }
    Node* nextNode = front->next;
    if (front->prev != nullptr) {
        front->prev->next = front->next; // Update prev node’s next pointer
    }
    if (front->next != nullptr) {
        front->next->prev = front->prev; // Update next node’s prev pointer
    }
    delete front; // Free memory
    return nextNode; // Return next node for traversal
}

// Approach 1: Brute Force (Using Map)
Node* deleteAllOccurrencesBrute(Node* head, int target) {
    if (head == nullptr) {
        return nullptr; // Handle empty list
    }

    // Step 1: Store target nodes in map
    unordered_map<Node*, int> targetNodes;
    Node* temp = head;
    while (temp) {
        if (temp->val == target) {
            targetNodes[temp] = temp->val;
        }
        temp = temp->next;
    }

    // Step 2: Handle head nodes
    while (head != nullptr && targetNodes.find(head) != targetNodes.end()) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr; // Update new head’s prev pointer
        }
        delete temp;
    }

    // Step 3: Traverse and delete target nodes
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        if (targetNodes.find(curr) != targetNodes.end()) {
            curr = deleteKthNode(prev, curr); // Delete node and get next
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return head;
}

// Approach 2: Better (Single Pass with Helper)
Node* deleteAllOccurrencesBetter(Node* head, int target) {
    if (head == nullptr) {
        return nullptr; // Handle empty list
    }

    // Handle head nodes with target value
    while (head != nullptr && head->val == target) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr; // Update new head’s prev pointer
        }
        delete temp; // Free memory
    }

    // Traverse and delete remaining target nodes
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->val == target) {
            curr = deleteKthNode(prev, curr); // Delete node and get next
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return head;
}

// Approach 3: Optimal (Direct Single Pass)
Node* deleteAllOccurrencesOptimal(Node* head, int target) {
    if (head == nullptr) {
        return nullptr; // Handle empty list
    }

    // Handle head nodes with target value
    while (head != nullptr && head->val == target) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr; // Update new head’s prev pointer
        }
        delete temp; // Free memory
    }

    // Traverse and delete remaining target nodes
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->val == target) {
            if (prev != nullptr) {
                prev->next = curr->next; // Link prev to next
            }
            if (curr->next != nullptr) {
                curr->next->prev = prev; // Link next to prev
            }
            Node* temp = curr;
            curr = curr->next; // Move to next node
            delete temp; // Free memory
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return head;
}

int main() {
    // Create a sample doubly linked list: 1 <-> 2 <-> 3 <-> 1 <-> 4
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->prev = head;
    head->next->next = new Node(3);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(1);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new Node(4);
    head->next->next->next->next->prev = head->next->next->next;

    int target = 1;

    // Test Optimal Approach
    head = deleteAllOccurrencesOptimal(head, target);

    // Print the modified list
    Node* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " <-> ";
        curr = curr->next;
    }
    cout << endl;

    // Clean up memory
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}