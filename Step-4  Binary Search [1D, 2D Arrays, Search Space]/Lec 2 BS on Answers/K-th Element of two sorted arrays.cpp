#include <bits/stdc++.h>
using namespace std;

// ==============================================================================
// Section 1: Problem Statement
// ==============================================================================
/*
Problem: K-th Element of Two Sorted Arrays
Given two sorted arrays arr1 and arr2 of sizes m and n, find the k-th element in the 
merged sorted array.

Example:
Input: arr1 = [2, 3, 45], arr2 = [4, 6, 7, 8], k = 4
Output: 6
Explanation: Merged array = [2, 3, 4, 6, 7, 8, 45]. The 4th element is 6.

Constraints:
- 1 <= m, n <= 10^5
- 1 <= k <= m + n
- -10^9 <= arr1[i], arr2[i] <= 10^9

Edge Cases:
- One array is empty.
- k = 1 or k = m + n.
- Arrays have duplicate elements.
*/

// ==============================================================================
// Section 2: Observations and Solution Approaches
// ==============================================================================
/*
Observations:
1. **Key Patterns**:
   - Both arrays are sorted, suggesting a merge-like process or binary search to avoid full merging.
   - The k-th element in the merged array depends on the relative order of elements from both arrays.
   - For small k, we may not need to process the entire arrays; for large k, we need elements from both.
   - Binary search can optimize by partitioning the arrays into left and right halves, ensuring the k-th element is at the boundary.

2. **Intuitive Insights**:
   - Merging arrays explicitly is straightforward but inefficient in space or time.
   - We only need the k-th element, not the full merged array, so we can track positions without storing elements.
   - Binary search on the smaller array's contribution to the left partition (size k) can reduce the search space logarithmically.

3. **Mental Roadmap**:
   - Start with a brute-force merge to understand the baseline.
   - Optimize space by avoiding the merged array, tracking only the k-th element.
   - Use binary search to partition arrays, leveraging sorted property to eliminate halves efficiently.
   - Handle edge cases like empty arrays or k at boundaries.

==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force (Merge Arrays)
----------------------------------------
Logic:
- Merge both sorted arrays into a new array using the merge step of merge sort.
- Return the (k-1)-th element of the merged array (0-based indexing).
- Use two pointers to compare elements from arr1 and arr2, building the merged array.

Steps:
1. Initialize an empty result array arr3.
2. Use pointers i (for arr1) and j (for arr2) starting at 0.
3. While i < m and j < n:
   - If arr1[i] < arr2[j], append arr1[i] to arr3 and increment i.
   - Else, append arr2[j] to arr3 and increment j.
4. Append remaining elements from arr1 or arr2.
5. Return arr3[k-1].

Time Complexity: O(m + n)
- Merging takes O(m + n) to traverse both arrays.
Space Complexity: O(m + n)
- Extra array to store merged result.
Limitations:
- High space complexity due to storing the entire merged array.
- Unnecessary work since we only need the k-th element.

----------------------------------------
Approach 2: Better (Counter-Based Merge)
----------------------------------------
Logic:
- Avoid storing the merged array by using a counter to track the k-th element.
- Simulate the merge process, incrementing a counter until we reach the k-th position.
- Store the element when the counter hits k-1.

Steps:
1. Initialize counter cnt = 0 and variable ele to store the k-th element.
2. Use pointers i (for arr1) and j (for arr2) starting at 0.
3. While i < m and j < n:
   - If arr1[i] < arr2[j]:
     - If cnt == k-1, store arr1[i] in ele.
     - Increment cnt and i.
   - Else:
     - If cnt == k-1, store arr2[j] in ele.
     - Increment cnt and j.
4. Process remaining elements in arr1 or arr2, checking cnt == k-1.
5. Return ele.

Time Complexity: O(m + n)
- Still traverses both arrays to reach the k-th element.
Space Complexity: O(1)
- No extra array; only uses a few variables.
Limitations:
- Time complexity is still linear, processing more elements than necessary for large arrays.
- Not optimal for cases where k is small or arrays are unbalanced.

----------------------------------------
Approach 3: Optimal (Binary Search)
----------------------------------------
Logic:
- Use binary search to find how many elements from arr1 contribute to the left partition of size k.
- Partition both arrays such that the left partition has k elements, and the k-th element is the maximum of the left partition.
- Ensure the partition is valid by checking if the left elements are less than or equal to the right elements.

Steps:
1. Ensure arr1 is the smaller array (swap if necessary) to optimize binary search.
2. Define the left partition size as k.
3. Binary search on the range of elements from arr1 [max(0, k-n), min(k, m)]:
   - Compute mid1 (elements from arr1) and mid2 = k - mid1 (elements from arr2).
   - Calculate l1 (last element of arr1's left partition), l2 (last element of arr2's left partition), r1 (first element of arr1's right partition), r2 (first element of arr2's right partition).
   - If l1 <= r2 and l2 <= r1, the partition is valid; return max(l1, l2).
   - If l1 > r2, reduce elements from arr1 (high = mid1 - 1).
   - If l2 > r1, increase elements from arr1 (low = mid1 + 1).
4. Handle edge cases with default values (INT_MIN, INT_MAX).

Time Complexity: O(log(min(m, n)))
- Binary search on the smaller array’s range.
Space Complexity: O(1)
- Only uses a few variables.
Why Optimal:
- Logarithmic time complexity is significantly better than linear for large arrays.
- No extra space required.
- Efficiently handles all cases, including unbalanced arrays or extreme k values.

*/

