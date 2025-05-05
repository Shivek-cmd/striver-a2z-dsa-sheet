#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
// Problem: Given the heads of two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each node contains a single digit.
// Add the two numbers and return the sum as a linked list.
//
// Example 1:
// Input: l1 = [2,4,3], l2 = [5,6,4] (represents 342 + 465)
// Output: [7,0,8] (represents 807)
//
// Example 2:
// Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] (represents 9999999 + 9999)
// Output: [8,9,9,9,0,0,0,1] (represents 10009998)
//
// Constraints:
// - The linked lists are non-empty.
// - Each node's value is a digit between 0 and 9.
// - The numbers do not have leading zeros, except for the number 0 itself.
//
// Edge Cases:
// - Lists of different lengths (e.g., [9,9,9,9,9,9,9] + [9,9,9,9]).
// - Carry propagation to a new digit (e.g., [9,9] + [9,9] = [8,9,0,1]).
// - Single-digit lists (e.g., [1] + [2] = [3]).
// - Zero inputs (e.g., [0] + [0] = [0]).

// ==============================================================================
// Section 2: Solution Approaches
// ==============================================================================

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

/*
Approach 1: Iterative
- Logic: Traverse both lists simultaneously, summing digits and carry, and build a new list.
- Thought Process:
  - Since digits are in reverse order, addition starts from the least significant digit, mimicking
    standard arithmetic.
  - Key pattern: Each position’s sum is (digit1 + digit2 + carry), with the new digit as sum % 10
    and carry as sum / 10.
  - Use a dummy node to simplify list construction and handle edge cases like leading digits.
  - Continue processing until both lists are exhausted and no carry remains.
- Steps:
  1. Initialize a dummy node and a current pointer for the result list.
  2. Traverse both lists while nodes exist or carry is non-zero.
  3. Compute sum = (digit1 or 0) + (digit2 or 0) + carry.
  4. Create a new node with sum % 10.
  5. Update carry = sum / 10 (0 or 1, as sum <= 19).
  6. Link the new node and move pointers.
  7. Return the result list’s head.
- Time Complexity: O(max(N, M))
  - N and M are the lengths of l1 and l2.
  - Process each node in the longer list, plus one extra for final carry if needed.
- Space Complexity: O(1) auxiliary space (excluding output list)
  - Only use pointers and a constant amount of variables.
  - The output list is required, so its space (O(max(N, M))) is not counted as auxiliary.
- Limitations:
  - Requires careful handling of differing list lengths and carry.
  - Iterative approach is straightforward but may feel verbose compared to recursion.

Approach 2: Recursive
- Logic: Recursively process each pair of digits, passing the carry to the next recursive call.
- Thought Process:
  - Recursion naturally processes one digit pair at a time, with the carry passed forward.
  - Key pattern: Each recursive call computes sum % 10 for the current digit and sum / 10 for
    the carry, building the list as it unwinds.
  - Base case is when both lists are null and no carry exists.
  - Recursive approach is elegant but uses stack space.
- Steps:
  1. Base case: If both l1 and l2 are null and carry is 0, return null.
  2. Compute sum = (digit1 or 0) + (digit2 or 0) + carry.
  3. Create a node with sum % 10.
  4. Recursively call for next nodes and carry = sum / 10.
  5. Link the current node to the recursive result.
  6. Return the current node.
- Time Complexity: O(max(N, M))
  - Each recursive call processes one digit pair, up to the longer list’s length.
- Space Complexity: O(max(N, M))
  - Recursive call stack depth is proportional to the longer list’s length.
- Limitations:
  - Stack overflow risk for very long lists (unlikely in practice).
  - Less intuitive for some developers compared to iterative.

Optimal Approach: Iterative (Approach 1)
- Why Optimal:
  - Same time complexity as recursive (O(max(N, M))), but O(1) auxiliary space versus O(max(N, M))
    for recursive stack.
  - Iterative approach is more memory-efficient, especially for long lists.
  - Simpler to debug and maintain, as it avoids recursive call overhead.
  - Handles all edge cases robustly with straightforward pointer manipulation.
*/

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Approach 1: Iterative (Optimal)
Node* addTwoNumbersIterative(Node* l1, Node* l2) {
    Node* dummyNode = new Node(-1); // Dummy node to simplify list construction
    Node* curr = dummyNode;         // Pointer to build result list
    int carry = 0;                  // Carry for addition

    // Process while nodes exist or carry remains
    while (l1 || l2 || carry) {
        int sum = carry; // Start with carry
        if (l1) {        // Add l1’s digit if available
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {        // Add l2’s digit if available
            sum += l2->val;
            l2 = l2->next;
        }

        // Create node with sum % 10
        Node* newNode = new Node(sum % 10);
        // Set carry using if-else
        if (sum < 10) {
            carry = 0;
        } else {
            carry = 1;
        }
        curr->next = newNode;
        curr = curr->next; // Move to next position
    }

    return dummyNode->next; // Return head of result list
}

// Approach 2: Recursive
Node* addTwoNumbersRecursive(Node* l1, Node* l2, int carry = 0) {
    // Base case: no nodes and no carry
    if (!l1 && !l2 && !carry) {
        return nullptr;
    }

    int sum = carry; // Start with carry
    if (l1) {        // Add l1’s digit if available
        sum += l1->val;
    }
    if (l2) {        // Add l2’s digit if available
        sum += l2->val;
    }

    // Create node with sum % 10
    Node* node = new Node(sum % 10);
    
    // Recurse with next nodes and carry
    node->next = addTwoNumbersRecursive(l1 ? l1->next : nullptr, 
                                       l2 ? l2->next : nullptr, 
                                       sum / 10);
    
    return node; // Return current node
}

int main() {
    // Sample input: l1 = [2,4,3], l2 = [5,6,4]
    Node* l1 = new Node(2);
    l1->next = new Node(4);
    l1->next->next = new Node(3);
    
    Node* l2 = new Node(5);
    l2->next = new Node(6);
    l2->next->next = new Node(4);
    
    // Use iterative approach (optimal)
    Node* result = addTwoNumbersIterative(l1, l2);
    
    // Print result
    while (result) {
        cout << result->val;
        if (result->next) cout << " -> ";
        result = result->next;
    }
    cout << endl;
    
    return 0;
}