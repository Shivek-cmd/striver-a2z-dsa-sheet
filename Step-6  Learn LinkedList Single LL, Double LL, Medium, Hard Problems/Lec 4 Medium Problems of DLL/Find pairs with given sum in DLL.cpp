/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Find all pairs with given sum in a doubly linked list
Given the head of a doubly linked list and an integer target sum, find all pairs of nodes in the 
linked list whose values sum to the target sum. Return the pairs as a list of arrays, where each 
array contains the values of the two nodes forming the pair. The pairs should be returned in any order.

Examples:
Input: head -> 1 <-> 2 <-> 3 <-> 4 <-> 5, target = 7
Output: [[2,5], [3,4]]
Explanation: The pairs (2,5) and (3,4) have sums equal to 7.

Input: head -> 1 <-> 2 <-> 2 <-> 3, target = 4
Output: [[1,3], [2,2]]
Explanation: The pairs (1,3) and (2,2) have sums equal to 4.

Constraints:
- The number of nodes in the list is in the range [1, 10^5].
- -10^9 <= Node.val <= 10^9.
- The list is a valid doubly linked list with proper prev/next pointers.

Edge Cases:
- Single node list (no pairs possible).
- List with all nodes having the same value (check for pairs with identical values).
- No pairs sum to the target.
- Target sum achievable with multiple pairs, including duplicates.
- Negative values in the list.

==============================================================================
Section 2: Solution Approaches
==============================================================================
Observations and Analytical Thought Process:
- The problem requires finding pairs of node values in a doubly linked list that sum to a target.
- Key patterns:
  - Pairs can be anywhere in the list, not necessarily adjacent.
  - Doubly linked list allows traversal in both directions, but order of pairs is irrelevant.
  - Duplicate values (e.g., [2,2] for target=4) must be handled.
- Intuitive insights:
  - A brute force approach can check every pair of nodes, but this is inefficient.
  - Sorting the list enables a two-pointer technique (left and right pointers) to find pairs efficiently.
  - Using a hash map can track values and their frequencies for a single-pass solution.
- Mental roadmap:
  1. Handle edge cases like empty or single-node lists.
  2. Consider sorting the list to use two pointers or use a hash map for unsorted list.
  3. Ensure all pairs are found, including those with identical values.
  4. Return pairs in the required format (vector of vectors).

----------------------------------------
Approach 1: Brute Force (Check All Pairs)
----------------------------------------
Logic:
- Iterate through each node and pair it with every subsequent node to check if their values sum to the target.
- Collect valid pairs in the result vector.

Steps:
1. If head is nullptr or has only one node, return empty result.
2. Use two nested loops:
   - Outer loop: Iterate node1 from head to second-to-last node.
   - Inner loop: Iterate node2 from node1->next to last node.
3. If node1->val + node2->val == target, add {node1->val, node2->val} to result.
4. Return result.

Complexity:
- Time: O(n^2) where n is the number of nodes (nested loops).
- Space: O(1) excluding output (only stores result).
- Justification: Each node is paired with every subsequent node, leading to n*(n-1)/2 comparisons.

Limitations:
- Highly inefficient for large lists due to quadratic time complexity.
- No optimization for duplicate values or sorted properties.
- Redundant comparisons for pairs already checked.

----------------------------------------
Approach 2: Better (Hash Map)
----------------------------------------
Logic:
- Use a hash map to store the frequency of each value encountered.
- For each node, check if (target - node->val) exists in the map to form a pair.
- Handle duplicates carefully to include all valid pairs.

Steps:
1. If head is nullptr, return empty result.
2. Initialize an unordered_map to store value frequencies.
3. Traverse the list:
   - For each node, check if target - node->val exists in the map.
   - If yes, add pairs based on the frequency of the complement.
   - Increment the node’s value frequency in the map.
4. Return result.

Complexity:
- Time: O(n) for single pass through the list.
- Space: O(n) for the hash map storing up to n values.
- Justification: Hash map operations (insert, lookup) are O(1) on average; single traversal is O(n).

Advantages:
- Much faster than brute force for large lists.
- Works with unsorted lists, avoiding sorting overhead.
- Handles duplicates naturally via frequency counting.

Limitations:
- Extra space for the hash map.
- May need careful handling for negative values or large integers due to constraints.

----------------------------------------
Approach 3: Optimal (Sort and Two-Pointer)
----------------------------------------
Logic:
- Sort the doubly linked list using merge sort to enable a two-pointer approach.
- Use two pointers (left at head, right at tail) to find pairs summing to the target.
- Adjust pointers based on the sum (move left if sum is too small, right if too large).