// ==============================================================================
// Section 3: Code Implementation
// ==============================================================================

// Approach 1: Brute Force (Merge Arrays)
int kthElementBrute(vector<int>& arr1, vector<int>& arr2, int m, int n, int k) {
    // Input validation
    if (k < 1 || k > m + n) return -1;
    
    vector<int> merged;
    int i = 0, j = 0;
    
    // Merge arrays until one is exhausted
    while (i < m && j < n) {
        if (arr1[i] < arr2[j]) {
            merged.push_back(arr1[i++]);
        } else {
            merged.push_back(arr2[j++]);
        }
    }
    
    // Copy remaining elements from arr1
    while (i < m) {
        merged.push_back(arr1[i++]);
    }
    
    // Copy remaining elements from arr2
    while (j < n) {
        merged.push_back(arr2[j++]);
    }
    
    return merged[k - 1]; // k-th element (1-based)
}

// Approach 2: Better (Counter-Based Merge)
int kthElementBetter(vector<int>& arr1, vector<int>& arr2, int m, int n, int k) {
    // Input validation
    if (k < 1 || k > m + n) return -1;
    
    int ele = -1, cnt = 0;
    int i = 0, j = 0;
    
    // Merge until k-th element is found or one array is exhausted
    while (i < m && j < n) {
        if (arr1[i] < arr2[j]) {
            if (cnt == k - 1) ele = arr1[i];
            cnt++;
            i++;
        } else {
            if (cnt == k - 1) ele = arr2[j];
            cnt++;
            j++;
        }
    }
    
    // Process remaining elements from arr1
    while (i < m) {
        if (cnt == k - 1) ele = arr1[i];
        cnt++;
        i++;
    }
    
    // Process remaining elements from arr2
    while (j < n) {
        if (cnt == k - 1) ele = arr2[j];
        cnt++;
        j++;
    }
    
    return ele;
}

// Approach 3: Optimal (Binary Search)
int kthElementOptimal(vector<int>& arr1, vector<int>& arr2, int m, int n, int k) {
    // Input validation
    if (k < 1 || k > m + n) return -1;
    
    // Ensure arr1 is the smaller array
    if (m > n) return kthElementOptimal(arr2, arr1, n, m, k);
    
    int left = k; // Size of left partition
    int low = max(0, k - n), high = min(k, m);
    
    while (low <= high) {
        int mid1 = (low + high) >> 1; // Elements from arr1
        int mid2 = left - mid1;       // Elements from arr2
        
        // Initialize boundary values
        int l1 = (mid1 - 1 >= 0) ? arr1[mid1 - 1] : INT_MIN;
        int l2 = (mid2 - 1 >= 0) ? arr2[mid2 - 1] : INT_MIN;
        int r1 = (mid1 < m) ? arr1[mid1] : INT_MAX;
        int r2 = (mid2 < n) ? arr2[mid2] : INT_MAX;
        
        // Check if partition is valid
        if (l1 <= r2 && l2 <= r1) {
            return max(l1, l2); // k-th element is max of left partition
        }
        // Adjust search range
        else if (l1 > r2) {
            high = mid1 - 1; // Take fewer elements from arr1
        } else {
            low = mid1 + 1;  // Take more elements from arr1
        }
    }
    
    return -1; // Should never reach here with valid inputs
}

// Main function to test the approaches
int main() {
    vector<int> arr1 = {2, 3, 45};
    vector<int> arr2 = {4, 6, 7, 8};
    int k = 4;
    
    // Test all approaches
    cout << "Brute Force: " << kthElementBrute(arr1, arr2, arr1.size(), arr2.size(), k) << endl;
    cout << "Better: " << kthElementBetter(arr1, arr2, arr1.size(), arr2.size(), k) << endl;
    cout << "Optimal: " << kthElementOptimal(arr1, arr2, arr1.size(), arr2.size(), k) << endl;
    
    return 0;
}