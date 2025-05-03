#include <iostream>
#include <unordered_map>

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
Problem: Detect whether a linked list contains a cycle (loop).
- A cycle exists if a node's next pointer points to a previously visited node.
- Input: Head of a singly linked list.
- Output: Boolean (true if cycle exists, false otherwise).

Example Inputs and Outputs:
1. Input: LL: 1 -> 2 -> 3 -> 4 -> 5 -> 3 (points back to node with value 3)
   Output: True
   Explanation: Node with value 5 points back to node with value 3, forming a cycle.
2. Input: LL: 1 -> 2 -> 3 -> 4 -> nullptr
   Output: False
   Explanation: No cycle exists; list terminates at nullptr.

Constraints:
- Number of nodes: 0 <= N <= 10^5
- Node values: -10^9 <= value <= 10^9
- List may be empty (head = nullptr).

Edge Cases:
- Empty list (head = nullptr): No cycle, return false.
- Single node with no cycle: No cycle, return false.
- Single node with self-loop: Cycle exists, return true.
- Large lists with/without cycles.
- Lists with duplicate values (cycle detection based on node identity, not value).
*/

/*
Observations:
1. **Key Pattern**: A cycle means revisiting a node, which can be detected by tracking nodes (by address) or observing pointer behavior.
2. **Intuitive Insight**: In a linear list, traversal reaches nullptr. In a cyclic list, traversal never ends unless detected.
3. **Challenge**: Distinguishing between duplicate values and actual cycles requires tracking node addresses, not just values.
4. **Efficient Detection**: A cycle implies a repeating path, so we can exploit pointer movement patterns (e.g., fast/slow pointers) or store visited nodes.
5. **Mental Roadmap**:
   - Track visited nodes using a hash set to detect repetition (hashing approach).
   - Use two pointers with different speeds to meet inside a cycle (Floyd’s algorithm).
   - Handle edge cases like empty lists or single-node cycles explicitly.
   - Optimize for space (O(1)) or time (O(N)) based on requirements.
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
- If a node is already in the set, a cycle exists.
- If traversal reaches nullptr, no cycle exists.

Steps:
1. Initialize an unordered_set to store node pointers.
2. Traverse the list using a temporary pointer (temp = head).
3. For each node:
   - If node is in the set, return true (cycle detected).
   - Add node to the set.
   - Move to next node.
4. If temp becomes nullptr, return false (no cycle).

Time Complexity: O(N * log(N))
- Traversal: O(N).
- Hash set operations (insert, search): O(log(N)) in worst case for unordered_set.
- Total: O(N * log(N)) due to N nodes and log(N) per operation.

Space Complexity: O(N)
- Hash set stores up to N nodes.

Limitations:
- Uses additional O(N) memory, which may be significant for large lists.
- Slower due to hash operations compared to constant-time pointer operations.

Trade-offs:
- Simple to implement and understand.
- Memory-intensive, not ideal for space-constrained environments.

----------------------------------------
Approach 2: Floyd’s Tortoise and Hare (Optimal)
----------------------------------------
Logic:
- Use two pointers: slow (moves 1 step) and fast (moves 2 steps).
- If a cycle exists, fast will eventually catch slow inside the cycle.
- If fast reaches nullptr, no cycle exists.
- Intuition: Fast pointer closes the gap by 1 node per iteration in a cycle.

Steps:
1. Initialize slow and fast pointers to head.
2. While fast and fast->next are not nullptr:
   - Move slow by 1 step (slow = slow->next).
   - Move fast by 2 steps (fast = fast->next->next).
   - If slow == fast, return true (cycle detected).
3. If loop exits (fast or fast->next is nullptr), return false.

Time Complexity: O(N)
- Fast pointer either reaches nullptr (no cycle) or meets slow in the cycle.
- In a cycle, fast catches slow in O(N) steps, as the gap reduces by 1 per iteration.
- Total: Linear time proportional to list length.

Space Complexity: O(1)
- Only two pointers are used, regardless of list size.

Limitations:
- Slightly harder to understand without cycle detection intuition.
- Does not identify the cycle’s starting point (requires additional logic).

Trade-offs:
- Extremely space-efficient (O(1)).
- Faster than hashing due to constant-time pointer operations.
- Optimal for most use cases due to minimal resource usage.

Why Optimal?
- Floyd’s algorithm eliminates the need for extra memory, making it suitable for large lists.
- O(N) time with O(1) space is the best possible for cycle detection without modifying the list.
- Simple pointer operations are faster than hash table operations.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Hashing
bool detectCycleHashing(Node* head) {
    // Handle empty list
    if (!head) return false;

    // Set to store visited nodes
    unordered_map<Node*, bool> visited;

    Node* temp = head;
    while (temp) {
        // If node is already visited, cycle exists
        if (visited.find(temp) != visited.end()) {
            return true;
        }
        // Mark node as visited
        visited[temp] = true;
        // Move to next node
        temp = temp->next;
    }

    // Reached nullptr, no cycle
    return false;
}

// Approach 2: Floyd’s Tortoise and Hare
bool detectCycleFloyd(Node* head) {
    // Handle empty list or single node
    if (!head || !head->next) return false;

    // Initialize slow and fast pointers
    Node* slow = head;
    Node* fast = head;

    // Traverse until fast reaches end or pointers meet
    while (fast && fast->next) {
        slow = slow->next;          // Move slow by 1
        fast = fast->next->next;    // Move fast by 2
        if (slow == fast) {         // Cycle detected
            return true;
        }
    }

    // Fast reached nullptr, no cycle
    return false;
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

// Utility function to delete linked list (no cycle handling for simplicity)
void deleteLinkedList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Test Case 1: List with cycle
    int arr1[] = {1, 2, 3, 4, 5};
    Node* head1 = createLinkedList(arr1, 5, 2); // Cycle at node with value 3
    cout << "Test Case 1 (Cycle):\n";
    cout << "Hashing: " << (detectCycleHashing(head1) ? "Cycle detected" : "No cycle") << endl;
    cout << "Floyd: " << (detectCycleFloyd(head1) ? "Cycle detected" : "No cycle") << endl;

    // Test Case 2: List without cycle
    int arr2[] = {1, 2, 3, 4};
    Node* head2 = createLinkedList(arr2, 4);
    cout << "\nTest Case 2 (No Cycle):\n";
    cout << "Hashing: " << (detectCycleHashing(head2) ? "Cycle detected" : "No cycle") << endl;
    cout << "Floyd: " << (detectCycleFloyd(head2) ? "Cycle detected" : "No cycle") << endl;

    // Test Case 3: Empty list
    Node* head3 = nullptr;
    cout << "\nTest Case 3 (Empty List):\n";
    cout << "Hashing: " << (detectCycleHashing(head3) ? "Cycle detected" : "No cycle") << endl;
    cout << "Floyd: " << (detectCycleFloyd(head3) ? "Cycle detected" : "No cycle") << endl;

    // Test Case 4: Single node with self-loop
    Node* head4 = new Node(1);
    head4->next = head4;
    cout << "\nTest Case 4 (Single Node with Self-Loop):\n";
    cout << "Hashing: " << (detectCycleHashing(head4) ? "Cycle detected" : "No cycle") << endl;
    cout << "Floyd: " << (detectCycleFloyd(head4) ? "Cycle detected" : "No cycle") << endl;

    // Clean up (avoid deleting cyclic lists to prevent infinite loops)
    deleteLinkedList(head2);
    delete head4;

    return 0;
}


/*
Thought Process: Proving Floyd’s Tortoise and Hare Algorithm for Cycle Detection

Floyd’s Tortoise and Hare Algorithm (also known as the "cycle detection algorithm") uses two pointers—slow and fast—to detect a cycle in a linked list. The slow pointer moves one step at a time, while the fast pointer moves two steps at a time. The key claim is that if the slow and fast pointers meet (i.e., slow == fast), there is a cycle in the linked list. Below is a deep, intuitive, and analytical thought process to prove why this is true, focusing on the mechanics of the algorithm and the mathematical reasoning behind it.

---

### 1. Problem Context and Intuition
- **What is a cycle?** In a linked list, a cycle exists if a node’s next pointer points to a previously visited node, creating a loop. This means traversal never reaches nullptr and instead repeats a sequence of nodes indefinitely.
- **Why two pointers?** The algorithm uses two pointers moving at different speeds to exploit the repetitive nature of a cycle. If there’s a cycle, the faster pointer should eventually "catch up" to the slower one, like two runners on a circular track.
- **Key Insight**: The fast pointer, moving twice as fast, reduces the relative distance to the slow pointer by one node per iteration inside a cycle. This guarantees a meeting point if a cycle exists.

---

### 2. Mental Model: Visualizing the Linked List
Let’s break the linked list into two parts:
- **Non-cyclic part**: A sequence of nodes from the head to the start of the cycle (if any). Let’s call its length `k` (number of nodes before the cycle begins).
- **Cyclic part**: A loop of nodes that forms the cycle. Let’s call its length `C` (number of nodes in the cycle).

For example:
- List: 1 -> 2 -> 3 -> 4 -> 5 -> 3 (cycle starts at 3).
- Non-cyclic part: 1 -> 2 (k = 2 nodes).
- Cyclic part: 3 -> 4 -> 5 -> 3 (C = 3 nodes).

If there’s no cycle, the list ends at nullptr, and the fast pointer will reach the end before meeting the slow pointer.

---

### 3. Algorithm Mechanics
- **Initialization**: Both slow and fast pointers start at the head of the linked list.
- **Movement**:
  - Slow pointer moves 1 step: `slow = slow->next`.
  - Fast pointer moves 2 steps: `fast = fast->next->next`.
- **Termination Conditions**:
  - If `fast` or `fast->next` becomes nullptr, there’s no cycle (list is linear).
  - If `slow == fast` (pointers point to the same node), a cycle is detected.

The algorithm runs until one of these conditions is met.

---

### 4. Why Do They Meet in a Cycle?
To prove that `slow == fast` implies a cycle, let’s analyze the behavior of the pointers in the presence of a cycle.

#### Step 1: Entering the Cycle
- Assume the list has a cycle, with `k` nodes before the cycle and a cycle of length `C`.
- The slow pointer moves at 1 node per step, and the fast pointer moves at 2 nodes per step.
- After `t` steps:
  - Slow pointer has moved `t` nodes.
  - Fast pointer has moved `2t` nodes.
- After `k` steps (when slow reaches the cycle’s start):
  - Slow is at the cycle’s entry node (position `k`).
  - Fast is at position `2k` (which may be inside the cycle, depending on `k` and `C`).
- Inside the cycle, positions are modulo `C` (since the cycle repeats every `C` nodes). For example, if fast is at position `2k`, its position in the cycle is `2k % C`.

#### Step 2: Relative Speed in the Cycle
- Once both pointers are in the cycle (or when analyzing their relative motion), the fast pointer moves twice as fast as the slow pointer.
- Relative speed = Fast speed - Slow speed = 2 - 1 = 1 node per step.
- This means the fast pointer closes the gap to the slow pointer by 1 node per iteration.

#### Step 3: Distance Reduction
- Suppose at some point, both pointers are in the cycle, and the fast pointer is `d` nodes behind the slow pointer (i.e., fast needs to traverse `d` nodes to reach slow’s position in the cycle).
- After 1 step:
  - Slow moves 1 node forward.
  - Fast moves 2 nodes forward.
  - New distance = `d - 1` (fast gains 1 node relative to slow).
- After `d` steps, the distance becomes `d - d = 0`, meaning fast catches up to slow (they are at the same node).

#### Step 4: Guaranteed Meeting
- The cycle is a closed loop of length `C`, so all positions are modulo `C`.
- The initial distance `d` between slow and fast in the cycle is at most `C - 1` (the largest possible gap in a cycle of length `C`).
- Since the distance decreases by 1 per step, the pointers will meet after at most `C` steps (or fewer, depending on their starting positions in the cycle).
- Thus, if a cycle exists, the fast pointer will always catch the slow pointer.

---

### 5. Mathematical Proof
Let’s formalize the proof with mathematics for clarity.

- **Setup**:
  - `k`: Number of nodes before the cycle.
  - `C`: Length of the cycle.
  - Slow pointer moves 1 node/step, fast pointer moves 2 nodes/step.
- **Positions after `t` steps**:
  - Slow: `t` nodes from the head.
  - Fast: `2t` nodes from the head.
- **In the cycle**:
  - Assume slow enters the cycle after `k` steps (at time `t = k`).
  - Slow’s position in the cycle: `(t - k) % C` (offset from cycle start).
  - Fast’s position in the cycle: `(2t - k) % C`.
- **Meeting condition**:
  - They meet when they are at the same node, i.e., their positions in the cycle are equal:
    `(t - k) % C == (2t - k) % C`.
  - Simplify:
    `(t - k) == (2t - k) (mod C)`.
    `t - k - 2t + k == 0 (mod C)`.
    `-t == 0 (mod C)`.
    `t == 0 (mod C)`.
  - This means they meet when `t` is a multiple of `C` (i.e., after some number of steps `t = m * C` for integer `m`).
- **Conclusion**:
  - The equation shows that the pointers’ positions align periodically within the cycle.
  - Since the relative speed ensures the gap closes by 1 node per step, they will meet after a finite number of steps (at most `C` steps after entering the cycle).

---

### 6. Why Doesn’t It Meet Without a Cycle?
- If there’s no cycle, the list is linear, and traversal eventually reaches nullptr.
- The fast pointer, moving twice as fast, will reach nullptr before the slow pointer (or at the same time for very short lists).
- Since there’s no loop to trap the pointers, `slow == fast` never occurs unless they’re both at the head initially (handled by edge case checks).

---

### 7. Edge Cases and Robustness
- **Empty list (`head == nullptr`)**: No cycle, return false.
- **Single node with self-loop**: Fast and slow meet immediately (after one step), detecting the cycle.
- **Single node without loop**: Fast reaches nullptr, no cycle.
- **Long non-cyclic list**: Fast reaches nullptr, no meeting occurs.
- **Cycle at the start (k = 0)**: Works the same, as pointers start in the cycle.
- The algorithm handles all cases because it only relies on pointer movement and null checks.

---

### 8. Intuition: The Race Analogy
Imagine two runners on a circular track:
- Slow runner moves at 1 unit/second.
- Fast runner moves at 2 units/second.
- If the track is circular (cycle), the fast runner will eventually lap the slow runner, no matter their starting positions.
- If the track is straight (no cycle), the fast runner reaches the end first, and they never meet.

The linked list cycle is like the circular track, and the relative speed ensures the fast pointer overtakes the slow one.

---

### 9. Why Is This Sufficient to Prove a Cycle?
- **If slow == fast**: They meet at the same node, which is only possible in a cycle because:
  - In a linear list, fast would reach nullptr first.
  - In a cycle, the closed loop ensures repeated traversal, allowing fast to catch slow.
- **No false positives**: The only way slow and fast meet is if they’re trapped in a cycle, as a linear list terminates before a meeting.
- **No false negatives**: If a cycle exists, the relative speed guarantees a meeting (proven above).

---

### 10. Time Complexity Insight
- **Non-cyclic case**: Fast pointer reaches nullptr in O(N) steps, where N is the list length.
- **Cyclic case**:
  - Time to reach cycle: O(k) steps.
  - Time to meet in cycle: O(C) steps (since gap closes in at most C steps).
  - Total: O(k + C) = O(N), where N is the total number of nodes.
- The algorithm is linear because the meeting occurs soon after entering the cycle.

---

### Conclusion
Floyd’s algorithm proves a cycle exists when `slow == fast` because:
1. In a cycle, the fast pointer’s double speed ensures it closes the gap to the slow pointer by 1 node per step.
2. The cyclic structure guarantees they meet after a finite number of steps (at most the cycle length).
3. In a non-cyclic list, fast reaches nullptr, preventing a meeting.
4. Mathematical analysis confirms their positions align periodically in a cycle, and the relative speed ensures convergence.

This thought process combines intuition (runners on a track), mechanics (pointer movements), and mathematics (modulo alignment) to rigorously prove the algorithm’s correctness.

*/