#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem Statement:
Given an array of N integers. Every number in the array except one appears twice. 
Find the single number in the array.

Example 1:
Input Format: arr[] = {1,1,2,2,3,3,4,5,5,6,6}
Result: 4
Explanation: Only the number 4 appears once in the array.

Example 2:
Input Format: arr[] = {1,1,3,5,5}
Result: 3
Explanation: Only the number 3 appears once in the array.

Edge Case:
- If the array has only one element, return that element.
- Handle arrays of any size and the case where elements are sorted.
============================================================================== 
Section 2: Solution Approaches 
============================================================================== 

============================================================================== 
Approach 1: Naive Approach (Brute force): 
============================================================================== 
- Traverse the array and check if an element is different from both its adjacent elements. 
- If such an element is found, return it as the unique element. 
- Time Complexity: O(N), as we traverse the entire array. 
- Space Complexity: O(1), as we do not use extra space. 

============================================================================== 
Approach 2: Using XOR: 
============================================================================== 
- XOR all elements of the array. 
- Due to the properties of XOR, duplicate elements cancel each other out and the result will be the single unique element. 
- Time Complexity: O(N), as we traverse the array. 
- Space Complexity: O(1), as we only use a single variable to store the result. 

============================================================================== 
Approach 3: Optimal Approach (Using Binary Search) 
============================================================================== 
The optimal solution uses Binary Search to reduce the search space and find the single element in a sorted, rotated array where every element except one appears twice. 

We leverage the fact that the array is sorted and that pairs of elements always appear adjacent to each other. Here's a step-by-step explanation of the algorithm:

**Intuition:**
- **Binary Search**: We will apply a binary search to the array. The binary search efficiently reduces the problem size by half with each iteration.
  
- **Unique Element**: The goal is to find the single element that does not have a pair. We use the fact that pairs of elements occur next to each other (either at even-odd or odd-even indices) in the array.

**How the Binary Search Algorithm Works for this Problem:**

**Step 1: Edge Case Handling**
- If the array has only one element (n == 1), that element is obviously the unique one. So, return it directly.
- If the first element is different from the second element (arr[0] != arr[1]), then the first element is the unique element.
- Similarly, if the last element is different from the second last element (arr[n-1] != arr[n-2]), the last element is the unique one.

**Step 2: Apply Binary Search**
- **Low and High pointers**: We maintain two pointers: low (initially set to 1) and high (initially set to n-2). The indices 0 and n-1 are handled as edge cases before we start the binary search.
- **Midpoint Calculation**: We calculate mid as `(low + high) / 2`. This is the index of the element we will examine in each iteration of binary search.

**Step 3: Check if the Mid Element is the Unique Element**
- If the element at mid is not equal to its adjacent elements (`arr[mid] != arr[mid-1]` and `arr[mid] != arr[mid+1]`), then `arr[mid]` is the unique element, and we can return it.

**Step 4: Identifying the Halves**
- **Left Half**: If we are in the left half, the sequence of numbers will be in pairs, meaning:
  - If mid is even, the next element `arr[mid+1]` will be the same as `arr[mid]`.
  - If mid is odd, the previous element `arr[mid-1]` will be the same as `arr[mid]`.
  - In this case, the single element must be on the right side, so we set `low = mid + 1` to search in the right half.

- **Right Half**: If we are in the right half, the sequence of numbers will also be in pairs, but:
  - If mid is even, the previous element `arr[mid-1]` will be the same as `arr[mid]`.
  - If mid is odd, the next element `arr[mid+1]` will be the same as `arr[mid]`.
  - In this case, the single element must be on the left side, so we set `high = mid - 1` to search in the left half.

**Step 5: Repeat**
- This process continues until we find the unique element or narrow the search space down to a single element.

- **Time Complexity**: O(log N), as binary search reduces the problem size by half in each iteration.
- **Space Complexity**: O(1), as we use only a few extra variables for indices and the result.


==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Naive Approach (Brute Force)
int findSingleElementNaive(vector<int>& arr) {
    int n = arr.size();

    // Edge case for a single element array
    if (n == 1) return arr[0];

    for (int i = 0; i < n; i++) {
        // Check if the current element is unique by comparing it with adjacent elements
        if ((i == 0 && arr[i] != arr[i + 1]) || 
            (i == n - 1 && arr[i] != arr[i - 1]) ||
            (i > 0 && i < n - 1 && arr[i] != arr[i - 1] && arr[i] != arr[i + 1])) {
            return arr[i];
        }
    }

    return -1;  // In case of an error, but this should not happen
}

// Approach 2: Using XOR
int findSingleElementXOR(vector<int>& arr) {
    int result = 0;
    for (int num : arr) {
        result ^= num;  // XOR all the numbers
    }
    return result;
}

// Approach 3: Optimal Approach (Using Binary Search)
int findSingleElement(vector<int>& arr) {
    int n = arr.size();

    // Edge cases
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = (low + high) / 2;

        // Check if mid is the single element
        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) {
            return arr[mid];
        }

        // Check if we are in the left half of the array
        if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) || (mid % 2 == 1 && arr[mid] == arr[mid - 1])) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Just in case something goes wrong
}

int main() {
    vector<int> arr1 = {1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6};
    vector<int> arr2 = {1, 1, 3, 5, 5};
    
    // Test Approach 1: Naive Approach (Brute Force)
    cout << "Single element in arr1 (Naive): " << findSingleElementNaive(arr1) << endl;
    cout << "Single element in arr2 (Naive): " << findSingleElementNaive(arr2) << endl;

    // Test Approach 2: XOR Approach
    cout << "Single element in arr1 (XOR): " << findSingleElementXOR(arr1) << endl;
    cout << "Single element in arr2 (XOR): " << findSingleElementXOR(arr2) << endl;

    // Test Approach 3: Binary Search Approach
    cout << "Single element in arr1 (Binary Search): " << findSingleElement(arr1) << endl;
    cout << "Single element in arr2 (Binary Search): " << findSingleElement(arr2) << endl;

    return 0;
}
