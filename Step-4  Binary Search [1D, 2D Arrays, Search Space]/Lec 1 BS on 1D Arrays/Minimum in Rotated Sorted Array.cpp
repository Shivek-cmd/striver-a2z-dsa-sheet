#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Given an integer array arr of size N, sorted in ascending order (with distinct values).
The array is rotated between 1 to N times. Find the minimum element in the array.

Examples:
    Example 1:
        Input: arr = [4,5,6,7,0,1,2,3]
        Output: 0
        Explanation: Array was rotated 4 times, 0 is the minimum element.
    Example 2:
        Input: arr = [3,4,5,1,2]
        Output: 1
        Explanation: Array was rotated 3 times, 1 is the minimum element.

Constraints:
    - 1 <= N <= 10^5
    - -10^9 <= arr[i] <= 10^9
    - Array contains distinct values and is rotated between 1 and N times.

Edge Cases:
    - Single element array (N=1): Return the only element.
    - Array not rotated: Minimum is at index 0.
    - Array rotated N times: Minimum is at index 0.
    - Array rotated once: Minimum is at index N-1.
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
- Iterate through the array and track the minimum element.
- Since the array is rotated, the minimum element marks the rotation point.

Algorithm:
1. Initialize mini = INT_MAX.
2. For each element arr[i] in the array:
   - Update mini = min(mini, arr[i]).
3. Return mini.

Time Complexity: O(N)
- We traverse the entire array once.

Space Complexity: O(1)
- Only a single variable (mini) is used.

Limitations:
- Inefficient for large arrays as it checks every element.
- Does not leverage the sorted and rotated property of the array.

----------------------------------------
Approach 2: Optimal (Binary Search)
----------------------------------------
Logic:
- The array is sorted and rotated, so one half (left or right) is always sorted.
- The minimum element is the first element of the unsorted half or the smallest in the sorted half.
- Use binary search to identify the sorted half and update the minimum.

Algorithm:
1. Initialize ans = INT_MAX, low = 0, high = N-1.
2. While low <= high:
   - Compute mid = low + (high - low) / 2.
   - If arr[low] <= arrMID:
     - Left half is sorted, minimum in left half is arr[low].
     - Update ans = min(ans, arr[low]).
     - Eliminate left half: low = mid + 1.
   - Else:
     - Right half is sorted, minimum in right half is arr[mid].
     - Update ans = min(ans, arr[mid]).
     - Eliminate right half: high = mid - 1.
3. Return ans.

Time Complexity: O(log N)
- Binary search halves the search space in each iteration.

Space Complexity: O(1)
- Only uses a constant amount of extra space.

Advantages:
- Efficient for large arrays due to logarithmic time complexity.
- Leverages the sorted property to avoid checking every element.

Limitations:
- Slightly complex to implement correctly compared to linear search.
- Assumes distinct values to ensure clear sorted/unsorted halves.

----------------------------------------
Approach 3: Further Optimized Binary Search
----------------------------------------
Logic:
- Extends Approach 2 by checking if the entire subarray from low to high is sorted.
- If arr[low] <= arr[high], the subarray is sorted, and arr[low] is the minimum.
- This avoids unnecessary binary search steps when the subarray is fully sorted.

Algorithm:
1. Initialize ans = INT_MAX, low = 0, high = N-1.
2. While low <= high:
   - Compute mid = low + (high - low) / 2.
   - If arr[low] <= arr[high]:
     - Subarray is sorted, update ans = min(ans, arr[low]).
     - Break, as no further search is needed.
   - If arr[low] <= arr[mid]:
     - Left half is sorted, update ans = min(ans, arr[low]).
     - Eliminate left half: low = mid + 1.
   - Else:
     - Right half is sorted, update ans = min(ans, arr[mid]).
     - Eliminate right half: high = mid - 1.
3. Return ans.

Time Complexity: O(log N)
- Still uses binary search, but may terminate earlier for sorted subarrays.

Space Complexity: O(1)
- No extra data structures used.

Advantages:
- Optimizes cases where the subarray is fully sorted, reducing iterations.
- Maintains the efficiency of binary search for worst-case scenarios.

Limitations:
- Minimal improvement over Approach 2 in worst-case scenarios.
- Slightly more conditions to check, increasing code complexity.

Why Approach 3 is Optimal:
- Combines the efficiency of binary search with an early termination condition.
- Handles all edge cases (single element, no rotation, full rotation) efficiently.
- Maintains O(log N) time complexity while potentially reducing iterations.
==============================================================================
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Brute Force (Linear Search)
int findMinBruteForce(const vector<int>& arr) {
    // Handle edge case: empty array
    if (arr.empty()) return INT_MAX;
    
    int mini = INT_MAX;
    // Iterate through array to find minimum
    for (int num : arr) {
        mini = min(mini, num);
    }
    return mini;
}

// Approach 2: Optimal Binary Search
int findMinBinarySearch(const vector<int>& arr) {
    // Handle edge cases
    if (arr.empty()) return INT_MAX;
    if (arr.size() == 1) return arr[0];
    
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid integer overflow
        
        // If left half is sorted
        if (arr[low] <= arr[mid]) {
            // Update ans with minimum of left half
            ans = min(ans, arr[low]);
            // Eliminate left half
            low = mid + 1;
        }
        // If right half is sorted
        else {
            // Update ans with minimum of right half
            ans = min(ans, arr[mid]);
            // Eliminate right half
            high = mid - 1;
        }
    }
    return ans;
}

// Approach 3: Further Optimized Binary Search
int findMinOptimized(const vector<int>& arr) {
    // Handle edge cases
    if (arr.empty()) return INT_MAX;
    if (arr.size() == 1) return arr[0];
    
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid integer overflow
        
        // Check if subarray from low to high is sorted
        if (arr[low] <= arr[high]) {
            // Update ans with minimum of sorted subarray
            ans = min(ans, arr[low]);
            break; // No further search needed
        }
        
        // If left half is sorted
        if (arr[low] <= arr[mid]) {
            // Update ans with minimum of left half
            ans = min(ans, arr[low]);
            // Eliminate left half
            low = mid + 1;
        }
        // If right half is sorted
        else {
            // Update ans with minimum of right half
            ans = min(ans, arr[mid]);
            // Eliminate right half
            high = mid - 1;
        }
    }
    return ans;
}

// Main function to test all approaches
int main() {
    // Test case 1
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2, 3};
    cout << "Test Case 1:\n";
    cout << "Brute Force: " << findMinBruteForce(arr1) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr1) << endl;
    cout << "Optimized Binary Search: " << findMinOptimized(arr1) << endl;
    
    // Test case 2
    vector<int> arr2 = {3, 4, 5, 1, 2};
    cout << "\nTest Case 2:\n";
    cout << "Brute Force: " << findMinBruteForce(arr2) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr2) << endl;
    cout << "Optimized Binary Search: " << findMinOptimized(arr2) << endl;
    
    // Edge case: Single element
    vector<int> arr3 = {1};
    cout << "\nEdge Case (Single Element):\n";
    cout << "Brute Force: " << findMinBruteForce(arr3) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr3) << endl;
    cout << "Optimized Binary Search: " << findMinOptimized(arr3) << endl;
    
    // Edge case: No rotation
    vector<int> arr4 = {1, 2, 3, 4, 5};
    cout << "\nEdge Case (No Rotation):\n";
    cout << "Brute Force: " << findMinBruteForce(arr4) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr4) << endl;
    cout << "Optimized Binary Search: " << findMinOptimized(arr4) << endl;
    
    return 0;
}