#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Question:
    Write a function to left rotate an array by one place.

    Example:
    Input:  [1, 2, 3, 4, 5]
    Output: [2, 3, 4, 5, 1]

    Rotation must be done in-place if possible.
*/

/*
    ✅ Left Rotate an Array by One Place

    1. BRUTE FORCE APPROACH:
        - Create an auxiliary array of the same size.
        - Copy all elements from index 1 to n-1 into it.
        - Copy the first element at the last position.
        - Copy the auxiliary array back to the original array.
        - Time Complexity: O(n)
        - Space Complexity: O(n)

    2. OPTIMAL IN-PLACE APPROACH:
        - Store the first element in a temporary variable.
        - Shift all elements to the left by one.
        - Place the stored element at the last position.
        - Time Complexity: O(n)
        - Space Complexity: O(1)
*/

// --------------------------------------
// 1. Brute Force Approach
// --------------------------------------
void leftRotateByOne_BruteForce(vector<int> &arr) {
    int n = arr.size();
    vector<int> temp(n);

    // Copy from index 1 to end
    for (int i = 1; i < n; i++) {
        temp[i - 1] = arr[i];
    }

    // Place first element at the end
    temp[n - 1] = arr[0];

    // Copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

// --------------------------------------
// 2. Optimal In-Place Approach
// --------------------------------------
void leftRotateByOne_Optimal(vector<int> &arr) {
    int n = arr.size();
    int firstElement = arr[0];

    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    arr[n - 1] = firstElement;
}

// --------------------------------------
// Main Function
// --------------------------------------
int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5}; // For brute force
    vector<int> arr2 = arr1;            // For optimal approach

    // Brute Force
    leftRotateByOne_BruteForce(arr1);
    cout << "[Brute Force] Array after left rotation by one: ";
    for (int val : arr1) cout << val << " ";
    cout << endl;

    // Optimal
    leftRotateByOne_Optimal(arr2);
    cout << "[Optimal] Array after left rotation by one: ";
    for (int val : arr2) cout << val << " ";
    cout << endl;

    return 0;
}
