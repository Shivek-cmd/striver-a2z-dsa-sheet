#include <bits/stdc++.h>
using namespace std;





/*
    🔸 Problem Statement:
    Given an array of positive integers and a target sum `k`, 
    return the length of the longest contiguous subarray that sums to `k`.

    🧪 Examples:

    Example 1:
    Input:  arr = {2, 3, 5}, k = 5
    Output: 2
    Explanation: {2, 3} sums to 5

    Example 2:
    Input:  arr = {2, 3, 5, 1, 9}, k = 10
    Output: 3
    Explanation: {2, 3, 5} sums to 10
*/

/*
    ✅ All Approaches:

    🔹 Approach 1: Brute Force (Nested Loops)
        - Try every subarray using 2 nested loops.
        - For each subarray, calculate its sum.
        - If sum == k, update maxLen.

        Time Complexity: O(N^2)
        Space Complexity: O(1)

    🔹 Approach 2: Brute Force with Early Break (Slightly Better)
        - Same as brute force but break inner loop when sum > k
        - Valid only when all elements are positive

        Time Complexity: O(N^2)
        Space Complexity: O(1)

    🔹 Approach 3: Optimal - Sliding Window (Two Pointers)
        - Maintain a window [start, end] and sum of that window.
        - Move end forward and add to sum.
        - If sum > k, move start forward and subtract.
        - If sum == k, update maxLen.
         Valid for both positive adn p+n also

        Time Complexity: O(2N)
        Space Complexity: O(1)

    🔹 Approach 4: Prefix Sum + Hash Map (Handles Positives & Negatives)

    --------------------
    🔹 Prefix Sum Approach (Optimal for all integers)
    - Use a hash map to store prefix sum and first occurrence index.
    - For each element, compute prefix sum.
    - Check if (prefix_sum - k) exists in the map:
        → If yes, update maxLen = i - index
    - If prefix_sum not in map, insert it.

    Time Complexity: O(N)
    Space Complexity: O(N)    
*/

/* -------------------------------
    ✅ All Solutions
--------------------------------*/

// 🔸 Approach 1: Brute Force
int longestSubarrayWithSumK_BruteForce(vector<int>& arr, int k) {
    int maxLen = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int sum = 0;

        for (int j = i; j < n; j++) {
            sum += arr[j];

            if (sum == k) {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}

// 🔸 Approach 2: Brute Force with Early Break
int longestSubarrayWithSumK_BruteWithBreak(vector<int>& arr, int k) {
    int maxLen = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int sum = 0;

        for (int j = i; j < n; j++) {
            sum += arr[j];

            if (sum == k) {
                maxLen = max(maxLen, j - i + 1);
            }

            if (sum > k) break; // ✅ Early break since elements are positive
        }
    }

    return maxLen;
}

// 🔸 Approach 3: Optimal Sliding Window (for positives only)
int longestSubarrayWithSumK_SlidingWindow(vector<int>& arr, int k) {
    int left = 0, right = 0, sum = 0;
    int n = arr.size();
    int max_len = 0;

    while (right < n) {
        sum += arr[right];

        // Shrink the window until sum <= k
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }

        // If the sum equals k, update max_len
        if (sum == k) {
            max_len = max(max_len, right - left + 1);
        }

        // Move the right pointer to the next element
        right++;
    }

    return max_len;
}


int longestSubarrayWithSumK_PrefixMap(vector<int>& arr, int k) {
    unordered_map<int, int> prefixMap; // prefixSum -> index
    int sum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];

        if (sum == k) {
            maxLen = i + 1;  // Whole array so far
        }

        if (prefixMap.find(sum - k) != prefixMap.end()) {
            maxLen = max(maxLen, i - prefixMap[sum - k]);
        }

        // Store the first occurrence of each prefix sum
        if (prefixMap.find(sum) == prefixMap.end()) {
            prefixMap[sum] = i;
        }
    }

    return maxLen;
}

/* -------------------------------
    ✅ Main Function to Test All
--------------------------------*/

int main() {
    vector<int> arr = {2, 3, 5, 1, 9};
    int k = 10;

    cout << "[Brute Force] Length: " << longestSubarrayWithSumK_BruteForce(arr, k) << endl;
    cout << "[Brute w/ Early Break] Length: " << longestSubarrayWithSumK_BruteWithBreak(arr, k) << endl;
    cout << "[Sliding Window Optimal] Length: " << longestSubarrayWithSumK_SlidingWindow(arr, k) << endl;
    cout << "[Prefix Sum + Map] Length: " << longestSubarrayWithSumK_PrefixMap(arr, k) << endl;

    return 0;
}
