#include <bits/stdc++.h>
using namespace std;

// Definition for the linked list node
struct Node {
    int val;
    Node* next;
    Node* child;
    Node(int x) : val(x), next(NULL), child(NULL) {}
};

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
/*
Problem: Flattening a Linked List
- Given a linked list with N head nodes, each node has two pointers:
  - 'next': points to the next node in the main list.
  - 'child': points to a sorted linked list where the current node is the head.
- The task is to flatten the linked list into a single sorted linked list, connected via 'next' pointers.

Example:
Input:
5 -> 10 -> 19 -> 28
|    |     |     |
7    20    22    35
|          |     |
8          50    40
|                |
30               45
Output: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50

Constraints:
- 0 <= N <= 10^4 (number of nodes in main list)
- 1 <= Node.val <= 10^5
- All child linked lists are sorted
- Total number of nodes (main + child lists) is within practical limits

Edge Cases:
- Empty list (head = nullptr)
- Single node with no child or next
- No child lists (only main list)
- Single node with child list
- Large number of nodes in child lists
*/

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================
/*
Observations and Analytical Thought Process:
1. **Core Insight**: The linked list is a multi-level structure where each node in the main list (via 'next') can have a sorted child list (via 'child'). Flattening requires combining all nodes into a single sorted list using 'next' pointers.
2. **Key Pattern**: Since child lists are already sorted, the problem resembles merging multiple sorted lists, but the structure requires handling both 'next' and 'child' pointers.
3. **Intuitive Approach**: Collect all node values, sort them, and create a new list. This is straightforward but uses extra space.
4. **Recursive Insight**: The list can be flattened by recursively processing the 'next' list and merging it with the current node's child list, leveraging the sorted nature of child lists.
5. **Edge Cases to Handle**:
   - Empty list: return nullptr.
   - Single node: include its child list if present.
   - No child lists: process only the main list.
   - Large child lists: ensure all nodes are included without missing any.
6. **Mental Roadmap**:
   - Traverse the main list and child lists to collect or process nodes.
   - Use sorting or merging to ensure the output is sorted.
   - Reconstruct the list using 'next' pointers, setting 'child' pointers to nullptr.
   - Handle edge cases explicitly to avoid null pointer issues.

Approach 1: Brute Force (Collect and Sort)
a. Logic:
   - Traverse the entire structure (main list and child lists) to collect all node values in a vector.
   - Sort the vector to achieve the required order.
   - Create a new linked list from the sorted values, linking nodes via 'next' pointers.
b. Steps:
   1. Handle empty list: return nullptr.
   2. Traverse main list (via 'next'):
      - Add current node’s value to vector.
      - Traverse child list (via 'child') and add values to vector.
   3. Sort the vector.
   4. Create new linked list from sorted vector.
   5. Return new list’s head.
c. Complexity:
   - Time: O(n log n), where n is the total number of nodes (main + child lists). Traversal is O(n), sorting is O(n log n).
   - Space: O(n) for the vector, plus O(n) for the new list (though original list memory is reused in practice).
d. Limitations:
   - High space usage due to vector.
   - Sorting is computationally expensive compared to leveraging existing sorted child lists.
   - Creates a new list, potentially wasting memory if original nodes could be reused.

Approach 2: Recursive Merge (Optimal)
a. Logic:
   - Recursively flatten the 'next' list, then merge the current node’s child list with the flattened result.
   - Use a merge function to combine two sorted lists (child lists) into a single sorted list (via 'next' pointers).
   - This leverages the sorted nature of child lists to avoid explicit sorting.
b. Steps:
   1. Base case: if head is nullptr or has no next, return head.
   2. Recursively flatten the next list (head->next).
   3. Disconnect head->next to isolate current node’s child list.
   4. Merge current node (with its child list) and the flattened next list.
   5. Return merged list’s head.
c. Complexity:
   - Time: O(n log m), where n is the total number of nodes, m is the number of main list nodes. Each merge is O(k) where k is the length of the lists, and recursion depth is O(m).
   - Space: O(m) for recursion stack, where m is the main list length. No extra data structures needed.
d. Advantages:
   - Leverages sorted child lists, avoiding explicit sorting.
   - Reuses existing nodes, reducing memory allocation compared to brute force.
e. Limitations:
   - Recursive stack space for deep main lists.
   - Slightly more complex due to pointer manipulation.

Optimal Approach Justification:
- The recursive merge approach is optimal because it avoids the O(n log n) sorting cost of the brute force approach, leveraging the pre-sorted child lists. It minimizes extra space (no vector) and reuses nodes, making it more efficient for large inputs while maintaining simplicity.
*/

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Brute Force: Collect all values, sort, and create new list
Node* flattenLinkedListBrute(Node* head) {
    // Handle empty list
    if (!head) {
        return nullptr;
    }
    
    // Collect all values in a vector
    vector<int> values;
    Node* curr = head;
    while (curr) {
        // Add current node’s value
        values.push_back(curr->val);
        
        // Traverse child list
        Node* childCurr = curr->child;
        while (childCurr) {
            values.push_back(childCurr->val);
            childCurr = childCurr->child;
        }
        
        // Move to next node in main list
        curr = curr->next;
    }
    
    // Sort the vector
    sort(values.begin(), values.end());
    
    // Create new sorted linked list
    if (values.empty()) {
        return nullptr;
    }
    
    Node* newHead = new Node(values[0]);
    Node* newCurr = newHead;
    for (size_t i = 1; i < values.size(); i++) {
        Node* newNode = new Node(values[i]);
        newCurr->next = newNode;
        newCurr = newCurr->next;
    }
    
    return newHead;
}

