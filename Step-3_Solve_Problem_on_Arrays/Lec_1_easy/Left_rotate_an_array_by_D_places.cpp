#include <bits/stdc++.h>
using namespace std;

/*
    ✅ Left Rotate an Array by D Places

    ---------------------------------------------
    🔁 Approach 1: Brute Force (Using Extra Array)
    ---------------------------------------------
    - Create a temporary array of same size.
    - Copy elements from index d to n-1 into temp.
    - Then copy elements from index 0 to d-1.
    - Copy temp back to original array.
    - Time Complexity: O(n)
    - Space Complexity: O(n)

    ------------------------------------------------
    🔁 Approach 2: Repeated Left Rotate by One (Naive)
    ------------------------------------------------
    - Repeat the left rotation by one, d times.
    - Each left rotate takes O(n), so total is O(n*d)
    - Space Complexity: O(1)

    -----------------------------------------------
    🔁 Approach 3: Optimal Approach (Reversal Algorithm)
    -----------------------------------------------
    - Step 1: Reverse first d elements
    - Step 2: Reverse the remaining n-d elements
    - Step 3: Reverse the entire array
    - Time Complexity: O(n)
    - Space Complexity: O(1)
*/

// Utility function to reverse a portion of the array
void reverse(vector<int>& arr, int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// Optimal approach using reversal algorithm
void leftRotateByD(vector<int> &arr, int d) {
    int n = arr.size();
    d = d % n; // Handle d > n

    // Step 1: Reverse first d elements
    reverse(arr, 0, d - 1);

    // Step 2: Reverse remaining n - d elements
    reverse(arr, d, n - 1);

    // Step 3: Reverse entire array
    reverse(arr, 0, n - 1);
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int d = 2; // Number of places to rotate

    // Call the function
    leftRotateByD(arr, d);

    // Print the rotated array
    cout << "Array after left rotation by " << d << " places: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
