#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
/*
    Problem:
    --------
    Given the head of a singly linked list of integers, determine the middle node.
    If the number of nodes is even, return the second middle node.

    Examples:
    ---------
    Input: 1 -> 2 -> 3 -> 4 -> 5
    Output: 3

    Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    Output: 4

    Constraints:
    ------------
    - Number of nodes: [1, 100]
    - Node value: [1, 100]

    Edge Cases:
    -----------
    - Single node list => return that node
    - Even number of nodes => return the second middle
    - Empty list => return nullptr
*/

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================

/*
    Approach 1: Brute Force
    -----------------------
    a. Traverse the list to count the total number of nodes (n).
    b. Traverse again to the (n/2)th node (return second middle for even n).

    Pseudocode:
    -----------
    1. count = 0
    2. traverse to count nodes
    3. mid = count / 2
    4. traverse again to mid-th node
    5. return that node

    Time Complexity: O(N) + O(N) = O(N)
    Space Complexity: O(1)
    Trade-offs: Extra traversal; simple but inefficient for large lists.
*/

/*
    Approach 2: Optimal (Two Pointer / Tortoise-Hare)
    --------------------------------------------------
    a. Use two pointers: slow moves one step, fast moves two steps.
    b. When fast reaches the end, slow is at the middle.
    c. Works for both odd and even-length lists; returns second middle automatically.

    Pseudocode:
    -----------
    1. slow = head, fast = head
    2. while (fast != NULL && fast->next != NULL)
        - slow = slow->next
        - fast = fast->next->next
    3. return slow

    Time Complexity: O(N)
    Space Complexity: O(1)
    Advantage: One-pass, efficient, elegant.
*/

/*
==============================================================================
Thought Process: Tortoise-Hare (Two Pointer) Method
==============================================================================

Observation:
------------
- We want to find the **middle node** of a singly linked list in just **one pass**.
- Using two pointers (slow and fast) allows us to simulate progress at different speeds:
    - Slow pointer moves one step at a time.
    - Fast pointer moves two steps at a time.

Key Insight:
------------
- When the fast pointer reaches the end of the list:
    - The slow pointer will have reached **halfway**.
    - This is due to the fast pointer covering twice the distance of the slow pointer.
- In the case of an **even-length list**, fast will reach the end (`nullptr`) after an even number of steps.
    - The slow pointer will be at the **second middle** node — as required by the problem.

Step-by-Step Intuition:
-----------------------
1. Initialize two pointers:
    - `slow = head`
    - `fast = head`

2. Traverse the list:
    - Move `slow` one node at a time.
    - Move `fast` two nodes at a time.

3. Terminate when:
    - `fast == nullptr` (end reached) or
    - `fast->next == nullptr` (only one step remaining)

4. At this point, `slow` will be pointing to the **middle node**.

Why This Works:
---------------
- For a list of length `n`:
    - Fast covers 2 steps for every 1 step of slow.
    - So when fast is at position `n`, slow is at `n/2`.

    Example:
    --------
    List: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    Step 1: slow = 2, fast = 3
    Step 2: slow = 3, fast = 5
    Step 3: slow = 4, fast = nullptr → stop
    Result: slow is at 4 (the second middle node)

Time and Space Complexity:
--------------------------
- Time: O(N) — visits each node once.
- Space: O(1) — constant space, no extra storage.

Conclusion:
-----------
- The two-pointer (tortoise-hare) method is the most elegant and efficient way
  to find the middle of a linked list, handling both odd and even cases naturally.
*/


// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Definition for singly-linked list
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

// Brute Force Approach: Two Traversals
Node* findMiddleBrute(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    int count = 0;
    Node* curr = head;

    // Count the number of nodes
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }

    // Move to (count / 2)-th node
    int mid = count / 2;
    curr = head;
    while (mid--) {
        curr = curr->next;
    }

    return curr; // This will be the second middle if even count
}

// Optimal Approach: Tortoise-Hare (Slow & Fast pointers)
Node* findMiddleOptimal(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    Node* slow = head;
    Node* fast = head;

    // Move fast by 2 and slow by 1
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow; // Second middle node if list length is even
}

// Utility function to print linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Construct sample linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);

    cout << "Input Linked List: ";
    printList(head);

    // Brute Force Output
    Node* middleBrute = findMiddleBrute(head);
    cout << "Middle Node (Brute Force): ";
    if (middleBrute) cout << middleBrute->val << endl;

    // Optimal Output
    Node* middleOptimal = findMiddleOptimal(head);
    cout << "Middle Node (Optimal): ";
    if (middleOptimal) cout << middleOptimal->val << endl;

    // Memory Cleanup
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
