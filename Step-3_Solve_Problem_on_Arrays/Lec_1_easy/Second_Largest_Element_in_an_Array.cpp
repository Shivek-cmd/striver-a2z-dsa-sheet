#include <bits/stdc++.h>
using namespace std;
/*
    🔸 Question:
    Write a function to return the second largest element in a given array.

    Example:
    Input:  [1, 2, 4, 7, 7, 5]
    Output: 5

    If no second largest exists (e.g., all elements are the same or array size < 2), return -1.
*/
/*
    ✅ Function to return the second largest element in the array

    1. BRUTE FORCE APPROACH:
        - Sort the array in ascending order.
        - Traverse from second last element and find the first element not equal to the largest.
        - Time Complexity: O(n log n)
        - Space Complexity: O(1) (in-place sort)

    2. OPTIMAL APPROACH (Two Pass):
        - First pass to find the largest element.
        - Second pass to find the max element less than the largest.
        - Time Complexity: O(2n)
        - Space Complexity: O(1)

    3. OPTIMAL APPROACH (One Pass):
        - Initialize:
            largest = arr[0]
            second_largest = INT_MIN
        - Traverse the array:
            - If current > largest:
                second_largest = largest
                largest = current
            - Else if current != largest and current > second_largest:
                second_largest = current
        - This ensures we update both values in one pass.
        - Time Complexity: O(n)
        - Space Complexity: O(1)
*/

// 1. Brute Force
int findSecondLargest_BruteForce(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return -1;

    sort(arr.begin(), arr.end());

    int largest = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] != largest) {
            return arr[i];
        }
    }

    return -1;
}

// 2. Optimal (Two Pass)
int findSecondLargest_TwoPass(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int largest = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > largest)
            largest = arr[i];
    }

    int second_largest = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] != largest && arr[i] > second_largest)
            second_largest = arr[i];
    }

    return second_largest == INT_MIN ? -1 : second_largest;
}

// 3. Optimal (One Pass)
int findSecondLargest_OnePass(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int largest = arr[0];
    int second_largest = INT_MIN;

    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            second_largest = largest;
            largest = arr[i];
        } else if (arr[i] < largest && arr[i] > second_largest) {
            second_largest = arr[i];
        }
    }

    return second_largest == INT_MIN ? -1 : second_largest;
}

int main() {
    vector<int> arr = {1, 2, 4, 7, 7, 5};

    // Brute Force
    int second1 = findSecondLargest_BruteForce(arr);
    cout << "[1. Brute Force] Second largest: ";
    second1 != -1 ? cout << second1 << endl : cout << "Does not exist\n";

    // Two Pass Optimal
    int second2 = findSecondLargest_TwoPass(arr);
    cout << "[2. Two Pass Optimal] Second largest: ";
    second2 != -1 ? cout << second2 << endl : cout << "Does not exist\n";

    // One Pass Optimal
    int second3 = findSecondLargest_OnePass(arr);
    cout << "[3. One Pass Optimal] Second largest: ";
    second3 != -1 ? cout << second3 << endl : cout << "Does not exist\n";

    return 0;
}
