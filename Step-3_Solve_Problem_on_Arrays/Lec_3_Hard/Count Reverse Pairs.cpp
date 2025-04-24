
#include <bits/stdc++.h>
using namespace std;

// Section 1: Problem Statement
// Problem: Given an array of N integers, count the reverse pairs.
// A reverse pair is a pair (i, j) where i < j and arr[i] > 2*arr[j].
// Input: A vector of N integers.
// Output: The number of reverse pairs in the array.
// Constraints:
// - 1 <= N <= 10^5
// - -10^9 <= arr[i] <= 10^9
// Edge Cases:
// - N = 1: No pairs possible.
// - Array with negative numbers or zeros.
// - Large values leading to potential overflow in 2*arr[j].
// Examples:
// Example 1: arr = {1, 3, 2, 3, 1} -> Result: 2 (pairs: (3,1), (3,1))
// Example 2: arr = {3, 2, 1, 4} -> Result: 1 (pair: (3,1))

// Section 2: Solution Approaches
/*
-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------



Logic:
- Check every possible pair (i, j) where i < j to see if arr[i] > 2*arr[j].
- If the condition is met, it’s a reverse pair.
Thought Process:
- Reverse pairs are defined by pairs where the earlier index has a value more than twice the value at the later index.
- A straightforward way is to compare each element with all subsequent elements.
Steps:
1. Iterate i from 0 to N-2.
2. For each i, iterate j from i+1 to N-1.
3. If arr[i] > 2*arr[j], increment the reverse pair count.
4. Return the total count.
Time Complexity: O(N^2)
- Nested loops: outer loop runs N-1 times, inner loop runs up to N-1 times.
Space Complexity: O(1)
- Only uses a counter variable.
Limitations:
- Inefficient for large N (up to 10^5), leading to 10^10 operations.
Trade-offs:
- Simple to implement but impractical for large inputs.

-----------------------------------------------------
Approach 2: Merge-Sort (Optimal)
-----------------------------------------------------


Logic:
- Use merge-sort to process the array and count reverse pairs during the merge step.
- For each element in the left subarray, count elements in the right subarray where arr[i] > 2*arr[j].
- This is done before merging to leverage the sorted subarrays.
Thought Process:
- Merge-sort divides the array into halves, sorts them, and merges them.
- During merging, we can count pairs where arr[i] > 2*arr[j] by comparing elements from the left and right subarrays.
- Since subarrays are sorted, we can efficiently count pairs using two pointers.
Steps:
1. Recursively divide the array into two halves using mergeSort.
2. In mergeSort:
   - Call mergeSort on left half (low to mid).
   - Call mergeSort on right half (mid+1 to high).
   - Count pairs where arr[i] > 2*arr[j] using countPairs.
   - Merge the halves.
3. In countPairs:
   - Iterate through left subarray (low to mid).
   - For each arr[i], find elements in right subarray (mid+1 to high) where arr[i] > 2*arr[j].
   - Use a pointer to track valid j indices.
4. In merge:
   - Merge sorted subarrays into a temporary array.
   - Transfer merged elements back to the original array.
5. Return total reverse pairs from mergeSort.
Time Complexity: O(N log N)
- Merge-sort divides into log N levels, each taking O(N) for merge and countPairs.
- countPairs uses two pointers, iterating each subarray at most once per merge.
Space Complexity: O(N)
- Temporary array used in merge step.
Advantages:
- Efficient for large N (up to 10^5).
- Leverages sorting to count pairs without nested loops.
Limitations:
- Requires extra space for the temporary array.
- More complex than brute force.
Why Optimal:
- O(N log N) is significantly faster than O(N^2) for large inputs.
- Efficiently counts pairs during the merge process using sorted subarrays.
*/

// Section 3: Code Implementation

// Approach 1: Brute Force
long long countReversePairsBruteForce(const vector<int>& arr) {
    long long reversePairs = 0;
    int n = arr.size();
    // Check all pairs (i, j) where i < j
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            // Check if arr[i] > 2*arr[j]
            if ((long long)arr[i] > 2 * (long long)arr[j]) {
                reversePairs++; // Found a reverse pair
            }
        }
    }
    return reversePairs;
}

// Approach 2: Merge-Sort
// Function to count pairs where arr[i] > 2*arr[j]
long long countPairs(vector<int>& arr, int low, int mid, int high) {
    long long cnt = 0;
    int right = mid + 1;
    // Iterate through left subarray
    for (int i = low; i <= mid; i++) {
        // Find elements in right subarray where arr[i] > 2*arr[j]
        while (right <= high && (long long)arr[i] > 2 * (long long)arr[right]) {
            right++;
        }
        // All elements from mid+1 to right-1 satisfy the condition
        cnt += (right - (mid + 1));
    }
    return cnt;
}

// Merge function to merge two sorted subarrays
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp; // Temporary array for merging
    int left = low; // Pointer for left subarray
    int right = mid + 1; // Pointer for right subarray
    
    // Merge the two subarrays
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            temp.push_back(arr[right++]);
        }
    }
    
    // Copy remaining elements from left subarray
    while (left <= mid) {
        temp.push_back(arr[left++]);
    }
    
    // Copy remaining elements from right subarray
    while (right <= high) {
        temp.push_back(arr[right++]);
    }
    
    // Transfer merged elements back to original array
    for (int i = 0; i < temp.size(); i++) {
        arr[low + i] = temp[i];
    }
}

// Merge-sort function to recursively divide and merge
long long mergeSort(vector<int>& arr, int low, int high) {
    long long reversePairs = 0;
    if (low < high) {
        int mid = low + (high - low) / 2;
        // Count pairs in left half
        reversePairs += mergeSort(arr, low, mid);
        // Count pairs in right half
        reversePairs += mergeSort(arr, mid + 1, high);
        // Count pairs across halves
        reversePairs += countPairs(arr, low, mid, high);
        // Merge the subarrays
        merge(arr, low, mid, high);
    }
    return reversePairs;
}

// Wrapper function for merge-sort approach
long long countReversePairsMergeSort(const vector<int>& arr) {
    if (arr.empty()) return 0; // Handle empty array
    vector<int> temp = arr; // Create a copy to avoid modifying input
    return mergeSort(temp, 0, temp.size() - 1);
}

// Main function to test both approaches
int main() {
    vector<vector<int>> testCases = {
        {1, 3, 2, 3, 1},    // 2 reverse pairs
        {3, 2, 1, 4}        // 1 reverse pair
    };
    
    for (int i = 0; i < testCases.size(); i++) {
        const auto& arr = testCases[i];
        cout << "Test Case " << i + 1 << ": Array = ";
        for (int x : arr) cout << x << " ";
        cout << endl;
        
        // Brute Force
        long long result1 = countReversePairsBruteForce(arr);
        cout << "Brute Force - Reverse Pairs: " << result1 << endl;
        
        // Merge-Sort
        long long result2 = countReversePairsMergeSort(arr);
        cout << "Merge-Sort - Reverse Pairs: " << result2 << endl;
        cout << endl;
    }
    
    return 0;
}