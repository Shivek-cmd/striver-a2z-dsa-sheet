#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Question:
    Write a function to perform Linear Search on an array.
    Return the index of the target element if found, otherwise return -1.

    Example:
    Input:  arr = [10, 20, 30, 40, 50], target = 30
    Output: 2
*/

/*
    ✅ Approach:
    - Traverse the array from left to right.
    - Compare each element with the target.
    - If a match is found, return its index.
    - If no match is found after the loop, return -1.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

// Function to perform linear search
int linearSearch(vector<int> &arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i; // Return index if found
        }
    }
    return -1; // Return -1 if not found
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 50}; // Sample array
    int target = 30; // Element to search for

    int index = linearSearch(arr, target);

    if (index != -1)
        cout << "Element found at index: " << index << endl;
    else
        cout << "Element not found in the array." << endl;

    return 0;
}
