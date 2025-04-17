#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
PROBLEM STATEMENT:
-----------------------------------------------------
Given an integer array arr, find the contiguous subarray (containing at least one number)
which has the largest sum and returns its sum and prints the subarray.

Examples:

Example 1:
Input: arr = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: arr = [1]
Output: 1
Explanation: Array has only one element and which is giving positive sum of 1.

-----------------------------------------------------
Approaches to solve the problem:

1. **Brute Force Approach (O(n^3))**:
   - Generate all subarrays.
   - For each subarray, compute its sum.
   - Keep track of the maximum sum found.
   - Time Complexity: O(n^3), Space Complexity: O(1)
   - This approach is inefficient as it generates and checks all possible subarrays.

2. **Better Approach (O(n^2))**:
   - Generate all subarrays, but instead of recalculating the sum of each subarray from scratch, we can use a dynamic approach where we add the next element to the previous sum.
   - Time Complexity: O(n^2), Space Complexity: O(1)
   - This approach reduces the complexity compared to brute force.

3. **Optimal Approach (Kadane's Algorithm - O(n))**:

        THOUGHT PROCESS
        At any point, a subarray can either continue growing or it can be beneficial to discard it and start a new subarray. 
        If the sum of the current subarray becomes negative, adding more elements to it will only decrease the overall sum.
        Therefore, we reset the subarray and start fresh from the next element.
        suppose there's an array in which two subarrays are below
        WHICH ARRAY IS BETTER [-1,2,3] or [2,3] obviously second one that's why we ignore the subarray which is reducing the sum
        
   - We traverse the array once and keep track of the maximum sum of the subarray ending at the current element.
   - If the current sum becomes negative, we reset it to zero since starting from the next element will be more beneficial.
   - This is a greedy approach with linear time complexity.
   - Time Complexity: O(n), Space Complexity: O(1)
   - This is the most efficient solution for this problem.

-----------------------------------------------------
*/

// Brute Force Approach (O(n^3))
int maxSubArraySum_BruteForce(const vector<int>& arr) {
    int max_sum = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;
}

// Better Approach (O(n^2))
int maxSubArraySum_Better(const vector<int>& arr) {
    int max_sum = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        int sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;
}

// Optimal Approach (Kadane's Algorithm - O(n))
int maxSubArraySum_Optimal(const vector<int>& arr) {
    int max_sum = INT_MIN;
    int curr_sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        curr_sum += arr[i];
        if (curr_sum < 0) {
            curr_sum = 0;  // Reset the sum to 0 if it becomes negative
        }
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}

// Additional feature: Print subarray with maximum sum (Kadane's Algorithm)
// int maxSubArraySum_Optimal_WithSubarray(const vector<int>& arr) {
//     int max_sum = INT_MIN;
//     int curr_sum = 0;
//     int start = 0, end = 0, temp_start = 0;
    
//     for (int i = 0; i < arr.size(); i++) {
          
        
//         // If current sum is less than 0, reset it and start from next element
//         if (curr_sum < 0) {
//             curr_sum = 0;
//             temp_start = i + 1;
//         }
        
//         if (curr_sum > max_sum) {
//             max_sum = curr_sum;
//             start = temp_start;
//             end = i;
//         }
//     }

//     // Print the subarray
//     cout << "Maximum Subarray Sum: " << max_sum << endl;
//     cout << "Subarray: ";
//     for (int i = start; i <= end; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     return max_sum;
// }

// Sample main function to test all approaches
int main() {
    vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    // Brute Force Approach
    cout << "Brute Force Approach: " << maxSubArraySum_BruteForce(arr1) << endl;

    // Better Approach
    cout << "Better Approach: " << maxSubArraySum_Better(arr1) << endl;

    // Optimal Approach (Kadane's Algorithm)
    cout << "Optimal Approach: " << maxSubArraySum_Optimal(arr1) << endl;

    // Optimal Approach with Subarray Print
    // maxSubArraySum_Optimal_WithSubarray(arr1);

    vector<int> arr2 = {1};
    
    // Testing with another simple case
    cout << "Brute Force Approach: " << maxSubArraySum_BruteForce(arr2) << endl;
    cout << "Better Approach: " << maxSubArraySum_Better(arr2) << endl;
    cout << "Optimal Approach: " << maxSubArraySum_Optimal(arr2) << endl;

    return 0;
}
