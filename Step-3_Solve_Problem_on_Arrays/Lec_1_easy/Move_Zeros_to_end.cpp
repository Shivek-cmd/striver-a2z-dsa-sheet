#include <bits/stdc++.h>
using namespace std;
/*
    🔸 Question:
    Write a function to move all zeros in a given array to the end,
    while maintaining the relative order of non-zero elements.

    Example:
    Input:  [0, 1, 0, 3, 12]
    Output: [1, 3, 12, 0, 0]
*/

/*
    1. Brute Force Approach:
    - Create an auxiliary array initialized with 0s
    - Copy all non-zero elements from original array to it
    - Then copy all elements of auxiliary array back to original
    - Time Complexity: O(n)
    - Space Complexity: O(n)

    2. Two Pointer Approach:
    - Move all non-zero elements to the front using index i
    - Then fill the rest of the array with 0s
    - Time Complexity: O(n)
    - Space Complexity: O(1)

    3. Two Pointer + Swap Approach (Optimal and Cleaner):
    - Use two pointers:
        i → index to place the next non-zero element
        j → loop through the array
    - If arr[j] != 0, swap arr[i] and arr[j], then increment i
    - Automatically places all non-zero values at front and zeroes at end
    - No need for second loop to fill zeros
    - Time Complexity: O(n)
    - Space Complexity: O(1)
*/

void moveZerosToEnd(vector<int> &arr) {
    int i = 0;
    for (int j = 0; j < arr.size(); j++) {
        if (arr[j] != 0) {
            arr[i++] = arr[j];
        }
    }
    while (i < arr.size()) {
        arr[i++] = 0;
    }
}


void moveZerosToEnd1(vector<int> &arr) {
    int i = 0; // Pointer to place the next non-zero element

    for (int j = 0; j < arr.size(); j++) {
        if (arr[j] != 0) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
}

int main() {
    vector<int> arr = {0, 1, 0, 3, 12};

    moveZerosToEnd(arr);

    cout << "Array after moving zeros to the end: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
