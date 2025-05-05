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
// Problem: Given a linked list, sort its nodes based on the data value in them.
// Return the head of the sorted linked list.
//
// Examples:
//   Example 1:
//     Input: Linked List: 3 -> 4 -> 2 -> 1 -> 5
//     Output: Sorted List: 1 -> 2 -> 3 -> 4 -> 5
//     Explanation: The input linked list when sorted from [3, 4, 2, 1, 5] results
//     in a linked list with values: [1, 2, 3, 4, 5].
//
//   Example 2:
//     Input: List: 40 -> 20 -> 60 -> 10 -> 50 -> 30
//     Output: Sorted List: 10 -> 20 -> 30 -> 40 -> 50 -> 60
//     Explanation: The input linked list when sorted from [40, 20, 60, 10, 50, 30]
//     results in a linked list with values: [10, 20, 30, 40, 50, 60].
//
// Constraints:
//   - Number of nodes: [0, 10^4]
//   - Node values: [-10^5, 10^5]
//   - Linked list is singly linked and non-circular.
//
// Edge Cases:
//   - Empty list (return nullptr).
//   - Single node (already sorted).
//   - Two nodes (swap if needed).
//   - Negative values (handle in sorting).

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================
// Observations and Thought Process:
// 1. **Key Pattern**: Sorting a linked list requires rearranging nodes or their values
//    in ascending order. Unlike arrays, linked lists lack random access, making
//    algorithms like QuickSort less efficient due to traversal costs.
// 2. **Intuitive Insight**: We can either copy values to an array for sorting (easy but
//    uses extra space) or manipulate the list structure directly using a divide-and-conquer
//    approach like MergeSort, which is well-suited for linked lists.
// 3. **Edge Cases**: Empty list (return nullptr), single node (return as is), and
//    handling negative values or duplicates in sorting.
// 4. **Mental Roadmap**:
//    - Brute Force: Extract values to a vector, sort, and reassign to list.
//    - Optimal: Use MergeSort by splitting the list into halves, sorting recursively,
//      and merging sorted sublists.




// ==============================================================================
// Approach 1: Brute Force (Vector-Based Sorting)
// ==============================================================================

// Logic:
//   - Traverse the linked list to collect all node values into a vector.
//   - Sort the vector using a standard sorting algorithm (e.g., std::sort).
//   - Traverse the list again to update node values with sorted vector elements.
// Steps:
//   1. If list is empty, return nullptr.
//   2. Create a vector to store node values.
//   3. Traverse list, push each value to vector.
//   4. Sort the vector in ascending order.
//   5. Traverse list again, assign sorted values from vector to nodes.
//   6. Return head.
// Complexity:
//   - Time: O(n) for traversal + O(n log n) for sorting + O(n) for reassignment = O(n log n).
//   - Space: O(n) for the vector storing node values.
// Limitations:
//   - Uses extra space (O(n)) for the vector.
//   - Does not manipulate list structure, so less "linked list-like" solution.
//   - Inefficient for very large lists due to extra memory allocation.



// ==============================================================================
// Approach 2: Optimal (MergeSort)
// ==============================================================================

// Logic:
//   - Use MergeSort, which is ideal for linked lists due to its divide-and-conquer nature
//     and sequential access pattern.
//   - Split the list into two halves using the fast-slow pointer technique to find the middle.
//   - Recursively sort each half.
//   - Merge the two sorted halves into a single sorted list.
// Steps:
//   1. If list is empty or has one node, return head (base case).
//   2. Find the middle node using fast-slow pointers.
//   3. Split the list into two halves by setting middle->next to nullptr.
//   4. Recursively sort the left and right halves.
//   5. Merge the sorted halves using a helper function.
//   6. Return the head of the merged list.
// Complexity:
//   - Time: O(n log n). Splitting takes O(log n) levels, and merging at each level takes O(n).
//   - Space: O(log n) for the recursive call stack (no extra data structure needed).
// Why Optimal:
//   - Matches the time complexity of the best sorting algorithms (O(n log n)).
//   - Uses minimal extra space (O(log n) for recursion, no O(n) storage).
//   - Leverages linked list structure by manipulating pointers, avoiding random access.
// Trade-offs:
//   - Recursive approach increases stack space for very deep recursion.
//   - Slightly more complex to implement due to pointer management.

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Helper function to find the middle node (for MergeSort)
Node* findMiddle(Node* head) {
    // Handle empty or single-node list
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Use fast-slow pointers to find middle
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Helper function to merge two sorted linked lists
Node* mergeTwoSortedLinkedLists(Node* list1, Node* list2) {
    // Create dummy node for merged list
    Node* dummyNode = new Node(-1);
    Node* temp = dummyNode;

    // Merge lists by comparing values
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            temp->next = list1;
            list1 = list1->next;
        } else {
            temp->next = list2;
            list2 = list2->next;
        }
        temp = temp->next;
    }

    // Attach remaining nodes
    if (list1) {
        temp->next = list1;
    } else {
        temp->next = list2;
    }

    // Return head of merged list
    Node* result = dummyNode->next;
    delete dummyNode; // Clean up dummy node
    return result;
}

// Brute Force Approach (Vector-Based Sorting)
Node* sortListBrute(Node* head) {
    // Handle empty list
    if (head == nullptr) {
        return nullptr;
    }

    // Collect values into vector
    vector<int> values;
    Node* temp = head;
    while (temp) {
        values.push_back(temp->val);
        temp = temp->next;
    }

    // Sort the vector
    sort(values.begin(), values.end());

    // Reassign sorted values to list
    temp = head;
    for (int i = 0; i < values.size() && temp; ++i) {
        temp->val = values[i];
        temp = temp->next;
    }

    return head;
}

// Optimal Approach (MergeSort)
Node* sortListOptimal(Node* head) {
    // Base case: empty or single node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Find middle node
    Node* middle = findMiddle(head);
    Node* right = middle->next;
    middle->next = nullptr; // Split list into two halves
    Node* left = head;

    // Recursively sort both halves
    left = sortListOptimal(left);
    right = sortListOptimal(right);

    // Merge sorted halves
    return mergeTwoSortedLinkedLists(left, right);
}

// Main function to test the solution
int main() {
    // Create sample linked list: 3->4->2->1->5
    Node* head = new Node(3);
    head->next = new Node(4);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(5);

    // Test Brute Force
    Node* result = sortListBrute(head);

    // Print the sorted linked list
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
    head = new Node(3);
    head->next = new Node(4);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(5);

    // Test Optimal
    result = sortListOptimal(head);

    // Print the sorted linked list
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
