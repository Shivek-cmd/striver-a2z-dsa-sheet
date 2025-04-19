/*
Problem Statement:
Given an array Arr[] of integers, rearrange the numbers of the given array into the lexicographically next greater permutation of numbers.
If such an arrangement is not possible, it must rearrange to the lowest possible order (i.e., sorted in ascending order).

Example 1:
Input format: Arr[] = {1, 3, 2}
Output: Arr[] = {2, 1, 3}
Explanation: All permutations of {1, 2, 3} are {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}.
So, the next permutation just after {1, 3, 2} is {2, 1, 3}.

Example 2:
Input format: Arr[] = {3, 2, 1}
Output: Arr[] = {1, 2, 3}
Explanation: As we see all permutations of {1, 2, 3}, we find {3, 2, 1} at the last position.
So, we have to return the topmost permutation, which is {1, 2, 3}.

======================
Approach 1: Brute Force Approach
======================

- Generate all permutations of the array.
- Store the permutations and find the next permutation in the list.
- Return the next permutation.

Time Complexity:
- Generating all permutations takes O(n!) time, where n is the length of the array.
- Finding the next permutation requires O(n!) comparisons, making this approach infeasible for larger arrays.
- overall time complexity is O(n!).

Space Complexity:
- Storing the permutations takes O(n!) space.

===========================
Approach 2: Better Approach (Using STL next_permutation)
===========================

- Use the C++ `next_permutation()` function from the `<algorithm>` library to find the next lexicographical permutation directly.
- This approach is much more efficient than the brute force approach.

Time Complexity:
- The `next_permutation()` function works in O(n) time, where n is the length of the array.
- This approach is optimal in terms of both time and space complexity.

Space Complexity:
- No extra space is used except for a few variables, so space complexity is O(1).

======================
Approach 3: Optimal Approach (Manual Implementation)
======================


- Instead of generating all permutations or using `next_permutation()`, we manually implement the logic to find the next permutation by:
    1. Finding the rightmost element that is smaller than its next element.
    2. Finding the smallest element to the right of the chosen element that is larger than the chosen element.
    3. Swapping the two elements.
    4. Reversing the sequence to the right of the chosen element to get the next permutation.
  
This approach ensures that we directly find the next permutation in O(n) time without generating all permutations or needing extra space.

Time Complexity:
- Finding the break point and the element to swap both take O(n).
- Reversing the array from the breakpoint takes O(n).
- So, the overall time complexity is O(n).

Space Complexity:
- The space complexity is O(1) as no extra space is used except for a few variables.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Approach 1: Brute Force (Generate all permutations)
void generatePermutations(vector<int>& arr, int index, vector<vector<int>>& result) {
    if (index == arr.size()) {
        result.push_back(arr); // Store the current permutation
        return;
    }

    for (int i = index; i < arr.size(); i++) {
        swap(arr[i], arr[index]); // Swap to generate a new permutation
        generatePermutations(arr, index + 1, result); // Recurse
        swap(arr[i], arr[index]); // Backtrack to restore the array
    }
}

vector<int> nextGreaterPermutationBruteForce(vector<int>& arr) {
    vector<vector<int>> permutations;
    generatePermutations(arr, 0, permutations); // Generate all permutations

    // Find the current permutation index
    int index = -1;
    for (int i = 0; i < permutations.size(); i++) {
        if (permutations[i] == arr) {
            index = i;
            break;
        }
    }

    // If we are at the last permutation, return the first one (sorted array)
    if (index == permutations.size() - 1) {
        sort(arr.begin(), arr.end()); // Sort the array for the lowest permutation
        return arr;
    }

    return permutations[index + 1]; // Return the next permutation
}

// Approach 2: Better Approach (Using STL next_permutation)
vector<int> nextGreaterPermutationSTL(vector<int>& arr) {
    bool hasNext = next_permutation(arr.begin(), arr.end());
    if (hasNext) {
        return arr;
    }
    return arr;
}

// Approach 3: Optimal Approach (Manual Implementation)
vector<int> nextGreaterPermutationOptimal(vector<int>& arr) {
    int n = arr.size();
    int idx = -1;

    // Step 1: Find the rightmost element that is smaller than the next element
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            idx = i;
            break;
        }
    }

    // If no such element exists, we are at the last permutation
    if (idx == -1) {
        sort(arr.begin(), arr.end()); // Sort the array to return the lowest permutation
        return arr;
    }

    // Step 2: Find the smallest element greater than arr[idx] to the right of it
    for (int i = n - 1; i > idx; i--) {
        if (arr[i] > arr[idx]) {
            swap(arr[i], arr[idx]);
            break;
        }
    }

    // Step 3: Reverse the subsequence to the right of idx
    reverse(arr.begin() + idx + 1, arr.end());
    return arr;
}

int main() {
    vector<int> A = {7, 9, 6, 5, 4, 8};

    // Testing Brute Force Approach
    vector<int> resultBrute = nextGreaterPermutationBruteForce(A);
    cout << "Next permutation (Brute Force): ";
    for (int num : resultBrute) {
        cout << num << " ";
    }
    cout << endl;

    // Testing Better Approach (Using STL next_permutation)
    vector<int> resultSTL = nextGreaterPermutationSTL(A);
    cout << "Next permutation (STL): ";
    for (int num : resultSTL) {
        cout << num << " ";
    }
    cout << endl;

    // Testing Optimal Approach (Manual Implementation)
    vector<int> resultOptimal = nextGreaterPermutationOptimal(A);
    cout << "Next permutation (Optimal): ";
    for (int num : resultOptimal) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
