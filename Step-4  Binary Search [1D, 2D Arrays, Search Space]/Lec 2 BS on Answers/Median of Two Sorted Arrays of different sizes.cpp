
/*==============================================================================
Section 1: Problem Statement
==============================================================================
Median of Two Sorted Arrays
Given two sorted arrays arr1 and arr2 of size m and n respectively, return the
median of the two sorted arrays. The median is defined as the middle value of a
sorted list of numbers. In case the length of the list is even, the median is the
average of the two middle elements.

Example 1:
Input: n1 = 3, arr1[] = {2,4,6}, n2 = 3, arr2[] = {1,3,5}
Output: 3.5
Explanation: The merged array is {1,2,3,4,5,6}. The median is the average of 3
and 4, which is 3.5.

Example 2:
Input: n1 = 3, arr1[] = {2,4,6}, n2 = 2, arr2[] = {1,3}
Output: 3
Explanation: The merged array is {1,2,3,4,6}. The median is 3.

Constraints:
- 0 <= m, n <= 10^4
- 1 <= m + n <= 2*10^4
- -10^6 <= arr1[i], arr2[i] <= 10^6

Edge Cases:
- One or both arrays empty (e.g., arr1 = {}, arr2 = {1}).
- Single element total (m + n = 1).
- Arrays of different sizes.
- Odd or even total length of merged array.
*/

/*==============================================================================
Section 2: Observations
==============================================================================
Observations provide a mental roadmap for solving the Median of Two Sorted Arrays:
1. Problem Nature: The goal is to find the median of the merged sorted array without
   necessarily merging it, as this can be inefficient for large arrays.
2. Median Definition:
   - For odd total length (m+n), the median is the middle element.
   - For even total length, it’s the average of the two middle elements.
3. Sorted Arrays: Since both arrays are sorted, we can leverage their order to avoid
   sorting a merged array, using either merging or binary search techniques.
4. Key Insight: The median lies at position (m+n)/2 (or average of (m+n)/2 and
   (m+n)/2-1 for even length). We only need these elements, not the full merged array.
5. Partitioning Insight: The median divides the merged array into two equal halves.
   We can find a partition in both arrays such that the left half contains elements
   <= right half, ensuring a sorted merged array.
6. Range of Elements: Elements can be negative or large ([-10^6, 10^6]), but this
   doesn’t affect the logic since we compare relative values.
7. Edge Cases:
   - Empty array(s): If one array is empty, the median comes from the non-empty array.
   - Single element: If m+n=1, return the only element.
   - Different sizes: The solution must handle m != n.
8. Pattern: The problem resembles finding the k-th smallest element in two sorted
   arrays, suggesting binary search on the smaller array to minimize comparisons.

These observations suggest three approaches: brute force (merge and find median),
better (merge only up to median), and optimal (binary search on partitions).
*/

