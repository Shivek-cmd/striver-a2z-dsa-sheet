#include <bits/stdc++.h>
using namespace std;


/*
    🔸 Question:
    Write a function to remove duplicates from a **sorted array** in-place
    and return the number of unique elements.

    Example:
    Input:  [1, 1, 2, 2, 3, 4, 4]
    Output: 4
    Modified array: [1, 2, 3, 4, _, _, _]

    Only the first part of the array needs to be correct — after removing duplicates.
*/
/*
    ✅ Remove duplicates from a sorted array

    1. BRUTE FORCE APPROACH:
        - Use a set to store unique elements.
        - Copy all elements from the set back to the original array.
        - Time Complexity: O(n log n)
        - Space Complexity: O(n)

    2. TWO POINTER APPROACH (Optimal):
        - Use two pointers:
            i → last index of unique elements
            j → iterate through the array
        - If arr[i] != arr[j], increment i and update arr[i] = arr[j]
        - Time Complexity: O(n)
        - Space Complexity: O(1)
*/

// ---------------------
// 1. Brute Force Approach
// ---------------------
int removeDuplicates_BruteForce(vector<int> &arr) {
    set<int> s;

    // Insert all elements into the set
    for (int i = 0; i < arr.size(); i++) {
        s.insert(arr[i]);
    }

    // Copy set elements back to the beginning of the array
    int i = 0;
    for (int val : s) {
        arr[i++] = val;
    }

    return s.size(); // Return the number of unique elements
}

// ---------------------
// 2. Two Pointer Optimal Approach
// ---------------------
int removeDuplicates_Optimal(vector<int> &arr) {
    if (arr.empty()) return 0;

    int i = 0;
    for (int j = 1; j < arr.size(); j++) {
        if (arr[i] != arr[j]) {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1; // Number of unique elements
}

// ---------------------
// Main Function
// ---------------------
int main() {
    vector<int> arr1 = {1, 1, 2, 2, 3, 4, 4};
    vector<int> arr2 = arr1; // Copy for second method

    // Call Brute Force Method
    int len1 = removeDuplicates_BruteForce(arr1);
    cout << "[Brute Force] Array after removing duplicates: ";
    for (int i = 0; i < len1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // Call Optimal Method
    int len2 = removeDuplicates_Optimal(arr2);
    cout << "[Optimal] Array after removing duplicates: ";
    for (int i = 0; i < len2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}
