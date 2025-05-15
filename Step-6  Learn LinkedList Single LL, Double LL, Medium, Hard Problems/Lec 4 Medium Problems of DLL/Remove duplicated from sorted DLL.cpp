/*
Problem: Remove duplicates from a sorted doubly linked list
Given the head of a doubly linked list with its values sorted in non-decreasing order, remove all 
duplicate occurrences of any value in the list so that only distinct values are present in the list. 
Return the head of the modified linked list.

Examples:
Input: head -> 1 <-> 1 <-> 3 <-> 3 <-> 4 <-> 5
Output: head -> 1 <-> 3 <-> 4 <-> 5
Explanation: All nodes with duplicate values (1 and 3) were removed, keeping only one occurrence.

Input: head -> 1 <-> 1 <-> 1 <-> 1 <-> 1 <-> 2
Output: head -> 1 <-> 2
Explanation: All duplicate nodes with value 1 were removed, keeping one 1 and the 2.

Constraints:
- The number of nodes in the list is in the range [1, 10^5].
- -10^9 <= Node.val <= 10^9.
- The list is sorted in non-decreasing order.
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

Node* removeDuplicates(Node* head) {
    // Function to remove all duplicate occurrences from sorted DLL
    if(head==nullptr || head->next==nullptr)
    {
        return head;
    }
    Node*temp1=head;
    Node*temp2=head->next;
    return head;
}

int main() {
    // Create a sample sorted doubly linked list: 1 <-> 1 <-> 3 <-> 3 <-> 4 <-> 5
    Node* head = new Node(1);
    head->next = new Node(1);
    head->next->prev = head;
    head->next->next = new Node(3);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(3);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new Node(4);
    head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = new Node(5);
    head->next->next->next->next->next->prev = head->next->next->next->next;

    // Call the function
    head = removeDuplicates(head);

    // Print the modified list
    Node* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " <-> ";
        curr = curr->next;
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