/*==============================================================================
Section 2: Solution Approaches
==============================================================================

==============================================================================
Approach 1: Brute Force (Merge and Find Median)
==============================================================================


Logic:
- Merge the two sorted arrays into a single sorted array using a merge-sort-like
  process.
- Find the median based on the total length:
  - Odd: Element at index (n1+n2)/2.
  - Even: Average of elements at (n1+n2)/2 and (n1+n2)/2-1.
Steps:
1. Create a vector to store the merged array.
2. Use two pointers to merge arr1 and arr2 into the vector in sorted order.
3. Copy any remaining elements from either array.
4. Compute median: If n1+n2 is odd, return middle element; if even, average the two
   middle elements.
Time Complexity: O(n1 + n2)
- Merging takes O(n1 + n2).
- Median calculation is O(1).
Space Complexity: O(n1 + n2)
- Merged array requires O(n1 + n2) space.
Limitations:
- High space usage due to storing the full merged array.
- Unnecessary work merging elements beyond the median position.
Trade-offs:
- Simple to implement but inefficient for large arrays.


==============================================================================
Approach 2: Better (Merge Only Up to Median)
==============================================================================

Logic:
- Instead of merging the entire arrays, only merge up to the median position(s)
  ((n1+n2)/2 or (n1+n2)/2-1).
- Use a counter to track the position in the merged sequence and store only the
  median elements.
- This avoids storing the full merged array, reducing space complexity.
Steps:
1. Calculate median indices: ind1 = (n1+n2)/2, ind2 = (n1+n2)/2-1 (for even length).
2. Use two pointers to merge elements from arr1 and arr2, incrementing a counter.
3. Store elements when counter hits ind1 or ind2.
4. Process remaining elements from either array if needed.
5. Compute median: If odd, return ind1 element; if even, average ind1 and ind2 elements.
Time Complexity: O((n1 + n2)/2) = O(n1 + n2)
- Merging stops at the median position, taking at most (n1+n2)/2 iterations.
Space Complexity: O(1)
- Only stores two elements (ind1el, ind2el) and a few variables.
Why Better:
- Eliminates the need for a merged array, reducing space to constant.
Limitations:
- Still linear time, processing up to half the elements.
Trade-offs:
- More complex than brute force but saves significant space.


==============================================================================
Approach 3: Optimal (Binary Search on Partitions)
==============================================================================

Logic:
- The median divides the merged sorted array into two equal halves (or nearly equal for odd lengths).
- Instead of merging arrays, partition both arr1 and arr2 such that the left half of the merged array has (n1+n2+1)/2 elements.
- Ensure left half elements are <= right half elements, maintaining sorted order.
- Use binary search on the smaller array to find the correct partition point, minimizing iterations.
- For a partition, check boundary elements (l1, l2, r1, r2) to validate sortedness.
- Compute median from boundary elements: max(l1, l2) for odd, or average of max(l1, l2) and min(r1, r2) for even.

Detailed Explanation:
- Let n1 = size of arr1, n2 = size of arr2, n = n1 + n2.
- The left half needs (n+1)/2 elements (works for both odd and even due to integer division).
- Take x elements from arr1 and y = (n+1)/2 - x elements from arr2 for the left half.
- Binary search on x in [0, n1] to find the correct partition.
- For x = mid1 from arr1, compute mid2 = (n+1)/2 - mid1 from arr2.
- Boundary elements:
  - l1: Max element from arr1's left half (arr1[mid1-1] or INT_MIN if mid1=0).
  - l2: Max element from arr2's left half (arr2[mid2-1] or INT_MIN if mid2=0).
  - r1: Min element from arr1's right half (arr1[mid1] or INT_MAX if mid1=n1).
  - r2: Min element from arr2's right half (arr2[mid2] or INT_MAX if mid2=n2).
- Partition is valid if l1 <= r2 and l2 <= r1 (ensures merged array is sorted).
- If valid:
  - Odd length: Median = max(l1, l2).
  - Even length: Median = (max(l1, l2) + min(r1, r2)) / 2.
- If l1 > r2, too many elements from arr1; reduce x (search left half).
- If l2 > r1, too few elements from arr1; increase x (search right half).
- Use smaller array for binary search to minimize range (O(log(min(n1, n2)))).
- Edge cases:
  - Empty arrays: If one is empty, median comes from the other.
  - Single element: If n1+n2=1, return the only element.
  - Boundary conditions: Use INT_MIN/INT_MAX for partitions at edges.
- Example: arr1={2,4,6}, arr2={1,3,5}, n=6, left=(6+1)/2=4.
  - Try x=2: mid1=2, mid2=4-2=2.
  - l1=arr1[1]=4, l2=arr2[1]=3, r1=arr1[2]=6, r2=arr2[2]=5.
  - Check: l1<=r2 (4<=5), l2<=r1 (3<=6). Valid.
  - Even: Median = (max(4,3) + min(6,5)) / 2 = (4+5)/2 = 4.5.

Time Complexity: O(log(min(n1, n2)))
- Binary search on smaller array takes O(log(min(n1, n2))) iterations.
- Each iteration performs O(1) operations (comparisons, calculations).
Space Complexity: O(1)
- Only uses a few integer variables (mid1, mid2, l1, l2, r1, r2).
*/
#include <bits/stdc++.h>
using namespace std;

