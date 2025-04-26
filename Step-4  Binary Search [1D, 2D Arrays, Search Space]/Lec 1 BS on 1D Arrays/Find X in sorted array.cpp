#include <vector>
using namespace std;

//==============================================================================
// Section 1: Problem Statement
//==============================================================================
/*
    Problem: Binary Search
    Given a sorted array of integers and a target value, determine if the target exists
    in the array. Return true if the target is found, false otherwise.

    Input:
    - A sorted vector<int> arr (ascending order).
    - An integer target to search for.

    Output:
    - Boolean: true if target is found, false otherwise.

    Example 1:
    Input: arr = [2, 3, 4, 10, 40], target = 10
    Output: true

    Example 2:
    Input: arr = [2, 3, 4, 10, 40], target = 5
    Output: false

    Constraints:
    - 0 <= arr.size() <= 10^5
    - -10^9 <= arr[i], target <= 10^9
    - Array is sorted in ascending order.

    Edge Cases:
    - Empty array (arr.size() == 0).
    - Single-element array.
    - Target not in array.
    - Target at the first or last index.
    - Duplicate elements (return true if any match found).
*/

//==============================================================================
// Section 2: Solution Approaches
//==============================================================================
/*
    Approach 1: Brute Force (Linear Search)
    Logic:
    - Iterate through each element in the array and check if it equals the target.
    - Since the array is sorted, we could stop early if we encounter an element greater
      than the target, but for simplicity, we check all elements.

    Steps:
    1. Loop through arr from index 0 to arr.size() - 1.
    2. If arr[i] == target, return true.
    3. If no match is found, return false.

    Time Complexity: O(n)
    - We may need to check all n elements in the worst case (target not present or at the end).
    Space Complexity: O(1)
    - Only uses a constant amount of extra space.
    Limitations:
    - Inefficient for large arrays, as it doesn't leverage the sorted property.
    - No benefit from the array being sorted.

    ---

    Approach 2: Iterative Binary Search
    Logic:
    - Use the sorted property to divide the search space in half each step.
    - Maintain two pointers, low and high, to define the current search range.
    - Compute the middle index and compare arr[mid] with the target.
    - Adjust the range based on the comparison (search left or right half).

    Steps:
    1. Initialize low = 0, high = arr.size() - 1.
    2. While low <= high:
       a. Compute mid = (low + high) / 2.
       b. If arr[mid] == target, return true.
       c. If arr[mid] > target, set high = mid - 1 (search left).
       d. If arr[mid] < target, set low = mid + 1 (search right).
    3. Return false if the loop ends (target not found).

    Time Complexity: O(log n)
    - The search space is halved each iteration, leading to logarithmic time.
    Space Complexity: O(1)
    - Only uses a constant amount of extra space for pointers.
    Limitations:
    - Requires the array to be sorted.
    - Iterative approach may be less intuitive for some recursive problems.

    ---

    Approach 3: Recursive Binary Search (Optimal)
    Logic:
    - Similar to iterative binary search, but uses recursion to divide the search space.
    - Each recursive call narrows the search range by adjusting low or high based on the
      comparison at the middle index.
    - Base case: if low > high, the target is not found.

    Steps:
    1. Base case: If low > high, return false.
    2. Compute mid = (low + high) / 2.
    3. If arr[mid] == target, return true.
    4. If arr[mid] > target, recurse on left half (low, mid - 1).
    5. If arr[mid] < target, recurse on right half (mid + 1, high).

    Time Complexity: O(log n)
    - Each recursive call halves the search space, similar to iterative.
    Space Complexity: O(log n)
    - Recursive call stack can grow to log n depth in the worst case.
    Limitations:
    - Recursive approach uses more stack space compared to iterative.
    - May cause stack overflow for extremely large arrays (rare with given constraints).

    Why Optimal?
    - Both iterative and recursive binary search achieve O(log n) time, but recursive is
      often preferred for its elegance and clarity in expressing the divide-and-conquer
      paradigm. The iterative approach is slightly more space-efficient (O(1) vs O(log n)),
      but the recursive version is included here as per the user's implementation.
    - For most practical array sizes (up to 10^5), the recursive stack depth is manageable.
*/

//==============================================================================
// Section 3: Code Implementation
//==============================================================================

// Brute Force: Linear Search
bool binarySearchBruteForce(const vector<int>& arr, int target) {
    // Handle empty array edge case
    if (arr.empty()) {
        return false;
    }
    // Iterate through each element
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return true; // Target found
        }
        // Optimization: Since array is sorted, stop if current element exceeds target
        if (arr[i] > target) {
            break;
        }
    }
    return false; // Target not found
}

// Iterative Binary Search
bool binarySearchIterative(const vector<int>& arr, int target) {
    // Handle empty array edge case
    if (arr.empty()) {
        return false;
    }
    int low = 0;
    int high = arr.size() - 1;
    // Continue while search range is valid
    while (low <= high) {
        // Compute middle index (avoid overflow with low + (high - low) / 2)
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return true; // Target found
        }
        else if (arr[mid] > target) {
            high = mid - 1; // Search left half
        }
        else {
            low = mid + 1; // Search right half
        }
    }
    return false; // Target not found
}

// Recursive Binary Search
bool binarySearchRecursive(const vector<int>& arr, int low, int high, int target) {
    // Base case: invalid search range
    if (low > high) {
        return false;
    }
    // Compute middle index (avoid overflow)
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        return true; // Target found
    }
    else if (arr[mid] > target) {
        // Recurse on left half
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
    else {
        // Recurse on right half
        return binarySearchRecursive(arr, mid + 1, high, target);
    }
}

// Wrapper function to simplify recursive call
bool binarySearch(const vector<int>& arr, int target) {
    // Handle empty array edge case
    if (arr.empty()) {
        return false;
    }
    return binarySearchRecursive(arr, 0, arr.size() - 1, target);
}

int main() {
    // Example input
    vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;

    // Test recursive binary search
    bool result = binarySearch(arr, target);
    return result; // Returns true (1) for target = 10

    // For testing other approaches, uncomment below:
    // bool resultBrute = binarySearchBruteForce(arr, target);
    // bool resultIterative = binarySearchIterative(arr, target);
}
