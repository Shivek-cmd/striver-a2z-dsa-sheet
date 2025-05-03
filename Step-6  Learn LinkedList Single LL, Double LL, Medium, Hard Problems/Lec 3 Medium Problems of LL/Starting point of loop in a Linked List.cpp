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
Problem: Given the head of a singly linked list that may contain a cycle, return the starting point of the cycle (the node where the cycle begins).
If there is no cycle, return nullptr.

Example 1:
Input: LL: 1 -> 2 -> 3 -> 4 -> 5
                 ^________|
Output: Node with value 3
Explanation: The linked list contains a cycle starting at the node with value 3. The last node (5) points back to the node with value 3, forming a loop of size 3 (3 -> 4 -> 5 -> 3).
ASCII Diagram:
       +-----+     +-----+     +-----+     +-----+     +-----+
       |  1  |---->|  2  |---->|  3  |---->|  4  |---->|  5  |
       +-----+     +-----+     +-----+     +-----+     +-----+
                              ^_____________________|

Example 2:
Input: LL: 1 -> 2 -> 3 -> 4 -> 9 -> 9 -> nullptr
Output: nullptr
Explanation: The linked list does not contain a cycle, so there is no starting point.
ASCII Diagram:
       +-----+     +-----+     +-----+     +-----+     +-----+     +-----+
       |  1  |---->|  2  |---->|  3  |---->|  4  |---->|  9  |---->|  9  |----> nullptr
       +-----+     +-----+     +-----+     +-----+     +-----+     +-----+

Example 3: Single Node with Self-Loop
Input: LL: 1
           ^__|
Output: Node with value 1
Explanation: The linked list has a single node with value 1, and its next pointer points to itself, forming a cycle of size 1.
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
- Empty list (head = nullptr): Return nullptr.
- Single node with no cycle: Return nullptr.
- Single node with self-loop: Return the node itself.
- Cycle starting at the head.
- Large lists with or without cycles.
*/

