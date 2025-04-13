#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Problem Statement:
    Given an array that contains only 1s and 0s, return the count of maximum consecutive 1s in the array.

    Examples:

    Example 1:
    Input:  arr = {1, 1, 0, 1, 1, 1}
    Output: 3

    Example 2:
    Input:  arr = {1, 0, 1, 1, 0, 1}
    Output: 2
*/

/*
    ✅ All Approaches:

    🔹 Approach 1: Brute Force
        - Use nested loops to count consecutive 1s starting from each index.
        - Update max every time you encounter a longer sequence.

        Time Complexity:  O(n^2)
        Space Complexity: O(1)

     🔹 Approach 2: Optimal (One-Pass)
        - Maintain two variables:
            → `count` to track the current streak of 1s
            → `maxCount` to track the maximum streak found so far
        - Traverse the array:
            - If current element is 1 → increment `count`, and update `maxCount` if needed
            - If current element is 0 → reset `count` to 0 (as the streak breaks)
        - After the loop, return `maxCount` as the result

        Time Complexity:  O(n)
        Space Complexity: O(1)
*/

/*---------------------------------------------------
    ✅ All Solutions
---------------------------------------------------*/

// 🔽 Approach 1: Brute Force
int findMaxConsecutiveOnes_BruteForce(vector<int>& arr) {
    int maxCount = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i; j < n && arr[j] == 1; j++) {
            count++;
        }
        maxCount = max(maxCount, count);
    }

    return maxCount;
}

// 🔽 Approach 2: Optimal (One-Pass)
int findMaxConsecutiveOnes_Optimal(vector<int>& arr) {
    int maxCount = 0, currCount = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) {
            currCount++;
        } else {
            maxCount = max(maxCount, currCount);
            currCount = 0;
        }
    }

    maxCount = max(maxCount, currCount); // Final update in case of ending with 1s
    return maxCount;
}

/*---------------------------------------------------
    ✅ Main Function to Test All Approaches
---------------------------------------------------*/
int main() {
    vector<int> arr = {1, 1, 0, 1, 1, 1};

    cout << "[Brute Force] Maximum consecutive 1s: " 
         << findMaxConsecutiveOnes_BruteForce(arr) << endl;

    cout << "[Optimal] Maximum consecutive 1s: " 
         << findMaxConsecutiveOnes_Optimal(arr) << endl;

    return 0;
}
