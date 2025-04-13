#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Question:
    Write a function to check if a given array is sorted in non-decreasing order.

    Example:
    Input:  [1, 2, 3, 4, 5]
    Output: true

    Input:  [1, 3, 2, 4]
    Output: false

    ✅ Function to check if the array is sorted in non-decreasing order

    Approach:
    - Traverse the array from the second element.
    - Compare each element with the previous one.
    - If any element is smaller than the previous, return false.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

bool isSorted(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5}; // Try {1, 3, 2, 4} to test unsorted case

    if (isSorted(arr)) {
        cout << "✅ The array is sorted." << endl;
    } else {
        cout << "❌ The array is NOT sorted." << endl;
    }

    return 0;
}
