#include <bits/stdc++.h>
using namespace std;

// Definition for doubly-linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int x) : data(x), prev(nullptr), next(nullptr) {}
};

// Definition for singly-linked list
struct SNode {
    int data;
    SNode* next;
    SNode(int x) : data(x), next(nullptr) {}
};

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem 1: Reverse a doubly linked list of size N consisting of positive integers.
Return the head of the reversed list.

Example (Doubly Linked List):
Input: 1<->2<->3<->4
Output: 4<->3<->2<->1

Input: 1
Output: 1

Problem 2: Reverse a singly linked list of size N consisting of positive integers.
Return the head of the reversed list.

Example (Singly Linked List):
Input: 1->2->3->4
Output: 4->3->2->1

Input: 1
Output: 1

Constraints:
- 1 <= N <= 10^5
- 1 <= Node.data <= 10^9
- The lists are valid (no cycles, proper pointers).

Edge Cases (Both Lists):
- Empty list (head = nullptr)
- Single node (N = 1)
- Two nodes (N = 2)
- Large list (N = 10^5)

Input Format:
- Head pointer to a doubly or singly linked list.

Output Format:
- Head pointer to the reversed doubly or singly linked list.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

Observations and Thought Process (Doubly Linked List):
1. **Key Pattern**: A doubly linked list has both prev and next pointers, allowing traversal in both directions. Reversing it involves swapping prev and next pointers for each node while maintaining connectivity.
2. **Intuitive Insight**: The head becomes the tail, and the tail becomes the head. Adjust pointers iteratively or recursively.
3. **Edge Cases**: Empty or single-node lists require no reversal. Two-node lists test pointer swaps.
4. **Mental Roadmap**:
   - Traverse the list, swapping prev and next pointers.
   - Track the new head (last node of the original list).
   - Use temporary storage to avoid losing pointers.
   - Handle edge cases to avoid null pointer dereferences.

Observations and Thought Process (Singly Linked List):
1. **Key Pattern**: A singly linked list has only next pointers, so reversal involves redirecting next pointers to point to the previous node.
2. **Intuitive Insight**: The head becomes the tail, and the last node becomes the head. Reverse the direction of all next pointers.
3. **Edge Cases**: Similar to doubly linked list (empty, single node, two nodes).
4. **Mental Roadmap**:
   - Use three pointers (prev, curr, next) to reverse next pointers iteratively.
   - Track the new head (last node of the original list).
   - Handle edge cases explicitly.

---


==============================================================================
Approach 1: Brute Force (Using a Stack) - Doubly Linked List
==============================================================================


Logic:
- Store all nodes in a stack to reverse the order.
- Rebuild the list by popping nodes and reassigning prev/next pointers.
Steps:
1. Traverse the list, pushing each node onto a stack.
2. Pop nodes to create a new list, setting next/prev pointers in reverse order.
3. Return the new head (last node popped).
Time Complexity: O(N) for traversal + O(N) for rebuilding = O(N)
Space Complexity: O(N) for the stack
Limitations:
- Requires extra space proportional to list size.
- Two passes through the list.



==============================================================================
Approach 1: Brute Force (Using a Stack) - Singly Linked List
==============================================================================

Logic:
- Store nodes in a stack and rebuild by popping.
Steps:
1. Push all nodes onto a stack.
2. Pop nodes, setting next pointers in reverse order.
3. Return the new head.
Time Complexity: O(N)
Space Complexity: O(N) for the stack
Limitations:
- Extra space and two passes, inefficient.

---



==============================================================================
Approach 2: Better (Recursive Reversal) - Doubly Linked List
==============================================================================


Logic:
- Use recursion to reverse the list by processing nodes from the end to the start.
Steps:
1. Base case: If head is nullptr or single node, return head.
2. Recursively reverse the sublist starting from head->next.
3. Update head's prev/next pointers and connect to the reversed sublist.
4. Return the new head.
Time Complexity: O(N) for recursive calls
Space Complexity: O(N) for recursive call stack
Limitations:
- Stack overflow for very large lists.
- Less intuitive than iterative.



