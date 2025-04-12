#include <bits/stdc++.h>
using namespace std;

/*
    ✅ Function to return the largest element in the array

    1. BRUTE FORCE APPROACH:
        - Sort the array and return the last element.
        - Time Complexity: O(n log n)
        - Space Complexity: O(1) [In-place sorting]

    2. OPTIMAL APPROACH (Implemented Below):
        - Initialize maxElement with the smallest possible integer.
        - Traverse the array and update maxElement whenever a larger element is found.
        - Time Complexity: O(n)
        - Space Complexity: O(1)
*/

int findLargestElement(vector<int> &arr) {
    // Initialize maxElement with minimum possible integer value
    int maxElement = INT_MIN;

    // Traverse the array to find the largest element
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];  // Update maxElement if current element is larger
        }
    }

    return maxElement;
}

int main() {
    vector<int> arr = {3, 8, 1, 99, 12, 7};

    // Call the function to find the largest element
    int largest = findLargestElement(arr);

    // Print the result
    cout << "The largest element is: " << largest << endl;

    return 0;
}
