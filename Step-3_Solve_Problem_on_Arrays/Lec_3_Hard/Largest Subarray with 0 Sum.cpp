#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Find the length of the longest subarray with a sum of zero in an array of integers.
- The array can contain positive, negative, or zero values.
- A subarray is a contiguous segment of the array.
- If no such subarray exists, return 0.

Example Inputs and Outputs:
1. Input: arr = [9, -3, 3, -1, 6, -5]
   Output: 5 (Subarray [-3, 3, -1, 6, -5] sums to 0)
2. Input: arr = [6, -2, 2, -8, 1, 7, 4, -10]
   Output: 8 (Entire array sums to 0)
3. Input: arr = [1, 0, -5]
   Output: 1 (Subarray [0] sums to 0)
4. Input: arr = [1, 3, -5, 6, -2]
   Output: 0 (No subarray sums to 0)

Constraints:
- 1 <= arr.size() <= 10^5
- -10^9 <= arr[i] <= 10^9

Edge Cases:
- Empty array: Return 0.
- No zero-sum subarray: Return 0.
- Array with all zeros: Return array size.
- Single element array: Return 1 if arr[0] == 0, else 0.
- Large inputs: Handle potential integer overflow in sum calculations.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Consider every possible subarray by iterating over all starting indices (i) and ending indices (j).
- Compute the sum of elements from index i to j.
- If the sum is zero, update the maximum length of such a subarray.

Algorithm:
1. Initialize max_length = 0.
2. For each index i from 0 to n-1:
   - For each index j from i to n-1:
     - Compute sum of arr[i] to arr[j].
     - If sum == 0, update max_length = max(max_length, j - i + 1).
3. Return max_length.

Time Complexity: O(n^2)
- Two nested loops iterate over all possible subarrays: O(n^2).
- Sum calculation for each subarray is O(1) per element, but overall dominated by loop structure.

Space Complexity: O(1)
- Only uses a constant amount of extra space.

Limitations:
- Inefficient for large arrays due to quadratic time complexity.
- Does not leverage patterns in sums to reduce computations.

----------------------------------------
Approach 2: Optimal (Prefix Sum with Hash Map)
----------------------------------------
Logic:
- Use the prefix sum technique: A subarray [i+1, j] has a sum of zero if prefix_sum[j] == prefix_sum[i].
- Store prefix sums in a hash map with their earliest indices.
- If a prefix sum is seen again, the subarray between the current index and the stored index has a sum of zero.
- If the prefix sum is zero, the subarray from index 0 to the current index has a sum of zero.

Algorithm:
1. Initialize max_length = 0, sum = 0, and an unordered_map to store prefix_sum -> earliest_index.
2. Iterate through the array (index i):
   - Add arr[i] to sum.
   - If sum == 0, update max_length = i + 1.
   - If sum exists in the map, update max_length = max(max_length, i - map[sum]).
   - If sum is not in the map, store sum -> i.
3. Return max_length.

Time Complexity: O(n)
- Single pass through the array: O(n).
- Hash map operations (insert, find) are O(1) on average.

Space Complexity: O(n)
- Hash map stores at most n prefix sums.

Why Optimal:
- Reduces time complexity from O(n^2) to O(n) by using a hash map to avoid recomputing sums.
- Efficiently handles large inputs and all edge cases.
- Minimal memory overhead compared to time savings.

Trade-offs:
- Requires O(n) extra space, unlike the brute force approach.
- Potential integer overflow for very large sums (mitigated with long long).
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Brute Force
int longestSubarrayWithZeroSumBruteForce(const vector<int>& arr) {
    int max_length = 0;
    int n = arr.size();

    // Handle empty array
    if (n == 0) return 0;

    // Iterate over all possible subarrays
    for (int i = 0; i < n; i++) {
        long long sum = 0; // Use long long to prevent overflow
        for (int j = i; j < n; j++) {
            sum += arr[j];
            // If sum is zero, update max_length
            if (sum == 0) {
                max_length = max(max_length, j - i + 1);
            }
        }
    }

    return max_length;
}

// Approach 2: Optimal (Prefix Sum with Hash Map)
int longestSubarrayWithZeroSumOptimal(const vector<int>& arr) {
    int max_length = 0;
    unordered_map<long long, int> mp; // prefixSum -> earliestIndex
    long long sum = 0; // Use long long to prevent overflow

    // Handle empty array
    if (arr.empty()) return 0;

    // Iterate through the array
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];

        // If sum is zero, subarray from 0 to i has sum zero
        if (sum == 0) {
            max_length = i + 1;
        }

        // If sum exists in map, subarray from mp[sum]+1 to i has sum zero
        if (mp.find(sum) != mp.end()) {
            max_length = max(max_length, i - mp[sum]);
        } else {
            // Store the earliest occurrence of this sum
            mp[sum] = i;
        }
    }

    return max_length;
}
int main() {
    vector<int> arr = {6, -2, 2, -8, 1, 7, 4, -10};

    int bruteForceResult = longestSubarrayWithZeroSumBruteForce(arr);
    cout << "Brute Force Result: Length of the longest subarray with zero sum = " << bruteForceResult << endl;

    int optimalResult = longestSubarrayWithZeroSumOptimal(arr);
    cout << "Optimal Result:     Length of the longest subarray with zero sum = " << optimalResult << endl;

    return 0;
}