==============================================================================
Approach 2: Better (Recursive Reversal) - Singly Linked List
==============================================================================


Logic:
- Recursively reverse the sublist and adjust next pointers.
Steps:
1. Base case: If head is nullptr or single node, return head.
2. Recursively reverse the sublist starting from head->next.
3. Set head->next->next to head and head->next to nullptr.
4. Return the new head.
Time Complexity: O(N)
Space Complexity: O(N) for recursive call stack
Limitations:
- Stack overflow risk for large lists.



==============================================================================
Approach 2: Better (Recursive Reversal)
==============================================================================


Logic:
- Recursively reverse the sublist starting from the next node and adjust the current node's next pointer to point to the previous node.
Steps:
1. Base case: If head is nullptr or single node, return head.
2. Recursively reverse the sublist starting from head->next, getting the new head.
3. Set head->next->next to head (make the next node point back to current).
4. Set head->next to nullptr (current node becomes the tail).
5. Return the new head.
Time Complexity: O(N) for recursive calls
Space Complexity: O(N) for recursive call stack
Limitations:
- Risk of stack overflow for very large lists due to recursion.
- Less intuitive than iterative for some developers.
- Still requires O(N) time but with higher space complexity than iterative.


---

==============================================================================
Approach 3: Optimal (Iterative In-Place Reversal) - Doubly Linked List
==============================================================================



Logic:
- Traverse the list once, swapping prev and next pointers in-place.
Steps:
1. Initialize current = head, temp = nullptr.
2. While current != nullptr:
   a. Store current->prev in temp.
   b. Swap current->prev with current->next.
   c. Set current->next to temp.
   d. Move current to current->prev (original next).
3. Set head to temp->prev (new head).
4. Return head.
Time Complexity: O(N) for single traversal
Space Complexity: O(1)
Why Optimal?
- Single pass, no extra data structures, minimal memory.
Limitations:
- Careful pointer manipulation required.




==============================================================================
Approach 3: Optimal (Iterative In-Place Reversal) - Singly Linked List
==============================================================================



Logic:
- Use three pointers to reverse next pointers in-place.
Steps:
1. Initialize prev = nullptr, curr = head.
2. While curr != nullptr:
   a. Store curr->next in next.
   b. Set curr->next to prev.
   c. Move prev to curr, curr to next.
3. Return prev (new head).
Time Complexity: O(N) for single traversal
Space Complexity: O(1)
Why Optimal?
- Single pass, no extra space, efficient.
Limitations:
- Requires careful pointer updates.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Function to print the doubly linked list (forward traversal)
void printLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << "<->";
        temp = temp->next;
    }
    cout << endl;
}

// Function to print the singly linked list (forward traversal)
void printSLL(SNode* head) {
    SNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << "->";
        temp = temp->next;
    }
    cout << endl;
}

// Approach 1: Brute Force (Using Stack) - Doubly Linked List
Node* reverseDLLBrute(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    stack<Node*> nodeStack;
    Node* curr = head;
    while (curr != nullptr) {
        nodeStack.push(curr);
        curr = curr->next;
    }
    head = nodeStack.top();
    nodeStack.pop();
    curr = head;
    curr->prev = nullptr;
    while (!nodeStack.empty()) {
        Node* nextNode = nodeStack.top();
        nodeStack.pop();
        curr->next = nextNode;
        nextNode->prev = curr;
        curr = nextNode;
    }
    curr->next = nullptr;
    return head;
}

// Approach 2: Better (Recursive Reversal) - Doubly Linked List
Node* reverseDLLRecursive(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node* newHead = reverseDLLRecursive(head->next);
    head->next->next = head;
    head->next->prev = nullptr;
    head->prev = head->next;
    head->next = nullptr;
    return newHead;
}

