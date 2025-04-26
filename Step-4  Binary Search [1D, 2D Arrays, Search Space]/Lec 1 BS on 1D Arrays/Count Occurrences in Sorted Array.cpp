#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem:
    You are given a **sorted array** containing **N integers** and a number **X**. 
    You have to find the **number of occurrences** of **X** in the given array.

Examples:
    Example 1:
        Input: N = 7, X = 3, array[] = {2, 2, 3, 3, 3, 3, 4}
        Output: 4
        Explanation: 3 occurs 4 times.

    Example 2:
        Input: N = 8, X = 2, array[] = {1, 1, 2, 2, 2, 2, 2, 3}
        Output: 5
        Explanation: 2 occurs 5 times.

Constraints:
    - 1 <= N <= 10^5
    - -10^9 <= array[i], X <= 10^9
    - Array is sorted in non-decreasing order

Edge Cases:
    - Empty array
    - X not present in array
    - All elements same as X

==============================================================================
Section 2: Solution Approaches
==============================================================================
Approach 1: Brute Force
------------------------
Logic:
    - Traverse the array linearly.
    - Count how many times X appears.

Steps:
    1. Initialize counter = 0.
    2. Loop through all elements:
        - If element == X, increment counter.
    3. Return counter.

Time Complexity:
    - O(N)

Space Complexity:
    - O(1)

Limitations:
    - Inefficient for very large arrays as it checks every element.

------------------------------------------------------------

Approach 2: Optimal Approach (Binary Search)
---------------------------------------------
Logic:
    - Use binary search to find first and last occurrences of X.
    - Calculate count = last - first + 1.

Steps:
    1. Perform binary search for first occurrence.
    2. Perform binary search for last occurrence.
    3. Return count.

Time Complexity:
    - O(log N)

Space Complexity:
    - O(1)

Why Optimal:
    - Much faster on large sorted arrays.

==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// ================== Approach 1: Brute Force ==================
int countOccurrencesBruteForce(const vector<int>& arr, int x) {
    int count = 0;
    for (int num : arr) {
        if (num == x) {
            count++;
        }
    }
    return count;
}

// ================== Approach 2: Optimal (Binary Search) ==================
int firstOccurrence(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    int first = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x) {
            first = mid;
            high = mid - 1; // search left
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return first;
}

int lastOccurrence(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    int last = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x) {
            last = mid;
            low = mid + 1; // search right
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return last;
}

int countOccurrencesOptimal(const vector<int>& arr, int x) {
    if (arr.empty()) {
        return 0;
    }

    int first = firstOccurrence(arr, x);
    int last = lastOccurrence(arr, x);

    if (first == -1 || last == -1) {
        return 0;
    }

    return (last - first + 1);
}

// ================== Main Function ==================
int main() {
    // Sample Test Cases
    vector<int> arr1 = {2, 2, 3, 3, 3, 3, 4};
    int x1 = 3;
    
    vector<int> arr2 = {1, 1, 2, 2, 2, 2, 2, 3};
    int x2 = 2;

    // Using Brute Force
    cout << "[Brute Force] Occurrences of " << x1 << ": " << countOccurrencesBruteForce(arr1, x1) << endl;
    cout << "[Brute Force] Occurrences of " << x2 << ": " << countOccurrencesBruteForce(arr2, x2) << endl;

    // Using Optimal (Binary Search)
    cout << "[Optimal] Occurrences of " << x1 << ": " << countOccurrencesOptimal(arr1, x1) << endl;
    cout << "[Optimal] Occurrences of " << x2 << ": " << countOccurrencesOptimal(arr2, x2) << endl;

    return 0;
}