/*
Observations:
1. **Key Pattern**: A cycle in a linked list implies a node is revisited, detectable by tracking nodes or exploiting pointer behavior in a loop.
2. **Intuitive Insight**: The cycle’s starting point is where a node’s next pointer points back to a previous node. We can either track all nodes visited or use pointer speed differences to locate this point.
3. **Challenge**: Identifying the exact cycle start requires distinguishing node identity (address) from value and handling cases where the cycle starts at the head or involves a single node.
4. **Efficient Detection**: A cycle creates a circular structure, so pointers moving at different speeds (e.g., slow and fast) can meet inside the cycle, and a second phase can pinpoint the start.
5. **Mental Roadmap**:
   - Use a hash set to store visited nodes and return the first revisited node as the cycle start.
   - Use Floyd’s Tortoise and Hare algorithm to detect the cycle and then find the cycle’s start by aligning pointers.
   - Handle edge cases like empty lists, single nodes, or cycles at the head explicitly.
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
- Traverse the linked list and store each node’s address in a hash set.
- The first node encountered that is already in the set is the cycle’s starting point.
- If traversal reaches nullptr, no cycle exists.

Steps:
1. Initialize an unordered_set to store node pointers.
2. Traverse the list using a temporary pointer (temp = head).
3. For each node:
   - If node is in the set, return it as the cycle’s start.
   - Add node to the set.
   - Move to next node.
4. If temp becomes nullptr, return nullptr (no cycle).

Time Complexity: O(N * log(N))
- Traversal: O(N), where N is the number of nodes.
- Hash set operations (insert, search): O(log(N)) in worst case for unordered_set.
- Total: O(N * log(N)) due to N nodes and log(N) per operation.

Space Complexity: O(N)
- Hash set stores up to N nodes.

Limitations:
- Requires O(N) extra memory, which can be significant for large lists.
- Slower than pointer-based methods due to hash operations.

Trade-offs:
- Simple and intuitive, easy to implement.
- Memory-intensive, not ideal for space-constrained environments.

----------------------------------------
Approach 2: Floyd’s Tortoise and Hare (Optimal)
----------------------------------------
Logic:
- Use two pointers: slow (moves 1 step) and fast (moves 2 steps) to detect a cycle.
- If they meet, a cycle exists. Reset slow to head and move both pointers one step at a time; their meeting point is the cycle’s start.
- Intuition: The distance from head to cycle start equals the distance from the meeting point to the cycle start (adjusted by cycle length).

Steps:
1. Initialize slow and fast pointers to head.
2. Phase 1: Detect cycle:
   - Move slow by 1 step, fast by 2 steps.
   - If they meet, a cycle exists; break.
   - If fast or fast->next is nullptr, return nullptr (no cycle).
3. Phase 2: Find cycle start:
   - Reset slow to head.
   - Move slow and fast one step at a time.
   - Return their meeting point as the cycle’s start.

Time Complexity: O(N)
- Phase 1: Fast pointer either reaches nullptr or meets slow in O(N) steps.
- Phase 2: Slow and fast meet at cycle start in O(N) steps (proportional to distance to cycle start).
- Total: O(N).

Space Complexity: O(1)
- Only uses two pointers, regardless of list size.

Limitations:
- Requires understanding of cycle detection and distance alignment.
- Does not provide cycle length or other metadata without additional logic.

Trade-offs:
- Extremely space-efficient (O(1)).
- Faster than hashing due to constant-time pointer operations.
- Slightly more complex to understand but optimal for performance.

Why Optimal?
- Floyd’s algorithm uses O(1) space, making it ideal for large lists.
- O(N) time with minimal operations (pointer movements) is the best possible without modifying the list.
- Eliminates the need for extra data structures, reducing overhead.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Hashing
Node* findCycleStartHashing(Node* head) {
    // Handle empty list
    if (!head) return nullptr;

    // Set to store visited nodes
    unordered_map<Node*, bool> visited;
    Node* temp = head;

    // Traverse the list
    while (temp) {
        // If node is already visited, it is the cycle's starting point
        if (visited.find(temp) != visited.end()) {
            return temp; // Return the node
        }
        // Mark node as visited
        visited[temp] = true;
        // Move to next node
        temp = temp->next;
    }

    // No cycle found
    return nullptr;
}

// Approach 2: Floyd’s Tortoise and Hare
Node* findCycleStartFloyd(Node* head) {
    // Handle empty list or single node
    if (!head || !head->next) return nullptr;

    // Step 1: Detect cycle using slow and fast pointers
    Node* slow = head;
    Node* fast = head;
    bool hasCycle = false;

    // Move slow (1 step) and fast (2 steps) until they meet or reach nullptr
    while (fast && fast->next) {
        slow = slow->next;          // Move slow by 1
        fast = fast->next->next;    // Move fast by 2
        if (slow == fast) {         // Cycle detected
            hasCycle = true;
            break;
        }
    }

    // If no cycle, return nullptr
    if (!hasCycle) return nullptr;

    // Step 2: Find cycle start
    // Reset slow to head, move both pointers one step at a time
    slow = head;
    while (slow != fast) {
        slow = slow->next;  // Move slow by 1
        fast = fast->next;  // Move fast by 1
    }

    // Meeting point is the cycle start
    return slow;
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
    // Test Case 1: List with cycle starting at node with value 3
    int arr1[] = {1, 2, 3, 4, 5};
    Node* head1 = createLinkedList(arr1, 5, 2); // Cycle at node with value 3
    cout << "Test Case 1 (Cycle at 3):\n";
    Node* result1 = findCycleStartHashing(head1);
    cout << "Hashing: ";
    if (result1) {
        cout << "Cycle starts at node with value " << result1->data << endl;
    } else {
        cout << "No cycle" << endl;
    }
    result1 = findCycleStartFloyd(head1);
    cout << "Floyd: ";
    if (result1) {
        cout << "Cycle starts at node with value " << result1->data << endl;
    } else {
        cout << "No cycle" << endl;
    }

    // Test Case 2: List without cycle
    int arr2[] = {1, 2, 3, 4, 9, 9};
    Node* head2 = createLinkedList(arr2, 6);
    cout << "\nTest Case 2 (No Cycle):\n";
    Node* result2 = findCycleStartHashing(head2);
    cout << "Hashing: ";
    if (result2) {
        cout << "Cycle starts at node with value " << result2->data << endl;
    } else {
        cout << "No cycle" << endl;
    }
    result2 = findCycleStartFloyd(head2);
    cout << "Floyd: ";
    if (result2) {
        cout << "Cycle starts at node with value " << result2->data << endl;
    } else {
        cout << "No cycle" << endl;
    }

    // Test Case 3: Single node with self-loop
    int arr3[] = {1};
    Node* head3 = createLinkedList(arr3, 1, 0); // Self-loop at node with value 1
    cout << "\nTest Case 3 (Self-Loop at 1):\n";
    Node* result3 = findCycleStartHashing(head3);
    cout << "Hashing: ";
    if (result3) {
        cout << "Cycle starts at node with value " << result3->data << endl;
    } else {
        cout << "No cycle" << endl;
    }
    result3 = findCycleStartFloyd(head3);
    cout << "Floyd: ";
    if (result3) {
        cout << "Cycle starts at node with value " << result3->data << endl;
    } else {
        cout << "No cycle" << endl;
    }

    // Test Case  lã4: Cycle starting at head
    int arr4[] = {1, 2, 3};
    Node* head4 = createLinkedList(arr4, 3, 0); // Cycle at node with value 1
    cout << "\nTest Case 4 (Cycle at 1):\n";
    Node* result4 = findCycleStartHashing(head4);
    cout << "Hashing: ";
    if (result4) {
        cout << "Cycle starts at node with value " << result4->data << endl;
    } else {
        cout << "No cycle" << endl;
    }
    result4 = findCycleStartFloyd(head4);
    cout << "Floyd: ";
    if (result4) {
        cout << "Cycle starts at node with value " << result4->data << endl;
    } else {
        cout << "No cycle" << endl;
    }

    // Test Case 5: Empty list
    Node* head5 = nullptr;
    cout << "\nTest Case 5 (Empty List):\n";
    Node* result5 = findCycleStartHashing(head5);
    cout << "Hashing: ";
    if (result5) {
        cout << "Cycle starts at node with value " << result5->data << endl;
    } else {
        cout << "No cycle" << endl;
    }
    result5 = findCycleStartFloyd(head5);
    cout << "Floyd: ";
    if (result5) {
        cout << "Cycle starts at node with value " << result5->data << endl;
    } else {
        cout << "No cycle" << endl;
    }

    // Clean up non-cyclic list (Test Case 2)
    deleteLinkedList(head2);

    // Note: Cyclic lists (head1, head3, head4) are not deleted to avoid complexity
    return 0;
}