// Approach 2: Better (Recursive Reversal) - Singly Linked List
SNode* reverseSLLRecursive(SNode* head) {
    // Base case: empty or single node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Recursively reverse the rest of the list
    SNode* newHead = reverseSLLRecursive(head->next);

    // Adjust pointers: make next node point back to current
    SNode*front=head->next;
    front->next = head;
    head->next = nullptr; // Current node becomes tail

    // Return the new head
    return newHead;
}


// Approach 3: Optimal (Iterative In-Place Reversal) - Doubly Linked List
Node* reverseDLLOptimal(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node* temp = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    head = temp->prev;
    return head;
}

// Approach 3: Optimal (Iterative In-Place Reversal) - Singly Linked List
SNode* reverseSLLOptimal(SNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    SNode* temp = nullptr;
    SNode* curr = head;
    SNode* front = nullptr;
    while (curr != nullptr) {
        front = curr->next;    // Store next node
        curr->next = temp;    // Reverse the link
        temp = curr;          // Move prev to current
        curr = front;          // Move to next node
    }
    return temp;
}

int main() {
    // Sample array to initialize the lists
    vector<int> arr = {1, 2, 3, 4};

    // === Doubly Linked List ===
    // Creating a doubly linked list
    Node* head = new Node(arr[0]);
    Node* node1 = head;
    Node* node2 = new Node(arr[1]);
    Node* node3 = new Node(arr[2]);
    Node* node4 = new Node(arr[3]);
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;

    cout << "Original Doubly Linked List: ";
    printLL(head);

    // Test Brute Force Approach
    Node* headBrute = reverseDLLBrute(head);
    cout << "Reversed Doubly Linked List (Brute Force): ";
    printLL(headBrute);

    // Recreate doubly linked list for recursive approach
    head = new Node(arr[0]);
    node1 = head;
    node2 = new Node(arr[1]);
    node3 = new Node(arr[2]);
    node4 = new Node(arr[3]);
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;

    // Test Recursive Approach
    Node* headRecursive = reverseDLLRecursive(head);
    cout << "Reversed Doubly Linked List (Recursive): ";
    printLL(headRecursive);

    // Recreate doubly linked list for optimal approach
    head = new Node(arr[0]);
    node1 = head;
    node2 = new Node(arr[1]);
    node3 = new Node(arr[2]);
    node4 = new Node(arr[3]);
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;

    // Test Optimal Approach
    Node* headOptimal = reverseDLLOptimal(head);
    cout << "Reversed Doubly Linked List (Optimal): ";
    printLL(headOptimal);

    // === Singly Linked List ===
    // Creating a singly linked list
    SNode* shead = new SNode(arr[0]);
    SNode* snode1 = shead;
    SNode* snode2 = new SNode(arr[1]);
    SNode* snode3 = new SNode(arr[2]);
    SNode* snode4 = new SNode(arr[3]);
    snode1->next = snode2;
    snode2->next = snode3;
    snode3->next = snode4;

    cout << "\nOriginal Singly Linked List: ";
    printSLL(shead);

    // Test Optimal Approach for Singly Linked List
    SNode* sheadOptimal = reverseSLLOptimal(shead);
    cout << "Reversed Singly Linked List (Optimal): ";
    printSLL(sheadOptimal);


    // Clean up memory for doubly linked list approaches
    while (headOptimal != nullptr) {
        Node* temp = headOptimal;
        headOptimal = headOptimal->next;
        delete temp;
    }
    while (headRecursive != nullptr) {
        Node* temp = headRecursive;
        headRecursive = headRecursive->next;
        delete temp;
    }
    while (headBrute != nullptr) {
        Node* temp = headBrute;
        headBrute = headBrute->next;
        delete temp;
    }

    // Clean up memory for singly linked list
    while (sheadOptimal != nullptr) {
        SNode* temp = sheadOptimal;
        sheadOptimal = sheadOptimal->next;
        delete temp;
    }

    return 0;
}