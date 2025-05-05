#include <bits/stdc++.h>
using namespace std;

// Observations for Solving the Intersection of Two Linked Lists Problem:
// 1. **Key Insight**: If two linked lists intersect, they share a common node, and all nodes after it are identical.
// 2. **Pattern Recognition**: The intersection point is where both lists converge. If no intersection exists, the result is null.
// 3. **Challenge**: Lists may have different lengths before the intersection, so we need to align them or detect the common node efficiently.
// 4. **Edge Cases**: Handle null lists, lists with no intersection, or intersection at the first node.
// 5. **Intuitive Approach**: Consider traversing both lists in a way that accounts for length differences or uses a set to track visited nodes.
// 6. **Mental Roadmap**: Start with a brute-force approach (checking each node), improve by aligning lengths, and optimize by equalizing traversal paths.

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================

// Problem: Given the heads of two singly linked lists (headA and headB), find the node where they intersect.
// If no intersection exists, return null.
// The intersection is defined as the node where both lists share the same memory address (not just value).

// Example 1:
// Input: List1 = [1,3,1,2,4], List2 = [3,2,4]
// Output: Node with value 2 (intersection starts at node 2)
// Explanation: Lists merge at node 2 and share nodes [2,4].

// Example 2:
// Input: List1 = [1,2,7], List2 = [2,8,1]
// Output: null
// Explanation: No intersection exists.

// Constraints:
// - Length of each list: [0, 10^4]
// - Node values: [-10^9, 10^9]
// - Lists may or may not intersect.
// - If they intersect, the intersection node is guaranteed to be reachable.

// Edge Cases:
// - One or both lists are empty (return null).
// - Lists intersect at the first node.
// - Lists have no intersection.
// - Lists have different lengths before the intersection.

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================




// ==============================================================================
// Approach 1: Brute Force (Using Hash Set)
// ==============================================================================



// Logic:
// - Store all nodes of the first list in a hash set.
// - Traverse the second list and check if any node exists in the hash set.
// - The first matching node is the intersection point.
// Steps:
// 1. Initialize an unordered_set to store node pointers.
// 2. Traverse list A, inserting each node into the set.
// 3. Traverse list B, checking each node against the set.
// 4. Return the first node found in the set or null if none.
// Time Complexity: O(n + m), where n and m are lengths of lists A and B (traverse each list once).
// Space Complexity: O(n), for storing nodes of list A in the hash set.
// Limitations:
// - Requires extra space for the hash set.
// - Not optimal if memory is a constraint.



// ==============================================================================
// Approach 2: Better (Length Difference)
// ==============================================================================


// Logic:
// - Compute the lengths of both lists.
// - Move the pointer of the longer list forward by the difference in lengths.
// - Traverse both lists simultaneously to find the first common node.
// Steps:
// 1. Calculate lengths of both lists (lenA and lenB).
// 2. Advance the head of the longer list by |lenA - lenB| nodes.
// 3. Traverse both lists in parallel until a common node is found or null is reached.
// 4. Return the common node or null.
// Time Complexity: O(n + m), for calculating lengths and traversing lists.
// Space Complexity: O(1), no extra space needed.
// Limitations:
// - Requires two passes to compute lengths before finding the intersection.
// - Less elegant than the optimal approach.


// ==============================================================================
// Approach 3: Optimal (Two Pointers)
// ==============================================================================



// Logic:
// - Use two pointers, t1 and t2, starting at heads of lists A and B.
// - Traverse both lists. When a pointer reaches the end, redirect it to the head of the other list.
// - After at most two switches, both pointers will have traveled the same total distance, meeting at the intersection or null.
// - This works because: If lists intersect, the distance from headA to intersection + headB to intersection is equalized.
// Steps:
// 1. Initialize t1 = headA, t2 = headB.
// 2. While t1 != t2:
//    - Move t1 and t2 to their next nodes.
//    - If t1 is null, set t1 = headB.
//    - If t2 is null, set t2 = headA.
// 3. Return t1 (or t2) as the intersection node or null.
// Time Complexity: O(n + m), where n and m are list lengths (each node visited at most twice).
// Space Complexity: O(1), no extra space.
// Why Optimal:
// - Single pass with no need to compute lengths explicitly.
// - Elegant and memory-efficient, handling all cases seamlessly.
// Limitations:
// - Slightly harder to understand initially compared to brute force.

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Definition for singly-linked list
struct Node {
    int val;
    Node *next;
    Node(int x) : val(x), next(nullptr) {}
};

// Brute Force: Using Hash Set
Node *getIntersectionNodeBrute(Node *headA, Node *headB) {
    unordered_set<Node*> nodeSet; // Set to store nodes of list A
    Node *temp = headA;
    
    // Store all nodes from list A
    while (temp) {
        nodeSet.insert(temp);
        temp = temp->next;
    }
    
    temp = headB;
    // Check list B for intersection
    while (temp) {
        if (nodeSet.find(temp) != nodeSet.end()) {
            return temp; // First common node found
        }
        temp = temp->next;
    }
    
    return nullptr; // No intersection
}

// Helper function to compute list length
int getLength(Node *head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// Better: Length Difference
Node *getIntersectionNodeBetter(Node *headA, Node *headB) {
    // Handle null inputs
    if (!headA || !headB) return nullptr;
    
    // Get lengths of both lists
    int lenA = getLength(headA);
    int lenB = getLength(headB);
    
    // Align longer list by advancing its head
    while (lenA > lenB) {
        headA = headA->next;
        lenA--;
    }
    while (lenB > lenA) {
        headB = headB->next;
        lenB--;
    }
    
    // Traverse both lists in parallel
    while (headA && headB && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    
    return headA; // Intersection node or null
}

// Optimal: Two Pointers
Node *getIntersectionNodeOptimal(Node *headA, Node *headB) {
    // Handle null inputs
    if (!headA || !headB) return nullptr;
    
    Node *t1 = headA;
    Node *t2 = headB;
    
    // Traverse until pointers meet or both become null
    while (t1 != t2) {
        t1 = t1 ? t1->next : headB; // Switch to headB when t1 reaches end
        t2 = t2 ? t2->next : headA; // Switch to headA when t2 reaches end
    }
    
    return t1; // Intersection node or null
}
