#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Given an integer array arr of size N, sorted in ascending order (with distinct values).
The array is rotated between 1 to N times. Find how many times the array has been rotated.
The rotation count is the index of the minimum element, as it indicates how many positions
the original sorted array was shifted.

Examples:
    Example 1:
        Input: arr = [4,5,6,7,0,1,2,3]
        Output: 4
        Explanation: Original array was [0,1,2,3,4,5,6,7]. Rotated 4 times, minimum (0) is at index 4.
    Example 2:
        Input: arr = [3,4,5,1,2]
        Output: 3
        Explanation: Original array was [1,2,3,4,5]. Rotated 3 times, minimum (1) is at index 3.

Constraints:
    - 1 <= N <= 10^5
    - -10^9 <= arr[i] <= 10^9
    - Array contains distinct values and is rotated between 1 and N times.

Edge Cases:
    - Single element array (N=1): Rotation count is 0 (no rotation possible).
    - Array not rotated: Minimum is at index 0, rotation count is 0.
    - Array rotated N times: Minimum is at index 0, rotation count is 0.
    - Array rotated once: Minimum is at index N-1, rotation count is N-1.
==============================================================================
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force (Linear Search)
----------------------------------------
Logic:
- The rotation count is the index of the minimum element in the array.
- Iterate through the array to find the minimum element and its index.
- The index of the minimum element indicates how many times the array was rotated.

Algorithm:
1. Initialize ans = INT_MAX and index = -1.
2. For each element arr[i] in the array:
   - If arr[i] < ans, update ans = arr[i] and index = i.
3. Return index as the rotation count.

Time Complexity: O(N)
- We traverse the entire array once to find the minimum element.

Space Complexity: O(1)
- Only two variables (ans and index) are used.

Limitations:
- Inefficient for large arrays as it checks every element.
- Does not utilize the sorted and rotated property of the array.

----------------------------------------
Approach 2: Optimal (Binary Search)
----------------------------------------
Logic:
- The minimum element's index is the rotation count, as it marks the point where the array was rotated.
- Since the array is sorted and rotated, one half (left or right) is always sorted.
- Use binary search to find the minimum element by identifying the sorted half and checking its leftmost element.
- Track the index of the minimum element found during the search.

Algorithm:
1. Initialize ans = INT_MAX, index = -1, low = 0, high = N-1.
2. While low <= high:
   - Compute mid = low + (high - low) / 2.
   - If arr[low] <= arr[high]:
     - Subarray is sorted, check if arr[low] < ans.
     - If true, update ans = arr[low] and index = low.
     - Break, as the minimum is found.
   - If arr[low] <= arr[mid]:
     - Left half is sorted, check if arr[low] < ans.
     - If true, update ans = arr[low] and index = low.
     - Eliminate left half: low = mid + 1.
   - Else:
     - Right half is sorted, check if arr[mid] < ans.
     - If true, update ans = arr[mid] and index = mid.
     - Eliminate right half: high = mid - 1.
3. Return index.

Time Complexity: O(log N)
- Binary search halves the search space in each iteration.

Space Complexity: O(1)
- Only a constant amount of extra space is used.

Advantages:
- Efficient for large arrays due to logarithmic time complexity.
- Leverages the sorted and rotated property to avoid linear traversal.
- Early termination when the subarray is fully sorted reduces iterations.

Limitations:
- More complex to implement than linear search.
- Assumes distinct values to ensure clear sorted/unsorted halves.

Why Approach 2 is Optimal:
- Achieves O(log N) time complexity, significantly faster than O(N) for large arrays.
- Efficiently handles all edge cases (single element, no rotation, full rotation).
- Early termination for sorted subarrays minimizes unnecessary iterations.
- Maintains O(1) space complexity, making it resource-efficient.
==============================================================================
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Brute Force (Linear Search)
int findRotationCountBruteForce(const vector<int>& arr) {
    // Handle edge case: empty array
    if (arr.empty()) return -1;
    
    int ans = INT_MAX, index = -1;
    // Iterate through array to find minimum and its index
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < ans) {
            ans = arr[i];
            index = i;
        }
    }
    return index;
}

// Approach 2: Optimal Binary Search
int findRotationCount(const vector<int>& arr) {
    // Handle edge cases
    if (arr.empty()) return -1;
    if (arr.size() == 1) return 0;
    
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX, index = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid integer overflow
        
        // Check if subarray from low to high is sorted
        if (arr[low] <= arr[high]) {
            // Update ans and index if arr[low] is smaller
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            break; // No further search needed
        }
        
        // If left half is sorted
        if (arr[low] <= arr[mid]) {
            // Update ans and index if arr[low] is smaller
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            // Eliminate left half
            low = mid + 1;
        }
        // If right half is sorted
        else {
            // Update ans and index if arr[mid] is smaller
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            // Eliminate right half
            high = mid - 1;
        }
    }
    return index;
}

// Main function to test both approaches
int main() {
    // Test case 1
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2, 3};
    cout << "Test Case 1:\n";
    cout << "Brute Force: " << findRotationCountBruteForce(arr1) << endl;
    cout << "Binary Search: " << findRotationCount(arr1) << endl;
    
    // Test case 2
    vector<int> arr2 = {3, 4, 5, 1, 2};
    cout << "\nTest Case 2:\n";
    cout << "Brute Force: " << findRotationCountBruteForce(arr2) << endl;
    cout << "Binary Search: " << findRotationCount(arr2) << endl;
    
    // Edge case: Single element
    vector<int> arr3 = {1};
    cout << "\nEdge Case (Single Element):\n";
    cout << "Brute Force: " << findRotationCountBruteForce(arr3) << endl;
    cout << "Binary Search: " << findRotationCount(arr3) << endl;
    
    // Edge case: No rotation
    vector<int> arr4 = {1, 2, 3, 4, 5};
    cout << "\nEdge Case (No Rotation):\n";
    cout << "Brute Force: " << findRotationCountBruteForce(arr4) << endl;
    cout << "Binary Search: " << findRotationCount(arr4) << endl;
    
    return 0;
}