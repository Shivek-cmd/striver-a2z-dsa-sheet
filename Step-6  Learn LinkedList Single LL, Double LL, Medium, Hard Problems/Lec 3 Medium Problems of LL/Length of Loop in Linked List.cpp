#include <bits/stdc++.h>

using namespace std;

// Node class represents a node in a linked list
class Node {
public:
    int data;
    Node* next;

    Node(int data1, Node* next1 = nullptr) {
        data = data1;
        next = next1;
    }
};

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Given the head of a singly linked list, determine the length of the loop (cycle) present in the linked list.
If there is no loop, return 0.

Example 1:
Input: LL: 1 -> 2 -> 3 -> 4 -> 5
                 ^________|
Output: 3
Explanation: The linked list contains a loop starting at the node with value 3. The loop consists of nodes 3 -> 4 -> 5 -> 3, which has a length of 3.
ASCII Diagram:
       +-----+     +-----+     +-----+     +-----+     +-----+
       |  1  |---->|  2  |---->|  3  |---->|  4  |---->|  5  |
       +-----+     +-----+     +-----+     +-----+     +-----+
                              ^_____________________|

Example 2:
Input: LL: 1 -> 2 -> 3 -> 4 -> 9 -> 9 -> nullptr
Output: 0
Explanation: The linked list does not contain a loop, so the length is 0.
ASCII Diagram:
       +-----+     +-----+     +-----+     +-----+     +-----+     +-----+
       |  1  |---->|  2  |---->|  3  |---->|  4  |---->|  9  |---->|  9  |----> nullptr
       +-----+     +-----+     +-----+     +-----+     +-----+     +-----+

Example 3: Single Node with Self-Loop
Input: LL: 1
           ^__|
Output: 1
Explanation: The linked list has a single node with value 1, and its next pointer points to itself, forming a loop of length 1.
ASCII Diagram:
       +-----+
       |  1  |----+
       +-----+    |
           ^______|

Constraints:
- Number of nodes: 0 <= N <= 10^5
- Node values: -10^9 <= value <= 10^9
- List may be empty (head = nullptr).

Edge Cases:
- Empty list (head = nullptr): Return 0.
- Single node with no cycle: Return 0.
- Single node with self-loop: Return 1.
- Large lists with or without loops.
*/

