/*
Problem Statement:
Given an array, print all the elements which are leaders. A Leader is an element that is greater than all of the elements on its right side in the array.

Example 1:
Input:
 arr = [4, 7, 1, 0]
Output:
 7 1 0
Explanation:
Rightmost element is always a leader. 7 and 1 are greater than the elements in their right side.

Example 2:
Input:
 arr = [10, 22, 12, 3, 0, 6]
Output:
 22 12 6
Explanation:
6 is a leader. In addition to that, 12 is greater than all the elements in its right side (3, 0, 6), also 22 is greater than 12, 3, 0, 6.

-----------------------------------------------------
Approach 1 - Brute Force Approach:
-----------------------------------------------------

- In this approach, we use two loops:
  - The outer loop picks each element one by one.
  - The inner loop compares this element with all the elements to its right.
  - If the element is greater than or equal to all elements on its right side, it is a leader.
- This approach takes O(n^2) time because we compare every element with all the elements on its right.

Time complexity: O(n^2)
Space complexity: O(n) (for storing leaders in a vector)




-----------------------------------------------------
Approach 2 - Optimized Approach:(Traverse from Right)
-----------------------------------------------------
 - The rightmost element is always a leader. 
 - For each element, if it is greater than the current maximum element (from its right side), it is a leader.
 - Keep updating the maximum element as you move from right to left.
 - This reduces the time complexity to O(n).


Time complexity: O(n) (only one loop from right to left)
Space complexity: O(n) (for storing leaders in a vector)

*/


#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;


vector<int> printLeadersBruteForce(int arr[], int n) {
    vector<int> leaders;
    for (int i = 0; i < n; i++) {
        bool isLeader = true;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] >= arr[i]) {
                isLeader = false;
                break;
            }
        }
        if (isLeader) {
            leaders.push_back(arr[i]);
        }
    }
    return leaders;
}



vector<int> printLeadersOptimized(int arr[], int n) {
    vector<int> leaders;
    int maxFromRight = arr[n - 1];  // The last element is always a leader
    leaders.push_back(maxFromRight);

    // Traverse the array from second last to the first element
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > maxFromRight) {
            leaders.push_back(arr[i]);
            maxFromRight = arr[i];  // Update the maximum from the right side
        }
    }

    // The leaders are stored in reverse order, so we reverse them before returning
    reverse(leaders.begin(), leaders.end());
    return leaders;
}

// Main function to test all approaches
int main() {
    // Sample Input Arrays for Testing
    int arr1[] = {4, 7, 1, 0};
    int arr2[] = {10, 22, 12, 3, 0, 6};
    
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    // Testing Brute Force Approach
    cout << "Brute Force Leaders for arr1: ";
    vector<int> leaders1 = printLeadersBruteForce(arr1, n1);
    for (int leader : leaders1) {
        cout << leader << " ";
    }
    cout << endl;

    // Testing Optimized Approach
    cout << "Optimized Leaders for arr1: ";
    vector<int> leadersOptimized1 = printLeadersOptimized(arr1, n1);
    for (int leader : leadersOptimized1) {
        cout << leader << " ";
    }
    cout << endl;
    
    // Testing Brute Force Approach for arr2
    cout << "Brute Force Leaders for arr2: ";
    vector<int> leaders2 = printLeadersBruteForce(arr2, n2);
    for (int leader : leaders2) {
        cout << leader << " ";
    }
    cout << endl;
    
    // Testing Optimized Approach for arr2
    cout << "Optimized Leaders for arr2: ";
    vector<int> leadersOptimized2 = printLeadersOptimized(arr2, n2);
    for (int leader : leadersOptimized2) {
        cout << leader << " ";
    }
    cout << endl;

    return 0;
}
