
#include <bits/stdc++.h>
using namespace std;

// Section 1: Problem Statement
// Problem: Given an array of N integers, count the inversions in the array using merge-sort.
// An inversion is a pair (A[i], A[j]) such that i < j and A[j] < A[i].
// Input: A vector of N integers.
// Output: The number of inversions in the array.
// Constraints:
// - 1 <= N <= 10^5
// - 1 <= arr[i] <= 10^9
// Edge Cases:
// - N = 1: No inversions possible.
// - Sorted array: 0 inversions.
// - Reverse sorted array: Maximum inversions, N*(N-1)/2.
// Examples:
// Example 1: arr = {1, 2, 3, 4, 5} -> Result: 0 (sorted, no inversions)
// Example 2: arr = {5, 4, 3, 2, 1} -> Result: 10 (reverse sorted, max inversions)
// Example 3: arr = {5, 3, 2, 1, 4} -> Result: 7 (pairs: (5,1), (5,3), (5,2), (5,4), (3,2), (3,1), (2,1))

// Section 2: Solution Approaches
/*
-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------


Logic:
- Check every possible pair (i, j) where i < j to see if arr[i] > arr[j].
- If the condition is met, it’s an inversion.
Thought Process:
- Inversions are defined by pairs where the earlier index has a larger value than the later index.
- A straightforward way is to compare each element with all subsequent elements.
Steps:
1. Iterate i from 0 to N-2.
2. For each i, iterate j from i+1 to N-1.
3. If arr[i] > arr[j], increment the inversion count.
4. Return the total count.
Time Complexity: O(N^2)
- Nested loops: outer loop runs N-1 times, inner loop runs up to N-1 times.
Space Complexity: O(1)
- Only uses a counter variable.
Limitations:
- Inefficient for large N (up to 10^5), leading to 10^10 operations.
- Doesn’t utilize the merge-sort requirement.
Trade-offs:
- Simple to implement but impractical for large inputs.



-----------------------------------------------------
Approach 2: Merge-Sort (Optimal)
-----------------------------------------------------

Logic:
- Use merge-sort to sort the array and count inversions during the merge step.
- When merging two sorted subarrays, if an element from the right subarray is smaller than an element from the left subarray, it forms inversions with all remaining elements in the left subarray.
Thought Process:
- Merge-sort divides the array into halves, sorts them, and merges them.
- During merging, if a[right] < a[left], the number of inversions is the number of elements remaining in the left subarray (mid - left + 1).
- This leverages the sorting process to count inversions efficiently.
Steps:
1. Recursively divide the array into two halves using mergeSort.
2. In mergeSort:
   - Call mergeSort on left half (low to mid).
   - Call mergeSort on right half (mid+1 to high).
   - Merge the halves and count inversions.
3. In merge:
   - Create a temporary array to store merged elements.
   - Use two pointers (left, right) for the left and right subarrays.
   - When a[right] < a[left], add (mid - left + 1) to inversions.
   - Copy remaining elements and transfer temp array to original array.
4. Return the total inversions from mergeSort.
Time Complexity: O(N log N)
- Merge-sort divides the array into log N levels, and each merge takes O(N) time.
- Inversion counting is done during the merge step without additional passes.
Space Complexity: O(N)
- Temporary array used in merge step.
Advantages:
- Meets the problem’s requirement to use merge-sort.
- Efficient for large N (up to 10^5).
Limitations:
- Requires extra space for the temporary array.
- More complex than brute force.
Why Optimal:
- O(N log N) is significantly faster than O(N^2) for large inputs.
- Leverages the sorting process to count inversions without extra iterations.

-----------------------------------------------------
// Section 3: Code Implementation
-----------------------------------------------------
*/



// Approach 1: Brute Force
long long countInversionsBruteForce(const vector<int>& arr) {
    long long inversions = 0;
    int n = arr.size();
    // Check all pairs (i, j) where i < j
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                inversions++; // Found an inversion
            }
        }
    }
    return inversions;
}

// Approach 2: Merge-Sort
// Merge function to merge two sorted subarrays and count inversions
long long merge(vector<int>& arr, int low, int mid, int high) {
    long long inversions = 0;
    vector<int> temp; // Temporary array for merging
    int left = low; // Pointer for left subarray
    int right = mid + 1; // Pointer for right subarray
    
    // Merge the two subarrays
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            // If arr[right] < arr[left], count inversions
            inversions += (mid - left + 1);
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
    
    return inversions;
}

// Merge-sort function to recursively divide and merge
long long mergeSort(vector<int>& arr, int low, int high) {
    long long inversions = 0;
    if (low < high) {
        int mid = low + (high - low) / 2;
        // Count inversions in left half
        inversions += mergeSort(arr, low, mid);
        // Count inversions in right half
        inversions += mergeSort(arr, mid + 1, high);
        // Count inversions during merge
        inversions += merge(arr, low, mid, high);
    }
    return inversions;
}

// Wrapper function for merge-sort approach
long long countInversionsMergeSort(const vector<int>& arr) {
    if (arr.empty()) return 0; // Handle empty array
    vector<int> temp = arr; // Create a copy to avoid modifying input
    return mergeSort(temp, 0, temp.size() - 1);
}

// Main function to test both approaches
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5},        // 0 inversions
        {5, 4, 3, 2, 1},        // 10 inversions
        {5, 3, 2, 1, 4}         // 7 inversions
    };
    
    for (int i = 0; i < testCases.size(); i++) {
        const auto& arr = testCases[i];
        cout << "Test Case " << i + 1 << ": Array = ";
        for (int x : arr) cout << x << " ";
        cout << endl;
        
        // Brute Force
        long long result1 = countInversionsBruteForce(arr);
        cout << "Brute Force - Inversions: " << result1 << endl;
        
        // Merge-Sort
        long long result2 = countInversionsMergeSort(arr);
        cout << "Merge-Sort - Inversions: " << result2 << endl;
        cout << endl;
    }
    
    return 0;
}