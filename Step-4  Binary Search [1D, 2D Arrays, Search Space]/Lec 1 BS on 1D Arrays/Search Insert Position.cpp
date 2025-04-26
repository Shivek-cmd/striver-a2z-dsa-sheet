
#include <bits/stdc++.h>
using namespace std;
/* 
==============================================================================
Section 1: Problem Statement
==============================================================================
Given a sorted array of distinct integers and a target value, find the index of the
target if it exists in the array. If not, return the index where it would be inserted
to maintain the sorted order.

Example Inputs and Outputs:
- Input: arr = [1, 3, 5, 6], target = 5
  Output: 2 (target 5 is at index 2)
- Input: arr = [1, 3, 5, 6], target = 2
  Output: 1 (target 2 should be inserted at index 1)
- Input: arr = [1, 3, 5, 6], target = 7
  Output: 4 (target 7 should be inserted at index 4)
- Input: arr = [], target = 1
  Output: 0 (insert at index 0 in empty array)

Constraints:
- 0 <= arr.size() <= 10^4
- -10^4 <= arr[i], target <= 10^4
- arr is sorted in ascending order with distinct values.

Edge Cases:
- Empty array
- Target smaller than all elements (insert at start)
- Target larger than all elements (insert at end)
- Target equal to an existing element
- Single-element array
*/

namespace SearchInsertPosition {

    /* 
    ==============================================================================
    Section 2: Solution Approaches
    ==============================================================================
    */
    
    // Approach 1: Linear Search (Brute Force)
    // Logic:
    // - Iterate through the array from left to right.
    // - If we find the target, return its index.
    // - If we encounter an element greater than the target, return the current index
    //   as the insertion point.
    // - If we reach the end, return the array size (insert at end).
    // Steps:
    // 1. If array is empty, return 0.
    // 2. For each index i, if arr[i] >= target, return i.
    // 3. If loop completes, return arr.size().
    // Time Complexity: O(n), where n is array size (scans entire array in worst case).
    // Space Complexity: O(1), no extra space used.
    // Limitations:
    // - Inefficient for large arrays since it doesn't leverage the sorted property.
    // - Always takes O(n) time even when target is at the start.
    
    // Approach 2: Binary Search (Optimal)
    // Logic:
    // - Since the array is sorted, use binary search to find the target or its insertion
    //   point efficiently.
    // - Maintain a variable to track the potential insertion index (upper bound).
    // - In each iteration, update the insertion index when a larger element is found.
    // Steps:
    // 1. If array is empty, return 0.
    // 2. Initialize low = 0, high = n-1, result = n.
    // 3. While low <= high:
    //    a. Compute mid = low + (high - low) / 2.
    //    b. If arr[mid] == target, return mid.
    //    c. If arr[mid] > target, update result = mid, search left (high = mid - 1).
    //    d. If arr[mid] < target, search right (low = mid + 1).
    // 4. Return result.
    // Time Complexity: O(log n), where n is array size (binary search halves the search
    //   space each iteration).
    // Space Complexity: O(1), only uses a few variables.
    // Why Optimal:
    // - Leverages the sorted property to reduce search time from O(n) to O(log n).
    // - Efficiently handles all cases, including when the target is not present.
    // Trade-offs:
    // - Slightly more complex to implement than linear search.
    // - Requires the array to be sorted.
    
    // Approach 3: Modified Binary Search (Alternative Optimal)
    // Logic:
    // - Similar to binary search but explicitly tracks the insertion point by returning
    //   low after the loop ends (low converges to the insertion point).
    // Steps:
    // 1. If array is empty, return 0.
    // 2. Initialize low = 0, high = n-1.
    // 3. While low <= high:
    //    a. Compute mid = low + (high - low) / 2.
    //    b. If arr[mid] == target, return mid.
    //    c. If arr[mid] > target, search left (high = mid - 1).
    //    d. If arr[mid] < target, search right (low = mid + 1).
    // 4. Return low (insertion point).
    // Time Complexity: O(log n), same as binary search.
    // Space Complexity: O(1), no extra space.
    // Limitations:
    // - Essentially equivalent to Approach 2 but with a different way of tracking the
    //   insertion point.
    // - No significant advantage over Approach 2 but provided for completeness.
    
    /* 
    ==============================================================================
    Section 3: Code Implementation
    ==============================================================================
    */
    
    // Approach 1: Linear Search
    int linearSearchInsert(const vector<int>& arr, int target) {
        // Handle empty array
        if (arr.empty()) return 0;
    
        // Iterate through array
        for (int i = 0; i < arr.size(); ++i) {
            // If current element is >= target, this is the insertion point
            if (arr[i] >= target) {
                return i;
            }
        }
    
        // If target is larger than all elements, insert at end
        return arr.size();
    }
    
    // Approach 2: Binary Search (Optimal)
    int binarySearchInsert(const vector<int>& arr, int target) {
        int n = arr.size();
        // Handle empty array
        if (n == 0) return 0;
    
        int low = 0, high = n - 1;
        int result = n; // Default insertion point (end of array)
    
        while (low <= high) {
            int mid = low + (high - low) / 2; // Avoid integer overflow
            if (arr[mid] == target) {
                return mid; // Target found
            } else if (arr[mid] > target) {
                result = mid; // Update insertion point
                high = mid - 1; // Search left
            } else {
                low = mid + 1; // Search right
            }
        }
    
        return result; // Return insertion point
    }
    
    // Approach 3: Modified Binary Search
    int modifiedBinarySearchInsert(const vector<int>& arr, int target) {
        int n = arr.size();
        // Handle empty array
        if (n == 0) return 0;
    
        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2; // Avoid integer overflow
            if (arr[mid] == target) {
                return mid; // Target found
            } else if (arr[mid] > target) {
                high = mid - 1; // Search left
            } else {
                low = mid + 1; // Search right
            }
        }
    
        return low; // Low is the insertion point
    }
    
    // Test function to demonstrate all approaches
    void testApproaches(const vector<int>& arr, int target) {
        cout << "Array: [";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
        }
        cout << "], Target: " << target << endl;
    
        cout << "Linear Search Result: " << linearSearchInsert(arr, target) << endl;
        cout << "Binary Search Result: " << binarySearchInsert(arr, target) << endl;
        cout << "Modified Binary Search Result: " << modifiedBinarySearchInsert(arr, target) << endl;
        cout << "----------------------------------------" << endl;
    }
    
    } // namespace SearchInsertPosition
    
    int main() {
        using namespace SearchInsertPosition;
    
        // Test cases
        vector<int> arr1 = {1, 3, 5, 6};
        int target1 = 5;
        testApproaches(arr1, target1);
    
        vector<int> arr2 = {1, 3, 5, 6};
        int target2 = 2;
        testApproaches(arr2, target2);
    
        vector<int> arr3 = {1, 3, 5, 6};
        int target3 = 7;
        testApproaches(arr3, target3);
    
        vector<int> arr4 = {};
        int target4 = 1;
        testApproaches(arr4, target4);
    
        vector<int> arr5 = {1};
        int target5 = 0;
        testApproaches(arr5, target5);
    
        return 0;
    }