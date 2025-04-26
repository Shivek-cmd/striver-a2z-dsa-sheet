#include <bits/stdc++.h>
using namespace std;

// IMPORTANT DIFFERENCE (Duplicates Handling):
//     // Edge case:
//     if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
//         low = low + 1;
//         high = high - 1;
//         continue;
//     }
//     -> When duplicates confuse sorted side detection, shrink both ends by 1.

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem:
    Given an integer array arr of size N, sorted in ascending order (duplicate values) 
    and a target value k. Now the array is rotated at some pivot point unknown to you. 
    Find if k is present. If k is present, return true, else return false.

Example 1:
Input Format: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 3
Result: True

Example 2:
Input Format: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 10
Result: False

Constraints:
    - 1 <= N <= 10^5
    - -10^9 <= arr[i], k <= 10^9
    - Array is sorted (ascending) but rotated
    - Elements may have duplicates
==============================================================================

==============================================================================
Section 2: Solution Approaches
==============================================================================

Approach 1: Naive Approach (Brute Force)
----------------------------------------
Logic:
    - Traverse the array linearly.
    - Check each element if it matches k.

Time Complexity:
    - O(N)

Space Complexity:
    - O(1)

------------------------------------------------------------

Approach 2: Optimal Approach (Modified Binary Search with Duplicates Handling)
------------------------------------------------------------
Logic:
    - Use binary search.
    - If arr[low] == arr[mid] == arr[high], shrink both sides.
    - Otherwise, detect sorted side and eliminate.

Time Complexity:
    - O(N) worst case (if there are many duplicates), O(log N) average case.
    - Reason: In the worst case, when all elements are the same (e.g., array = {3, 3, 3, 3, 3, 3, 3}), the algorithm
      reduces the search space one step at a time (by moving low and high pointers), leading to a linear scan. 
      Hence, the worst-case time complexity is O(N). In average and best cases, the binary search principle works 
      and the time complexity is O(log N).

Space Complexity:
    - O(1)
    -  Reason: We are using only a few variables (low, high, mid), which results in constant space complexity, 
      regardless of the input size.

==============================================================================

==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// ===================== Approach 1: Brute Force =====================
bool searchInRotatedArrayBruteForce(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

// ===================== Approach 2: Optimal (Binary Search with Duplicates) =====================
bool searchInRotatedArrayOptimal(const vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return true;
        }

        // Edge case: when duplicates confuse sorted detection
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (target >= arr[low] && target < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if (target > arr[mid] && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return false; // Target not found
}

// ===================== Main Function =====================
int main() {
    // Sample test cases
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2, 3};
    int target1 = 0;
    
    vector<int> arr2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;

    vector<int> arr3 = {2, 5, 6, 0, 0, 1, 2}; // duplicate elements
    int target3 = 0;
    int target4 = 3;
    int target5 = 10; // Not present

    cout << "Brute Force Approach:" << endl;
    cout << "Is " << target1 << " present? " << (searchInRotatedArrayBruteForce(arr1, target1) ? "True" : "False") << endl;
    cout << "Is " << target2 << " present? " << (searchInRotatedArrayBruteForce(arr2, target2) ? "True" : "False") << endl;
    cout << "Is " << target3 << " present? " << (searchInRotatedArrayBruteForce(arr3, target3) ? "True" : "False") << endl;
    cout << "Is " << target4 << " present? " << (searchInRotatedArrayBruteForce(arr3, target4) ? "True" : "False") << endl;
    cout << "Is " << target5 << " present? " << (searchInRotatedArrayBruteForce(arr3, target5) ? "True" : "False") << endl;

    cout << "\nOptimal (Binary Search with Duplicates) Approach:" << endl;
    cout << "Is " << target1 << " present? " << (searchInRotatedArrayOptimal(arr1, target1) ? "True" : "False") << endl;
    cout << "Is " << target2 << " present? " << (searchInRotatedArrayOptimal(arr2, target2) ? "True" : "False") << endl;
    cout << "Is " << target3 << " present? " << (searchInRotatedArrayOptimal(arr3, target3) ? "True" : "False") << endl;
    cout << "Is " << target4 << " present? " << (searchInRotatedArrayOptimal(arr3, target4) ? "True" : "False") << endl;
    cout << "Is " << target5 << " present? " << (searchInRotatedArrayOptimal(arr3, target5) ? "True" : "False") << endl;

    return 0;
}
