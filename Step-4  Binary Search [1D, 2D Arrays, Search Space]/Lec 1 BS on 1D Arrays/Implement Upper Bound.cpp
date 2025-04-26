#include <bits/stdc++.h>
using namespace std;

/**
  ==============================================================================
Section 1: Problem Statement
==============================================================================

 *
 * Problem: Upper Bound in a Sorted Array
 * Given a sorted array of N integers and an integer x, find the smallest index i such
 * that arr[i] > x. If no such index exists, return N (the size of the array).
 *
 * Example 1:
 * Input: N = 4, arr = {1, 2, 2, 3}, x = 2
 * Output: 3
 * Explanation: Index 3 is the smallest index such that arr[3] = 3 > x.
 *
 * Example 2:
 * Input: N = 5, arr = {3, 5, 8, 15, 19}, x = 8
 * Output: 4
 * Explanation: Index 4 is the smallest index such that arr[4] = 19 > x.
 *
 * Constraints:
 * - 1 <= N <= 10^5 (array size)
 * - -10^9 <= arr[i], x <= 10^9 (array elements and target value)
 * - The array is sorted in non-decreasing order.
 *
 * Edge Cases:
 * - Empty array (return 0)
 * - x smaller than all elements (return 0)
 * - x greater than or equal to all elements (return N)
 * - Multiple occurrences of x (return the index after the last occurrence)
 */

/**

==============================================================================
Section 2: Solution Approaches
==============================================================================


 *
 * Approach 1: Naive Approach (Linear Search)
 * Logic:
 * - Since the array is sorted, iterate through the array from the start.
 * - Return the first index i where arr[i] > x.
 * - If no such index is found, return N (size of the array).
 *
 * Steps:
 * 1. Iterate through the array from index 0 to N-1.
 * 2. If arr[i] > x, return i.
 * 3. If the loop completes without finding such an index, return N.
 *
 * Time Complexity: O(N)
 * - Reason: In the worst case (e.g., x is greater than or equal to all elements), 
 *   we scan the entire array.
 *
 * Space Complexity: O(1)
 * - Reason: Only a constant amount of extra space is used.
 *
 * Limitations:
 * - Inefficient for large arrays due to linear traversal.
 * - Does not leverage the sorted property of the array.
 *
 * ---
 *
 * Approach 2: Optimal Approach (Binary Search)
 * Logic:
 * - Since the array is sorted, use binary search to find the smallest index i where
 *   arr[i] > x.
 * - Maintain a result variable to track the potential upper bound.
 * - Adjust the search range based on whether arr[mid] > x or arr[mid] <= x.
 *
 * Steps:
 * 1. Initialize low = 0, high = N-1, and result = N.
 * 2. While low <= high:
 *    a. Compute mid = low + (high - low) / 2 to avoid integer overflow.
 *    b. If arr[mid] > x:
 *       - Update result = mid (potential upper bound).
 *       - Search the left half (high = mid - 1) for a smaller index.
 *    c. If arr[mid] <= x:
 *       - Search the right half (low = mid + 1).
 * 3. Return result.
 *
 * Time Complexity: O(log N)
 * - Reason: Binary search halves the search space in each iteration.
 *
 * Space Complexity: O(1)
 * - Reason: Only a constant amount of extra space is used.
 *
 * Why Optimal?
 * - Leverages the sorted property of the array to reduce the time complexity from O(N)
 *   to O(log N).
 * - Efficient for large arrays, as it minimizes the number of comparisons.
 *
 * Trade-offs:
 * - Requires the array to be sorted.
 * - Slightly more complex to implement than linear search.
 */

/**
 
==============================================================================
Section 3: Code Implementation
==============================================================================
 */

/**
 * Function for Naive Approach (Linear Search)
 * @param arr: Sorted vector of integers
 * @param x: Target value to find upper bound for
 * @return: Smallest index i where arr[i] > x, or n if no such index exists
 */
int upperBoundNaive(vector<int>& arr, int x) {
    int n = arr.size();
    
    /** Handle edge case: empty array */
    if (n == 0) return 0;
    
    /** Linearly scan the array */
    for (int i = 0; i < n; i++) {
        if (arr[i] > x) {
            return i; /** Return first index where arr[i] > x */
        }
    }
    
    return n; /** If no element > x, return size of array */
}

/**
 * Function for Optimal Approach (Binary Search)
 * @param arr: Sorted vector of integers
 * @param x: Target value to find upper bound for
 * @return: Smallest index i where arr[i] > x, or n if no such index exists
 */
int upperBoundOptimal(vector<int>& arr, int x) {
    int n = arr.size();
    
    /** Handle edge case: empty array */
    if (n == 0) return 0;
    
    int low = 0, high = n - 1;
    int result = n; /** Default result if no element > x */
    
    while (low <= high) {
        int mid = low + (high - low) / 2; /** Avoid integer overflow */
        if (arr[mid] > x) {
            result = mid; /** Update potential upper bound */
            high = mid - 1; /** Search left half for smaller index */
        } else {
            low = mid + 1; /** Search right half */
        }
    }
    
    return result;
}

/**
 * Main function to test both approaches
 */
int main() {
    /** Test cases */
    vector<vector<int>> testCases = {
        {1, 2, 2, 3},          /** x = 2 */
        {3, 5, 8, 15, 19},     /** x = 8 */
        {},                     /** x = 1 (empty array) */
        {1, 1, 1},             /** x = 1 (all equal elements) */
        {1, 2, 3},             /** x = 3 (x equal to largest) */
        {1, 2, 3}              /** x = 0 (x smaller than all) */
    };
    vector<int> xValues = {2, 8, 1, 1, 3, 0};
    vector<int> expected = {3, 4, 0, 3, 3, 0};
    
    for (int i = 0; i < testCases.size(); i++) {
        vector<int>& arr = testCases[i];
        int x = xValues[i];
        
        /** Test Naive Approach */
        int resultNaive = upperBoundNaive(arr, x);
        cout << "Test Case " << i + 1 << " (Naive): x = " << x << ", Result = " << resultNaive;
        cout << (resultNaive == expected[i] ? " (Pass)" : " (Fail)") << endl;
        
        /** Test Optimal Approach */
        int resultOptimal = upperBoundOptimal(arr, x);
        cout << "Test Case " << i + 1 << " (Optimal): x = " << x << ", Result = " << resultOptimal;
        cout << (resultOptimal == expected[i] ? " (Pass)" : " (Fail)") << endl;
        
        cout << endl;
    }
    
    return 0;
}

/**
 * Expected Output:
 * Test Case 1 (Naive): x = 2, Result = 3 (Pass)
 * Test Case 1 (Optimal): x = 2, Result = 3 (Pass)
 *
 * Test Case 2 (Naive): x = 8, Result = 4 (Pass)
 * Test Case 2 (Optimal): x = 8, Result = 4 (Pass)
 *
 * Test Case 3 (Naive): x = 1, Result = 0 (Pass)
 * Test Case 3 (Optimal): x = 1, Result = 0 (Pass)
 *
 * Test Case 4 (Naive): x = 1, Result = 3 (Pass)
 * Test Case 4 (Optimal): x = 1, Result = 3 (Pass)
 *
 * Test Case 5 (Naive): x = 3, Result = 3 (Pass)
 * Test Case 5 (Optimal): x = 3, Result = 3 (Pass)
 *
 * Test Case 6 (Naive): x = 0, Result = 0 (Pass)
 * Test Case 6 (Optimal): x = 0, Result = 0 (Pass)
 */