// Helper for Optimal: Merge two sorted lists (linked via child pointers) into a sorted list (via next pointers)
Node* mergeTwoList(Node* list1, Node* list2) {
    // Create dummy node for merged list
    Node* dummyNode = new Node(-1);
    Node* res = dummyNode;
    
    // Merge while both lists have nodes
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            res->next = list1;
            res = list1;
            list1 = list1->child; // Advance in child list
        } else {
            res->next = list2;
            res = list2;
            list2 = list2->child; // Advance in child list
        }
    }
    
    // Append remaining nodes
    if (list1) {
        res->next = list1;
    }
    if (list2) {
        res->next = list2;
    }
    
    Node* result = dummyNode->next;
    delete dummyNode; // Free dummy node
    return result;
}

// Optimal: Recursive merge approach
Node* flattenLinkedListOptimal(Node* head) {
    // Base case: empty or no next node
    if (!head || !head->next) {
        return head;
    }
    
    // Recursively flatten the next list
    Node* nextFlattened = flattenLinkedListOptimal(head->next);
    
    // Disconnect next to process current node’s child list
    head->next = nullptr;
    
    // Merge current node (with child list) and flattened next list
    return mergeTwoList(head, nextFlattened);
}

int main() {
    // Create sample linked list
    Node* head = new Node(5);
    head->next = new Node(10);
    head->next->next = new Node(19);
    head->next->next->next = new Node(28);
    
    head->child = new Node(7);
    head->child->child = new Node(8);
    head->child->child->child = new Node(30);
    
    head->next->child = new Node(20);
    
    head->next->next->child = new Node(22);
    head->next->next->child->child = new Node(50);
    
    head->next->next->next->child = new Node(35);
    head->next->next->next->child->child = new Node(40);
    head->next->next->next->child->child->child = new Node(45);
    
    // Flatten the linked list using optimal approach
    Node* result = flattenLinkedListOptimal(head);
    
    // Print the result
    Node* curr = result;
    while (curr != NULL) {
        cout << curr->val;
        if (curr->next != NULL) cout << " -> ";
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
    
    // Note: Original list memory is not freed to avoid complexity
    return 0;
}