#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Section 1: Problem Statement
//==============================================================================
/*
Problem Statement:
Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order, merge them 
in sorted order without using extra space (beyond O(1)). Modify arr1 to contain the first n 
elements and arr2 to contain the last m elements of the merged array.

Example 1:
Input: n = 4, arr1[] = [1, 4, 8, 10], m = 3, arr2[] = [2, 3, 9]
Output: arr1[] = [1, 2, 3, 4], arr2[] = [8, 9, 10]
Explanation: Merged array is [1, 2, 3, 4, 8, 9, 10]. First n=4 elements go to arr1, last m=3 to arr2.

Example 2:
Input: n = 4, arr1[] = [1, 3, 5, 7], m = 5, arr2[] = [0, 2, 6, 8, 9]
Output: arr1[] = [0, 1, 2, 3], arr2[] = [5, 6, 7, 8, 9]
Explanation: Merged array is [0, 1, 2, 3, 5, 6, 7, 8, 9].

Constraints:
- 1 <= n, m <= 10^5
- 0 <= arr1[i], arr2[i] <= 10^9
- Arrays are sorted in non-decreasing order.

Edge Cases:
- n = 0 or m = 0 (one array is empty).
- One array has all smaller or all larger elements.
- Arrays have duplicate elements.
*/

//==============================================================================
// Section 2: Solution Approaches
//==============================================================================
/*
Approach 1: Brute Force (Using Extra Space)
Logic:
- Create a temporary array to merge both arrays in sorted order.
- Use two pointers to compare elements from arr1 and arr2, placing smaller elements in the temporary array.
- Copy the first n elements back to arr1 and the last m elements to arr2.

Steps:
1. Initialize a temporary array arr3 of size n+m.
2. Use two pointers (left for arr1, right for arr2) to merge elements into arr3 in sorted order.
3. If arr1[left] <= arr2[right], add arr1[left] to arr3 and increment left.
4. Otherwise, add arr2[right] to arr3 and increment right.
5. Copy remaining elements from arr1 or arr2, if any.
6. Copy first n elements from arr3 to arr1 and last m elements to arr2.

Time Complexity: O(n+m) for merging + O(n+m) for copying = O(n+m).
Space Complexity: O(n+m) for the temporary array.
Limitations: Uses extra space, violating the problem's constraint.

Approach 2: Optimal Approach 1 (Swapping + Sorting)
Logic:
- Use two pointers to swap larger elements from arr1 with smaller elements from arr2.
- After swapping, sort both arrays to ensure they are in non-decreasing order.
- This ensures arr1 contains the smallest n elements and arr2 the largest m elements.

Steps:
1. Initialize left = n-1 (last index of arr1) and right = 0 (first index of arr2).
2. While left >= 0 and right < m:
   - If arr1[left] > arr2[right], swap them and move pointers (left--, right++).
   - Else, break as no further swaps are needed (arrays are sorted).
3. Sort arr1 and arr2 to restore sorted order.

Time Complexity: O(min(n,m)) for swapping + O(n log n + m log m) for sorting = O(n log n + m log m).
Space Complexity: O(log n + log m) due to sorting (introsort stack space). Ideally, O(1) is desired, so this may not fully meet the constraint.
Limitations: Sorting introduces O(log n) space, which may violate strict O(1) space requirement.

Approach 3: Optimal Approach 2 (Gap Method)
Logic:
- Treat arr1 and arr2 as a single imaginary array and use the gap method (inspired by Shell Sort).
- Compare elements separated by a gap, swapping if out of order, and reduce the gap until it becomes 1.
- This ensures the arrays are merged in-place with arr1 containing the smallest n elements.

Steps:
1. Calculate initial gap = ceil((n+m)/2).
2. While gap >= 1:
   - Set left = 0, right = left + gap.
   - While right < n+m:
     - If left in arr1, right in arr2: Compare arr1[left] with arr2[right-n].
     - If both in arr2: Compare arr2[left-n] with arr2[right-n].
     - If both in arr1: Compare arr1[left] with arr1[right].
     - Swap if left element > right element.
     - Increment left and right.
   - Update gap = ceil(gap/2).
3. After gap = 1, arrays are merged correctly.

Time Complexity: O((n+m) * log(n+m)) as gap ranges from (n+m)/2 to 1, and each iteration processes O(n+m) elements.
Space Complexity: O(1) as only a few variables are used.
Why Optimal: Achieves true O(1) space, meeting the problem's constraint, with reasonable time complexity.

Trade-offs:
- Brute Force: Simple but uses O(n+m) space.
- Optimal 1: Reduces space but sorting adds O(log n) space and O(n log n) time.
- Optimal 2: True O(1) space, but higher time complexity due to multiple passes.
*/