/*
Observations:
1. **Key Pattern**: A loop in a linked list forms a cycle where nodes repeat, and its length is the number of nodes in the cycle.
2. **Intuitive Insight**: To find the loop length, we need to detect the cycle and count the nodes in one complete traversal of the loop.
3. **Challenge**: Distinguishing between no cycle, a small cycle (e.g., self-loop), and a large cycle requires careful handling of node revisits or pointer behavior.
4. **Efficient Detection**: Cycles create a circular structure, so we can use a hash set to track nodes or leverage pointer speed differences to locate the cycle and measure its length.
5. **Mental Roadmap**:
   - Track visited nodes with a hash set, using indices to compute the cycle length when a node is revisited.
   - Use Floyd’s Tortoise and Hare algorithm to detect the cycle, then count nodes in the loop by traversing it.
   - Handle edge cases like empty lists, single nodes, or no cycles explicitly.
   - Optimize for space (O(1)) or simplicity (hashing) based on requirements.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Hashing (Brute Force)
----------------------------------------
Logic:
- Traverse the linked list, storing each node’s address and its index (position) in a hash map.
- When a node is revisited, the cycle length is the difference between the current index and the stored index of the revisited node.
- If traversal reaches nullptr, no cycle exists, so return 0.

Steps:
1. Initialize an unordered_map to store node pointers and their indices.
2. Traverse the list with a temporary pointer (temp = head) and a counter (index).
3. For each node:
   - If node is in the map, return the cycle length as (current index - stored index).
   - Store node and current index in the map.
   - Move to next node, increment index.
4. If temp becomes nullptr, return 0 (no cycle).

Time Complexity: O(N * log(N))
- Traversal: O(N), where N is the number of nodes.
- Hash map operations (insert, search): O(log(N)) in worst case for unordered_map.
- Total: O(N * log(N)).

Space Complexity: O(N)
- Hash map stores up to N nodes.

Limitations:
- Requires O(N) extra memory, which can be significant for large lists.
- Slower than pointer-based methods due to hash operations.

Trade-offs:
- Simple to implement and understand.
- Memory-intensive, not ideal for space-constrained environments.

----------------------------------------
Approach 2: Floyd’s Tortoise and Hare (Optimal)
----------------------------------------
Logic:
- Use two pointers (slow and fast) to detect a cycle.
- Once they meet in the cycle, count the nodes in the loop by moving one pointer around the cycle until it returns to the meeting point.
- If no cycle is detected, return 0.
- Intuition: The meeting point is inside the cycle, and traversing from there counts the cycle’s length.

Steps:
1. Initialize slow and fast pointers to head.
2. Phase 1: Detect cycle:
   - Move slow by 1 step, fast by 2 steps.
   - If they meet, a cycle exists; proceed to count length.
   - If fast or fast->next is nullptr, return 0 (no cycle).
3. Phase 2: Count cycle length:
   - From the meeting point, move one pointer (e.g., fast) one step at a time, counting steps until it returns to the meeting point.
   - Return the count as the cycle length.

Time Complexity: O(N)
- Phase 1: Cycle detection takes O(N) steps (fast either reaches nullptr or meets slow).
- Phase 2: Counting the cycle length takes O(C) steps, where C is the cycle length (C <= N).
- Total: O(N).

Space Complexity: O(1)
- Only uses two pointers, regardless of list size.

Limitations:
- Requires understanding of cycle detection to implement correctly.
- Slightly more complex than hashing due to two-phase logic.

Trade-offs:
- Extremely space-efficient (O(1)).
- Faster than hashing due to constant-time pointer operations.
- Optimal for performance in both time and space.

Why Optimal?
- Floyd’s algorithm eliminates the need for extra memory, making it ideal for large lists.
- O(N) time with O(1) space is the best possible for this problem without modifying the list.
- Simple pointer operations are faster than hash map operations.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Hashing
int findLoopLengthHashing(Node* head) {
    // Handle empty list
    if (!head) return 0;

    // Map to store visited nodes and their indices
    unordered_map<Node*, int> visited;
    Node* temp = head;
    int index = 0;

    // Traverse the list
    while (temp) {
        // If node is already visited, calculate cycle length
        if (visited.find(temp) != visited.end()) {
            return index - visited[temp];
        }
        // Store node and its index
        visited[temp] = index;
        // Move to next node, increment index
        temp = temp->next;
        index++;
    }

    // No cycle found
    return 0;
}

// Approach 2: Floyd’s Tortoise and Hare
int findLoopLengthFloyd(Node* head) {
    // Handle empty list or single node
    if (!head || !head->next) return 0;

    // Step 1: Detect cycle using slow and fast pointers
    Node* slow = head;
    Node* fast = head;
    bool hasCycle = false;

    // Move slow (1 step) and fast (2 steps) until they meet or reach nullptr
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    // If no cycle, return 0
    if (!hasCycle) return 0;

    // Step 2: Count cycle length
    int length = 1;
    fast = fast->next; // Move fast one step from meeting point
    while (fast != slow) {
        fast = fast->next; // Move one step
        length++;          // Increment length
    }

    return length;
}

// Utility function to create a linked list with optional cycle
Node* createLinkedList(int arr[], int n, int cyclePos = -1) {
    if (n == 0) return nullptr;

    Node* head = new Node(arr[0]);
    Node* temp = head;
    Node* cycleNode = nullptr;

    // Create list and track node at cyclePos
    for (int i = 1; i < n; ++i) {
        temp->next = new Node(arr[i]);
        temp = temp->next;
        if (i == cyclePos) {
            cycleNode = temp;
        }
    }

    // Create cycle if cyclePos is valid
    if (cyclePos != -1) {
        temp->next = cycleNode;
    }

    return head;
}

// Utility function to delete non-cyclic linked list
void deleteLinkedList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Test Case 1: List with loop of length 3
    int arr1[] = {1, 2, 3, 4, 5};
    Node* head1 = createLinkedList(arr1, 5, 2); // Loop at node with value 3
    cout << "Test Case 1 (Loop of length 3):\n";
    cout << "Hashing: Loop length = " << findLoopLengthHashing(head1) << endl;
    cout << "Floyd: Loop length = " << findLoopLengthFloyd(head1) << endl;

    // Test Case 2: List without loop
    int arr2[] = {1, 2, 3, 4, 9, 9};
    Node* head2 = createLinkedList(arr2, 6);
    cout << "\nTest Case 2 (No Loop):\n";
    cout << "Hashing: Loop length = " << findLoopLengthHashing(head2) << endl;
    cout << "Floyd: Loop length = " << findLoopLengthFloyd(head2) << endl;

    // Test Case 3: Single node with self-loop
    int arr3[] = {1};
    Node* head3 = createLinkedList(arr3, 1, 0); // Self-loop at node with value 1
    cout << "\nTest Case 3 (Self-Loop):\n";
    cout << "Hashing: Loop length = " << findLoopLengthHashing(head3) << endl;
    cout << "Floyd: Loop length = " << findLoopLengthFloyd(head3) << endl;

    // Test Case 4: Large list with loop of length 6
    int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Node* head4 = createLinkedList(arr4, 8, 2); // Loop at node with value 3
    cout << "\nTest Case 4 (Loop of length 6):\n";
    cout << "Hashing: Loop length = " << findLoopLengthHashing(head4) << endl;
    cout << "Floyd: Loop length = " << findLoopLengthFloyd(head4) << endl;

    // Test Case 5: Empty list
    Node* head5 = nullptr;
    cout << "\nTest Case 5 (Empty List):\n";
    cout << "Hashing: Loop length = " << findLoopLengthHashing(head5) << endl;
    cout << "Floyd: Loop length = " << findLoopLengthFloyd(head5) << endl;

    // Clean up non-cyclic list (Test Case 2)
    deleteLinkedList(head2);

    // Note: Cyclic lists (head1, head3, head4) are not deleted to avoid complexity
    return 0;
}