#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
// Problem: Check if a singly linked list is a palindrome.
// A linked list is a palindrome if its sequence of values reads the same forwards and backwards.
// Input: Head of a singly linked list (Node* head).
// Output: Boolean (true if palindrome, false otherwise).
// Examples:
//   1. Input: 1->2->3->2->1  Output: true
//   2. Input: 1->2->3->3->2->1  Output: true
//   3. Input: 1->2->3->2->3  Output: false
// Constraints:
//   - Number of nodes: 0 <= n <= 10^5
//   - Node values: -10^4 <= val <= 10^4
// Edge Cases:
//   - Empty list (return true)
//   - Single node (return true)
//   - Two nodes with different values (return false)

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================
// Approach 1: Brute Force (Using Vector)
// Logic:
//   - Traverse the linked list and store all node values in a vector.
//   - Use two pointers (one from start, one from end) to compare vector elements.
//   - If any pair mismatches, the list is not a palindrome.
// Steps:
//   1. Initialize an empty vector.
//   2. Traverse the list, pushing each node's value into the vector.
//   3. Set two pointers: i (start) and j (end of vector).
//   4. While i <= j, compare v[i] and v[j]. If unequal, return false.
//   5. If loop completes, return true.
// Time Complexity: O(n) for traversal + O(n) for comparison = O(n)
// Space Complexity: O(n) for the vector
// Limitations:
//   - Requires extra space proportional to the list size.
//   - Simple but not space-efficient.

// Approach 2: Optimal (Reverse Second Half)
// Logic:
//   - Find the middle of the list using the Tortoise and Hare algorithm.
//   - Reverse the second half of the list starting from the node after the middle.
//   - Compare the first half (from head) with the reversed second half.
//   - If all values match, the list is a palindrome.
//   - Restore the list by reversing the second half back (optional for this problem).
// Steps:
//   1. Handle edge cases: empty list or single node (return true).
//   2. Use slow and fast pointers to find the middle (slow points to middle node).
//   3. Reverse the second half starting from slow->next.
//   4. Compare first half (head) and second half (reversed head) node by node.
//   5. If any values differ, return false; else return true.
// Time Complexity: 
//   - Finding middle: O(n/2) = O(n)
//   - Reversing half: O(n/2) = O(n)
//   - Comparing halves: O(n/2) = O(n)
//   - Total: O(n)
// Space Complexity: O(1) as only a few pointers are used
// Why Optimal:
//   - Eliminates the need for extra space (unlike vector in brute force).
//   - Maintains same time complexity but with constant space.
// Trade-offs:
//   - Modifies the list temporarily (can be restored if needed).
//   - Slightly more complex due to list reversal and pointer management.

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Definition for singly-linked list
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

// Brute Force: Using Vector
bool isPalindromeBrute(Node* head) {
    // Store node values in vector
    vector<int> values;
    Node* temp = head;
    while (temp) {
        values.push_back(temp->val);
        temp = temp->next;
    }
    
    // Compare elements from both ends
    int i = 0, j = values.size() - 1;
    while (i <= j) {
        if (values[i] != values[j]) {
            return false;
        }
        i++;
        j--;
    }
    
    return true;
}

// Helper function to reverse a linked list
Node* reverse(Node* head) {
    // Base case: empty or single node
    if (!head || !head->next) {
        return head;
    }
    
    // Recursive reversal
    Node* newHead = reverse(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// Optimal: Reverse Second Half
bool isPalindromeOptimal(Node* head) {
    // Edge cases: empty list or single node
    if (!head || !head->next) {
        return true;
    }
    
    // Step 1: Find middle using Tortoise and Hare
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse second half
    Node* secondHalf = reverse(slow->next);
    
    // Step 3: Compare first and second halves
    Node* first = head;
    Node* second = secondHalf;
    while (second) {
        if (first->val != second->val) {
            return false;
        }
        first = first->next;
        second = second->next;
    }
    
    // Note: List restoration (reversing second half back) is skipped as not required
    return true;
}

int main() {
    // Create sample linked list: 1->2->3->2->1
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(1);
    
    // Test Brute Force
    cout << "Brute Force: " << (isPalindromeBrute(head) ? "True" : "False") << endl;
    
    // Test Optimal
    cout << "Optimal: " << (isPalindromeOptimal(head) ? "True" : "False") << endl;
    
    // Clean up memory
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}
