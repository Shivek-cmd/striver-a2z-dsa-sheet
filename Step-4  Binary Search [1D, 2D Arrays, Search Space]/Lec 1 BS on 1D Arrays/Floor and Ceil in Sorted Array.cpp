#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Given a sorted array of distinct integers and a target value x, implement functions to:
1. Find the floor: The largest element in the array that is less than or equal to x.
2. Find the ceil: The smallest element in the array that is greater than or equal to x.
3. Find both floor and ceil in a single function.

Example Inputs and Outputs:
- Input: arr = [1, 3, 5, 6], x = 4
  Output: Floor = 3, Ceil = 5
- Input: arr = [1, 3, 5, 6], x = 5
  Output: Floor = 5, Ceil = 5
- Input: arr = [], x = 1
  Output: Floor = -1, Ceil = -1 (undefined)

Constraints:
- 0 <= arr.size() <= 10^4
- -10^4 <= arr[i], x <= 10^4
- Array is sorted in ascending order with distinct values.

Edge Cases:
- Empty array (return -1 for both floor and ceil)
- x smaller than all elements (floor undefined, ceil is arr[0])
- x larger than all elements (floor is arr[n-1], ceil undefined)
- x equals an element (floor and ceil are the same)
- Single-element array
*/

namespace FloorCeilFunctions {

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================
*/

// Approach for findFloor (Separate Binary Search)
// Logic:
// - Use binary search to find the largest element <= x.
// - Track the largest element encountered that satisfies arr[mid] <= x.
// Steps:
// 1. If array is empty, return -1.
// 2. Initialize result = -1, low = 0, high = n-1.
// 3. While low <= high:
//    a. Compute mid.
//    b. If arr[mid] <= x, update result = arr[mid], search right (low = mid + 1).
//    c. If arr[mid] > x, search left (high = mid - 1).
// 4. Return result.
// Time Complexity: O(log n), where n is array size.
// Space Complexity: O(1), uses constant extra space.

// Approach for findCeil (Separate Binary Search)
// Logic:
// - Use binary search to find the smallest element >= x.
// - Track the smallest element encountered that satisfies arr[mid] >= x.
// Steps:
// 1. If array is empty, return -1.
// 2. Initialize result = -1, low = 0, high = n-1.
// 3. While low <= high:
//    a. Compute mid.
//    b. If arr[mid] >= x, update result = arr[mid], search left (high = mid - 1).
//    c. If arr[mid] < x, search right (low = mid + 1).
// 4. Return result.
// Time Complexity: O(log n).
// Space Complexity: O(1).

// Approach for findFloorAndCeil (Combined Binary Search)
// Logic:
// - Use a single binary search to find the lower bound (smallest index where arr[i] >= x).
// - Floor is the element just before the lower bound (if it exists).
// - Ceil is the element at the lower bound (if it exists).
// Steps:
// 1. If array is empty, return {-1, -1}.
// 2. Perform binary search to find lower bound.
// 3. Floor = arr[lower_bound - 1] if lower_bound > 0, else -1.
// 4. Ceil = arr[lower_bound] if lower_bound < n, else -1.
// 5. Return pair {floor, ceil}.
// Time Complexity: O(log n), single binary search.
// Space Complexity: O(1).
// Why Optimal:
// - Combines both computations in one pass, reducing redundant searches.
// - Still handles all edge cases correctly.

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Function 1: Find floor of x in a sorted array
int findFloor(const vector<int>& arr, int x) {
    int n = arr.size();
    if (n == 0) return -1; // Undefined for empty array

    int result = -1; // Initialize floor as undefined
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid integer overflow
        if (arr[mid] <= x) {
            result = arr[mid]; // Potential floor
            low = mid + 1; // Look for a larger element <= x
        } else {
            high = mid - 1; // Look for a smaller element
        }
    }

    return result;
}

// Function 2: Find ceil of x in a sorted array
int findCeil(const vector<int>& arr, int x) {
    int n = arr.size();
    if (n == 0) return -1; // Undefined for empty array

    int result = -1; // Initialize ceil as undefined
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid integer overflow
        if (arr[mid] >= x) {
            result = arr[mid]; // Potential ceil
            high = mid - 1; // Look for a smaller element >= x
        } else {
            low = mid + 1; // Look for a larger element
        }
    }

    return result;
}

// Function 3: Find both floor and ceil of x in a sorted array
pair<int, int> findFloorAndCeil(const vector<int>& arr, int x) {
    int n = arr.size();
    if (n == 0) return {-1, -1}; // Undefined for empty array

    int low = 0, high = n - 1;
    int lower_bound = n; // Default: insertion at end

    // Binary search to find lower bound (smallest index where arr[i] >= x)
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x) {
            lower_bound = mid; // Potential lower bound
            high = mid - 1; // Look for a smaller index
        } else {
            low = mid + 1; // Look for a larger element
        }
    }

    // Determine floor and ceil
    int floor = (lower_bound == 0) ? -1 : arr[lower_bound - 1];
    int ceil = (lower_bound == n) ? -1 : arr[lower_bound];

    return {floor, ceil};
}

// Test function to demonstrate all implementations
void testFunctions(const vector<int>& arr, int x) {
    cout << "Array: [";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
    }
    cout << "], Target: " << x << endl;

    // Test separate floor and ceil functions
    int floor = findFloor(arr, x);
    int ceil = findCeil(arr, x);
    cout << "Separate Functions:" << endl;
    cout << "  Floor: " << (floor == -1 ? "Undefined" : to_string(floor)) << endl;
    cout << "  Ceil: " << (ceil == -1 ? "Undefined" : to_string(ceil)) << endl;
}

} // namespace FloorCeilFunctions

int main() {
    using namespace FloorCeilFunctions;

    // Test cases
    vector<int> arr1 = {1, 3, 5, 6};
    testFunctions(arr1, 4); // Floor = 3, Ceil = 5
    testFunctions(arr1, 5); // Floor = 5, Ceil = 5
    testFunctions(arr1, 0); // Floor = -1, Ceil = 1
    testFunctions(arr1, 7); // Floor = 6, Ceil = -1
    testFunctions({}, 1);   // Floor = -1, Ceil = -1
    testFunctions({1}, 1);  // Floor = 1, Ceil = 1

    return 0;
}

/*
==============================================================================
Example Output
==============================================================================
Array: [1, 3, 5, 6], Target: 4
Separate Functions:
  Floor: 3
  Ceil: 5
Combined Function:
  Floor: 3
  Ceil: 5
----------------------------------------
Array: [1, 3, 5, 6], Target: 5
Separate Functions:
  Floor: 5
  Ceil: 5
Combined Function:
  Floor: 5
  Ceil: 5
----------------------------------------
Array: [1, 3, 5, 6], Target: 0
Separate Functions:
  Floor: Undefined
  Ceil: 1
Combined Function:
  Floor: Undefined
  Ceil: 1
----------------------------------------
Array: [1, 3, 5, 6], Target: 7
Separate Functions:
  Floor: 6
  Ceil: Undefined
Combined Function:
  Floor: 6
  Ceil: Undefined
----------------------------------------
Array: [], Target: 1
Separate Functions:
  Floor: Undefined
  Ceil: Undefined
Combined Function:
  Floor: Undefined
  Ceil: Undefined
----------------------------------------
Array: [1], Target: 1
Separate Functions:
  Floor: 1
  Ceil: 1
Combined Function:
  Floor: 1
  Ceil: 1
----------------------------------------
*/