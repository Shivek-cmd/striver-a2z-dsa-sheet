#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
Given a linked list containing nodes with values 0, 1, or 2, sort the list in non-decreasing order (all 0's first, then 1's, then 2's).
The sorting must be done by modifying the links between nodes, not by changing node values.

Example:
Input: 1 -> 0 -> 2 -> 1 -> 0 -> 2
Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2

Constraints:
- The number of nodes in the list is in the range [0, 100].
- Node values are only 0, 1, or 2.

Edge Cases:
- Empty list (head is nullptr).
- List with all nodes of the same value (e.g., all 0's).
- List with only two distinct values (e.g., 0's and 1's).
*/

// Definition for singly-linked list
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

/*
// ==============================================================================
   Approach 1: Brute Force Approach:
// ==============================================================================

1. Traverse the linked list and store all node values in a vector.
2. Sort the vector in non-decreasing order.
3. Rebuild the linked list by assigning the sorted values back to the nodes.

Time Complexity: O(N log N) due to sorting.
Space Complexity: O(N) for storing node values in a vector.

Limitations:
- Modifies node values instead of links, which may not be allowed in some constraints.
- Uses extra space proportional to the number of nodes.




// ==============================================================================
   Approach 2: Better Approach (Counting Sort):
// ==============================================================================


1. Count the occurrences of 0's, 1's, and 2's in the list.
2. Overwrite the node values in the original list based on counts (all 0's first, then 1's, then 2's).

Time Complexity: O(N) for two passes through the list.
Space Complexity: O(1) as only counts are stored.

Limitations:
- Still modifies node values instead of links.
- Requires two passes over the list.


// ==============================================================================
   Approach 3: Optimal Approach (Partitioning):
// ==============================================================================


1. Create three dummy nodes to act as heads for three sublists: 0's, 1's, and 2's.
2. Traverse the original list and partition nodes into these sublists based on their values.
3. Connect the sublists in order (0's -> 1's -> 2's).
4. Update the head of the original list to point to the head of the 0's sublist.

Time Complexity: O(N) for a single pass through the list.
Space Complexity: O(1) as only dummy nodes are used.

Advantages:
- Modifies links instead of node values.
- Efficient single-pass partitioning.
*/

void sortLinkedListBrute(Node* &head) {
    if (!head) return; // Handle empty list

    vector<int> values;
    Node* current = head;

    // Step 1: Extract values into a vector
    while (current) {
        values.push_back(current->val);
        current = current->next;
    }

    // Step 2: Sort the vector
    sort(values.begin(), values.end());

    // Step 3: Reassign values to nodes
    current = head;
    for (int val : values) {
        current->val = val;
        current = current->next;
    }
}

void sortLinkedListBetter(Node* &head) {
    if (!head) return;

    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    Node* curr = head;

    // Step 1: Count occurrences
    while (curr) {
        if (curr->val == 0) cnt0++;
        else if (curr->val == 1) cnt1++;
        else cnt2++;
        curr = curr->next;
    }

    // Step 2: Overwrite node values
    curr = head;
    while (curr) {
        if (cnt0 > 0) {
            curr->val = 0;
            cnt0--;
        } else if (cnt1 > 0) {
            curr->val = 1;
            cnt1--;
        } else {
            curr->val = 2;
            cnt2--;
        }
        curr = curr->next;
    }
}

Node* sortLinkedListOptimal(Node* &head) {
    if (!head) return nullptr;

    // Dummy nodes for sublists
    Node* zeroHead = new Node(-1);
    Node* oneHead = new Node(-1);
    Node* twoHead = new Node(-1);

    // Tail pointers for sublists
    Node* zeroTail = zeroHead;
    Node* oneTail = oneHead;
    Node* twoTail = twoHead;

    Node* curr = head;

    // Partition nodes into sublists
    while (curr) {
        if (curr->val == 0) {
            zeroTail->next = curr;
            zeroTail = zeroTail->next;
        } else if (curr->val == 1) {
            oneTail->next = curr;
            oneTail = oneTail->next;
        } else {
            twoTail->next = curr;
            twoTail = twoTail->next;
        }
        curr = curr->next;
    }

    // Connect sublists
    zeroTail->next = oneHead->next ? oneHead->next : twoHead->next;
    oneTail->next = twoHead->next;
    twoTail->next = nullptr;

    // Update head and clean up dummy nodes
    Node* sortedHead = zeroHead->next;
    delete zeroHead;
    delete oneHead;
    delete twoHead;

    return sortedHead;
}

// Utility function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Sample input
    Node* head = new Node(1);
    head->next = new Node(0);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(0);
    head->next->next->next->next->next = new Node(2);

    cout << "Original Linked List: ";
    printList(head);

    // Test Brute Force Approach
    Node* head1 = new Node(1);
    head1->next = new Node(0);
    head1->next->next = new Node(2);
    head1->next->next->next = new Node(1);
    head1->next->next->next->next = new Node(0);
    head1->next->next->next->next->next = new Node(2);
    sortLinkedListBrute(head1);
    cout << "Brute Force Sorted List: ";
    printList(head1);

    // Test Better Approach
    Node* head2 = new Node(1);
    head2->next = new Node(0);
    head2->next->next = new Node(2);
    head2->next->next->next = new Node(1);
    head2->next->next->next->next = new Node(0);
    head2->next->next->next->next->next = new Node(2);
    sortLinkedListBetter(head2);
    cout << "Better Sorted List: ";
    printList(head2);

    // Test Optimal Approach
    Node* head3 = new Node(1);
    head3->next = new Node(0);
    head3->next->next = new Node(2);
    head3->next->next->next = new Node(1);
    head3->next->next->next->next = new Node(0);
    head3->next->next->next->next->next = new Node(2);
    head3 = sortLinkedListOptimal(head3);
    cout << "Optimal Sorted List: ";
    printList(head3);

    return 0;
}