/*==============================================================================
Section 3: Code Implementation
==============================================================================
/* Brute Force: Merge and Find Median */
double medianBrute(const vector<int>& a, const vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    /* Check if both arrays are empty */
    if (n1 == 0 && n2 == 0) return 0.0;
    
    vector<int> merged;
    merged.reserve(n1 + n2); /* Preallocate space */
    int i = 0, j = 0;
    
    /* Merge arrays in sorted order */
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) {
            merged.push_back(a[i++]);
        } else {
            merged.push_back(b[j++]);
        }
    }
    
    /* Copy remaining elements from a */
    while (i < n1) {
        merged.push_back(a[i++]);
    }
    
    /* Copy remaining elements from b */
    while (j < n2) {
        merged.push_back(b[j++]);
    }
    
    int n = n1 + n2;
    /* Odd length: return middle element */
    if (n % 2 == 1) {
        return (double)merged[n / 2];
    }
    /* Even length: average of two middle elements */
    return ((double)merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

/* Better: Merge Only Up to Median */
double medianBetter(const vector<int>& a, const vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    int n = n1 + n2;
    
    /* Check if both arrays are empty */
    if (n == 0) return 0.0;
    
    int ind1 = n / 2; /* Index of median (or second median for even) */
    int ind2 = (n % 2 == 0) ? n / 2 - 1 : -1; /* First median for even */
    int i = 0, j = 0, cnt = 0;
    int ind1el = -1, ind2el = -1;
    
    /* Merge until median position(s) */
    while (i < n1 && j < n2 && cnt <= ind1) {
        if (a[i] <= b[j]) {
            if (cnt == ind1) ind1el = a[i];
            if (cnt == ind2) ind2el = a[i];
            cnt++;
            i++;
        } else {
            if (cnt == ind1) ind1el = b[j];
            if (cnt == ind2) ind2el = b[j];
            cnt++;
            j++;
        }
    }
    
    /* Process remaining elements from a */
    while (i < n1 && cnt <= ind1) {
        if (cnt == ind1) ind1el = a[i];
        if (cnt == ind2) ind2el = a[i];
        cnt++;
        i++;
    }
    
    /* Process remaining elements from b */
    while (j < n2 && cnt <= ind1) {
        if (cnt == ind1) ind1el = b[j];
        if (cnt == ind2) ind2el = b[j];
        cnt++;
        j++;
    }
    
    /* Odd length: return middle element */
    if (n % 2 == 1) {
        return (double)ind1el;
    }
    /* Even length: average of two middle elements */
    return (ind1el + ind2el) / 2.0;
}

/* Optimal: Binary Search on Partitions */
double medianOptimal(const vector<int>& a, const vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    /* Ensure a is the smaller array */
    if (n1 > n2) return medianOptimal(b, a);
    
    int n = n1 + n2;
    /* Check if both arrays are empty */
    if (n == 0) return 0.0;
    
    int left = (n + 1) / 2; /* Length of left half */
    int low = 0, high = n1;
    
    while (low <= high) {
        int mid1 = (low + high) / 2; /* Elements from a */
        int mid2 = left - mid1; /* Elements from b */
        
        /* Boundary elements */
        int l1 = (mid1 == 0) ? INT_MIN : a[mid1 - 1];
        int l2 = (mid2 == 0) ? INT_MIN : b[mid2 - 1];
        int r1 = (mid1 == n1) ? INT_MAX : a[mid1];
        int r2 = (mid2 == n2) ? INT_MAX : b[mid2];
        
        /* Valid partition found */
        if (l1 <= r2 && l2 <= r1) {
            if (n % 2 == 1) {
                return (double)max(l1, l2); /* Odd: max of left */
            }
            return (max(l1, l2) + min(r1, r2)) / 2.0; /* Even: average */
        }
        /* Adjust search range */
        else if (l1 > r2) {
            high = mid1 - 1; /* Take fewer from a */
        } else {
            low = mid1 + 1; /* Take more from a */
        }
    }
    
    return 0.0; /* Dummy return, should not reach */
}

/*==============================================================================
Section 4: Main Function
==============================================================================
*/
int main() {
    vector<int> a = {2, 4, 6};
    vector<int> b = {1, 3, 5};
    
    /* Test Brute Force */
    cout << "Brute Force: " << fixed << setprecision(1)
         << medianBrute(a, b) << endl;
    
    /* Test Better */
    cout << "Better: " << fixed << setprecision(1)
         << medianBetter(a, b) << endl;
    
    /* Test Optimal */
    cout << "Optimal: " << fixed << setprecision(1)
         << medianOptimal(a, b) << endl;
    
    /* Additional test case */
    vector<int> c = {2, 4, 6};
    vector<int> d = {1, 3};
    cout << "Optimal (Test Case 2): " << fixed << setprecision(1)
         << medianOptimal(c, d) << endl;
    
    return 0;
}