//==============================================================================
// Section 3: Code Implementation
//==============================================================================

// Helper function for Gap Method to swap if first element is greater
void swapIfGreater(long long arr1[], long long arr2[], int ind1, int ind2, int n) {
    if (ind1 < n && ind2 >= n) {
        // ind1 in arr1, ind2 in arr2
        if (arr1[ind1] > arr2[ind2 - n]) {
            swap(arr1[ind1], arr2[ind2 - n]);
        }
    } else if (ind1 >= n && ind2 >= n) {
        // Both in arr2
        if (arr2[ind1 - n] > arr2[ind2 - n]) {
            swap(arr2[ind1 - n], arr2[ind2 - n]);
        }
    } else {
        // Both in arr1
        if (arr1[ind1] > arr1[ind2]) {
            swap(arr1[ind1], arr1[ind2]);
        }
    }
}

// Approach 1: Brute Force (Extra Space)
void mergeBruteForce(long long arr1[], long long arr2[], int n, int m) {
    // Temporary array to store merged elements
    vector<long long> arr3(n + m);
    int left = 0, right = 0, index = 0;

    // Merge arr1 and arr2 into arr3 in sorted order
    while (left < n && right < m) {
        if (arr1[left] <= arr2[right]) {
            arr3[index++] = arr1[left++];
        } else {
            arr3[index++] = arr2[right++];
        }
    }

    // Copy remaining elements of arr1, if any
    while (left < n) {
        arr3[index++] = arr1[left++];
    }

    // Copy remaining elements of arr2, if any
    while (right < m) {
        arr3[index++] = arr2[right++];
    }

    // Copy back to arr1 and arr2
    for (int i = 0; i < n; i++) {
        arr1[i] = arr3[i];
    }
    for (int i = 0; i < m; i++) {
        arr2[i] = arr3[n + i];
    }
}

// Approach 2: Optimal Approach 1 (Swapping + Sorting)
void mergeOptimal1(long long arr1[], long long arr2[], int n, int m) {
    // Initialize pointers: left at end of arr1, right at start of arr2
    int left = n - 1, right = 0;

    // Swap larger elements from arr1 with smaller elements from arr2
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        } else {
            break; // No more swaps needed
        }
    }

    // Sort both arrays to ensure sorted order
    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);
}

// Approach 3: Optimal Approach 2 (Gap Method)
void mergeOptimal2(long long arr1[], long long arr2[], int n, int m) {
    // Calculate initial gap
    int len = n + m;
    int gap = (len / 2) + (len % 2); // ceil(len/2)

    // Continue until gap becomes 0
    while (gap > 0) {
        int left = 0, right = gap;

        // Process elements separated by gap
        while (right < len) {
            swapIfGreater(arr1, arr2, left, right, n);
            left++;
            right++;
        }

        // Update gap for next iteration
        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2); // ceil(gap/2)
    }
}

// Main function to test the merge function
int main() {
    // Test case
    long long arr1[] = {1, 4, 8, 10};
    long long arr2[] = {2, 3, 9};
    int n = 4, m = 3;

    // Call the optimal merge function (Gap Method)
    mergeOptimal2(arr1, arr2, n, m);

    // Print the result
    cout << "The merged arrays are: " << "\n";
    cout << "arr1[] = ";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\narr2[] = ";
    for (int i = 0; i < m; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}