#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem Statement:
Given an array of length N. Peak element is defined as the element greater than both of its neighbors. 
Formally, if 'arr[i]' is the peak element, 'arr[i - 1]' < 'arr[i]' and 'arr[i + 1]' < 'arr[i]'.
Find the index (0-based) of a peak element in the array. If there are multiple peak numbers, return the index of any peak number.

Note: For the first element, the previous element should be considered as negative infinity as well as for the last element, the next element should be considered as negative infinity.

Example 1:
Input Format: arr[] = {1,2,3,4,5,6,7,8,5,1}
Result: 7
Explanation: In this example, there is only 1 peak that is at index 7.

Example 2:
Input Format: arr[] = {1,2,1,3,5,6,4}
Result: 1
Explanation: In this example, there are 2 peak numbers that are at indices 1 and 5. We can consider any of them.

Example 3:
Input Format: arr[] = {1, 2, 3, 4, 5}
Result: 4
Explanation: In this example, there is only 1 peak that is at the index 4.

Example 4:
Input Format: arr[] = {5, 4, 3, 2, 1}
Result: 0
Explanation: In this example, there is only 1 peak that is at the index 0.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

Approach 1: Naive Approach (Brute force):
==============================================================================
- Traverse the array and check if an element is different from both its adjacent elements.
- If such an element is found, return it as the unique element.
- Time Complexity: O(N), as we traverse the entire array.
- Space Complexity: O(1), as we do not use any extra space.


============================================================================== 
Approach 2: Optimal Approach (Using Binary Search):
==============================================================================

The optimal solution uses Binary Search to reduce the search space and find the single peak element in an array where every element except one appears twice.

**Intuition:**
- The **primary goal** is to use Binary Search to reduce the search space by half with each iteration.
- **Peak Element**: A peak element is an element that is greater than both its neighbors. If such an element is found, it is the desired peak.
- By leveraging Binary Search, we can efficiently reduce the problem size at each step and find the peak element.

**How Binary Search Works for this Problem:**

### Step 1: Edge Case Handling
- If the array has only one element (`n == 1`), that element is the peak.
- If the first element is greater than the second element (`arr[0] > arr[1]`), then the first element is the peak element.
- Similarly, if the last element is greater than the second last element (`arr[n-1] > arr[n-2]`), the last element is the peak.

### Step 2: Apply Binary Search
- **Low and High pointers**: Set `low = 1` and `high = n - 2`, excluding the first and last elements, as they are already handled in the edge cases.
- **Midpoint Calculation**: Calculate `mid = (low + high) / 2`. This `mid` is the index of the element we will examine in each iteration of binary search.

### Step 3: Check if the Mid Element is the Peak Element
- If `arr[mid] > arr[mid - 1]` and `arr[mid] > arr[mid + 1]`, then `arr[mid]` is the peak element, and we return `mid`.

### Step 4: Identifying the Halves
By observing the array structure, we can deduce the following:
- **Left Half**: If we are in the left half of the peak element (the sequence of elements is increasing), we eliminate the left half.
    - If `arr[mid] > arr[mid - 1]`, the peak element lies in the right half, so we set `low = mid + 1`.
    
- **Right Half**: If we are in the right half of the peak element (the sequence of elements is decreasing), we eliminate the right half.
    - If `arr[mid] < arr[mid + 1]`, the peak element lies in the left half, so we set `high = mid - 1`.

### Step 5: Repeat Until the Peak is Found
- The process continues by halving the search space (`low` to `mid+1` or `high` to `mid-1`) until the peak element is found.

### Handling Multiple Peaks:
- In cases where there are multiple peaks, the algorithm will return **any one** of the peaks. This is because there can be more than one valid peak element in the array, and Binary Search ensures the first peak it encounters is returned.

### **Algorithm:**

1. **Edge Cases**:
   - If `n == 1`, return the only element.
   - If `arr[0] > arr[1]`, return `0`.
   - If `arr[n-1] > arr[n-2]`, return `n-1`.
2. **Binary Search**:
   - Set `low = 1` and `high = n-2`.
   - Loop while `low <= high`:
     - Calculate `mid = (low + high) / 2`.
     - If `arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1]`, return `mid`.
     - If `arr[mid] > arr[mid-1]`, set `low = mid + 1` (eliminate left half).
     - Otherwise, set `high = mid - 1` (eliminate right half).

### **Time Complexity**:
- **O(log N)**: Binary Search reduces the search space by half each time, making it much faster than a linear search.

### **Space Complexity**:
- **O(1)**: No extra space is used, aside from a few variables for pointers and midpoint calculations.

==============================================================================
*/


/*
==============================================================================
Section 3: Code Implementation
============================================================================== 
*/

// Function signature for the Naive Approach
int findPeakElementNaive(vector<int> &arr) {
    int n = arr.size();
    
    // Edge case: If the array has only one element
    if (n == 1) return 0;

    // Traverse the array and check the condition for peak
    for (int i = 0; i < n; i++) {
        if ((i == 0 || arr[i-1] < arr[i]) && (i == n-1 || arr[i] > arr[i+1])) {
            return i;  // Return the index of the peak element
        }
    }

    return -1;  // This should not be reached if the input follows the problem's constraints
}

// Function signature for the Binary Search Approach
int findPeakElementBinarySearch(vector<int>& arr) {
    int n = arr.size();

    // Edge cases
    if (n == 1) return 0;  // Single element
    if (arr[0] > arr[1]) return 0;  // Peak is at the first element
    if (arr[n - 1] > arr[n - 2]) return n - 1;  // Peak is at the last element

    // Apply binary search
    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = (low + high) / 2;

        // Check if mid is the peak element
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
        }

        // If we are in the left half
        if (arr[mid] > arr[mid - 1]) {
            low = mid + 1;
        } 
        // If we are in the right half
        else {
            high = mid - 1;
        }
    }

    return -1;  // This should not be reached if the input follows the problem's constraints
}

int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 5, 1};
    vector<int> arr2 = {1, 2, 1, 3, 5, 6, 4};
    vector<int> arr3 = {1, 2, 3, 4, 5};
    vector<int> arr4 = {5, 4, 3, 2, 1};
    
    // Test the Naive Approach
    cout << "Peak element in arr1 (Naive): " << findPeakElementNaive(arr1) << endl;
    cout << "Peak element in arr2 (Naive): " << findPeakElementNaive(arr2) << endl;
    cout << "Peak element in arr3 (Naive): " << findPeakElementNaive(arr3) << endl;
    cout << "Peak element in arr4 (Naive): " << findPeakElementNaive(arr4) << endl;

    // Test the Binary Search Approach
    cout << "Peak element in arr1 (Binary Search): " << findPeakElementBinarySearch(arr1) << endl;
    cout << "Peak element in arr2 (Binary Search): " << findPeakElementBinarySearch(arr2) << endl;
    cout << "Peak element in arr3 (Binary Search): " << findPeakElementBinarySearch(arr3) << endl;
    cout << "Peak element in arr4 (Binary Search): " << findPeakElementBinarySearch(arr4) << endl;

    return 0;
}
