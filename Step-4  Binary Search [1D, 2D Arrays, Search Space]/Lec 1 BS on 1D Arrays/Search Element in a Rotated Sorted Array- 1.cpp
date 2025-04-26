#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem:
    Given an integer array arr of size N, sorted in ascending order (with distinct values) 
    and a target value k. Now the array is rotated at some pivot point unknown to you. 
    Find the index at which k is present. If k is not present, return -1.

Examples:
    Example 1:
        Input: arr = [4,5,6,7,0,1,2,3], k = 0
        Output: 4
        Explanation: 0 is present at index 4.

    Example 2:
        Input: arr = [4,5,6,7,0,1,2], k = 3
        Output: -1
        Explanation: 3 is not present in the array.

Constraints:
    - 1 <= N <= 10^5
    - -10^9 <= arr[i], k <= 10^9
    - Array is sorted (ascending) but rotated
    - All array elements are distinct

Edge Cases:
    - Empty array
    - Single element array
    - k smaller or larger than all elements
    - k at pivot point
==============================================================================

==============================================================================
Section 2: Solution Approaches
==============================================================================

Approach 1: Naive Approach (Brute Force)
----------------------------------------
Logic:
    - Traverse the array linearly.
    - Check each element if it matches k.

Algorithm:
    1. Start from index 0.
    2. Compare each element with k.
    3. If found, return the index.
    4. If not found after complete traversal, return -1.

Time Complexity:
    - O(N), where N = size of the array.

Space Complexity:
    - O(1), no extra space.

Limitations:
    - Slow for large N.

------------------------------------------------------------

Approach 2: Optimal Approach (Using Modified Binary Search)
------------------------------------------------------------
Observation:
    - Even though the array is rotated, for any mid index, at least one side (left or right) must be sorted.

Logic:
    - Apply binary search.
    - Identify the sorted half at every step.
    - Check if k lies in the sorted half:
        - If yes, shrink search space to that half.
        - Otherwise, eliminate that half.

Algorithm:
    1. Initialize low = 0, high = n - 1.
    2. While low <= high:
        - mid = (low + high) / 2
        - If arr[mid] == k, return mid.
        - If left half [low..mid] is sorted:
            - If arr[low] <= k < arr[mid]: high = mid - 1.
            - Else: low = mid + 1.
        - Else right half [mid..high] is sorted:
            - If arr[mid] < k <= arr[high]: low = mid + 1.
            - Else: high = mid - 1.
    3. If element not found, return -1.

Time Complexity:
    - O(log N)

Space Complexity:
    - O(1)

Why Optimal:
    - Reduces search space logarithmically.

==============================================================================

==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// ===================== Approach 1: Brute Force =====================
int searchInRotatedArrayBruteForce(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// ===================== Approach 2: Optimal (Binary Search) =====================
int searchInRotatedArrayOptimal(const vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (target >= arr[low] && target < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if (target > arr[mid] && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return -1; // Target not found
}

// ===================== Main Function =====================
int main() {
    // Sample test cases
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2, 3};
    int target1 = 0;
    
    vector<int> arr2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;

    cout << "Brute Force Approach:" << endl;
    cout << "Index of " << target1 << " : " << searchInRotatedArrayBruteForce(arr1, target1) << endl;
    cout << "Index of " << target2 << " : " << searchInRotatedArrayBruteForce(arr2, target2) << endl;

    cout << "\nOptimal (Binary Search) Approach:" << endl;
    cout << "Index of " << target1 << " : " << searchInRotatedArrayOptimal(arr1, target1) << endl;
    cout << "Index of " << target2 << " : " << searchInRotatedArrayOptimal(arr2, target2) << endl;

    return 0;
}