Steps:
1. If head is nullptr, return empty result.
2. Sort the list using merge sort (O(n log n)).
3. Initialize left at head and right at tail.
4. While left is before right:
   - If left->val + right->val == target, add pair and move both pointers.
   - If sum < target, move left forward.
   - If sum > target, move right backward.
5. Return result.

Complexity:
- Time: O(n log n) for sorting + O(n) for two-pointer traversal = O(n log n).
- Space: O(log n) for merge sort recursion stack; O(1) for two-pointer part.
- Justification: Merge sort is O(n log n); two-pointer traversal is O(n) as each pointer moves at most n times.

Why Optimal:
- Balances time and space efficiency compared to brute force (O(n^2)) and hash map (O(n) space).
- Sorting enables linear pair-finding after initial sort.
- Handles duplicates by moving pointers appropriately.

Trade-offs:
- Sorting modifies the list structure (can copy list if preservation is needed).
- Slightly higher time complexity than hash map due to sorting.
- Recursive sorting may use stack space for very large lists.

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

// Approach 1: Brute Force (Check All Pairs)
vector<vector<int>> findPairsWithSumBrute(Node* head, int target) {
    vector<vector<int>> result;
    if (!head || !head->next) return result; // Handle empty or single-node list

    // Iterate through each pair of nodes
    Node* node1 = head;
    while (node1 && node1->next) {
        Node* node2 = node1->next;
        while (node2) {
            if (node1->val + node2->val == target) {
                result.push_back({node1->val, node2->val}); // Add valid pair
            }
            node2 = node2->next;
        }
        node1 = node1->next;
    }

    return result;
}

// Helper function to find the middle of the list for merge sort
Node* findMiddle(Node* head) {
    if (!head || !head->next) return head;
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Helper function to merge two sorted doubly linked lists
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node dummy(0);
    Node* curr = &dummy;

    while (left && right) {
        if (left->val <= right->val) {
            curr->next = left;
            left->prev = curr;
            left = left->next;
        } else {
            curr->next = right;
            right->prev = curr;
            right = right->next;
        }
        curr = curr->next;
    }

    if (left) {
        curr->next = left;
        left->prev = curr;
    }
    if (right) {
        curr->next = right;
        right->prev = curr;
    }

    Node* result = dummy.next;
    if (result) result->prev = nullptr;
    return result;
}

// Helper function to sort the doubly linked list using merge sort
Node* sortList(Node* head) {
    if (!head || !head->next) return head;

    // Find middle to split the list
    Node* mid = findMiddle(head);
    Node* right = mid->next;
    mid->next = nullptr;
    if (right) right->prev = nullptr;

    // Recursively sort left and right halves
    Node* left = sortList(head);
    right = sortList(right);

    // Merge the sorted halves
    return merge(left, right);
}

// Approach 2: Better (Hash Map)
vector<vector<int>> findPairsWithSumHash(Node* head, int target) {
    vector<vector<int>> result;
    if (!head) return result; // Handle empty list

    unordered_map<int, int> freq; // Map to store value frequencies
    Node* curr = head;

    while (curr) {
        int complement = target - curr->val;
        if (freq.find(complement) != freq.end()) {
            // Add pairs for each occurrence of complement
            for (int i = 0; i < freq[complement]; ++i) {
                result.push_back({min(complement, curr->val), max(complement, curr->val)});
            }
        }
        freq[curr->val]++; // Increment frequency
        curr = curr->next;
    }

    // Sort pairs for consistent output
    sort(result.begin(), result.end());
    return result;
}

// Approach 3: Optimal (Sort and Two-Pointer)
vector<vector<int>> findPairsWithSumOptimal(Node* head, int target) {
    vector<vector<int>> result;
    if (!head) return result; // Handle empty list

    // Sort the doubly linked list
    head = sortList(head);

    // Find tail
    Node* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    // Use two pointers to find pairs
    Node* left = head;
    while (left != tail && left->prev != tail) {
        int sum = left->val + tail->val;
        if (sum == target) {
            result.push_back({left->val, tail->val}); // Add valid pair
            left = left->next;
            tail = tail->prev;
        } else if (sum < target) {
            left = left->next; // Need larger sum
        } else {
            tail = tail->prev; // Need smaller sum
        }
    }

    return result;
}

int main() {
    // Create a sample doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->prev = head;
    head->next->next = new Node(3);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(4);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->prev = head->next->next->next;

    int target = 7;

    // Test Optimal Approach
    vector<vector<int>> result = findPairsWithSumOptimal(head, target);

    // Print the result
    for (const auto& pair : result) {
        cout << "[" << pair[0] << "," << pair[1] << "] ";
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