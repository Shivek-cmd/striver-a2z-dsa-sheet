#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Split Array Largest Sum
Given an integer array 'A' of size 'N' and an integer 'K', split the array into 'K' non-empty
subarrays such that the largest sum of any subarray is minimized. Return the minimized largest sum.
A subarray is a contiguous part of the array.

Input:
- A: Vector of integers representing the array.
- N: Size of the array (1 <= N <= 10^5).
- K: Number of subarrays to split into (1 <= K <= N).
- A[i]: Array elements (0 <= A[i] <= 10^9).

Output:
- Integer representing the minimized largest subarray sum.

Examples:
1. Input: A = {1, 2, 3, 4, 5}, N = 5, K = 3
   Output: 6
   Explanation: Split into [1, 2, 3], [4], [5]. Largest sum = 6.
2. Input: A = {3, 5, 1}, N = 3, K = 3
   Output: 5
   Explanation: Split into [3], [5], [1]. Largest sum = 5.

Constraints:
- 1 <= N <= 10^5
- 1 <= K <= N
- 0 <= A[i] <= 10^9

Edge Cases:
- K == N: Each element is its own subarray, answer = max(A).
- K == 1: Entire array is one subarray, answer = sum(A).
- K > N: Impossible to split, but not applicable given constraints (K <= N).
- Single element array (N == 1, K == 1): Answer = A[0].
- Array with zeros: May reduce subarray sums, but logic remains same.
- Large A[i] values: Use long long to avoid overflow in sum calculations.
*/

/*
==============================================================================
Section 2: Observations
==============================================================================
1. The minimum possible answer is the maximum element in the array (max(arr[])), 
   achieved when the array is split into N subarrays, each containing one element.
2. The maximum possible answer is the sum of all array elements (sum(arr[])), achieved
  when the array is treated as a single subarray.
3. The answer lies in the range [max(arr[]), sum(arr[])], defining the search space for
   the minimized largest subarray sum.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Iterate through all possible maximum subarray sums from max(A) to sum(A).
- For each sum, check if the array can be split into exactly K subarrays without any subarray exceeding that sum.
- Return the smallest sum that satisfies the condition.

Algorithm:
1. Find max(A) (lower bound) and sum(A) (upper bound).
2. For each possible maxSum from max(A) to sum(A):
   a. Use countPartitions() to calculate the number of subarrays needed.
   b. If the number of subarrays equals K, return maxSum.
3. Return max(A) if no solution is found (unlikely given constraints).

Time Complexity: O(N * (sum(A) - max(A) + 1))
- N: Array size, for countPartitions() loop.
- sum(A) - max(A) + 1: Range of possible sums, up to 10^14 in worst case.
- Impractical for large inputs due to linear search over huge range.

Space Complexity: O(1)
- Only uses constant extra space.

Limitations:
- Highly inefficient for large sum(A) (e.g., 10^9 * 10^5).
- Not suitable for real-time applications.

----------------------------------------
Approach 2: Optimal (Binary Search)
----------------------------------------
Logic:
- The answer lies in [max(A), sum(A)], and the number of subarrays needed decreases as the maximum sum increases (monotonic).
- Use binary search to find the smallest sum that allows splitting into exactly K subarrays.
- For each mid-point, check if the number of subarrays needed is <= K.

Algorithm:
1. Initialize low = max(A), high = sum(A).
2. While low <= high:
   a. Compute mid = low + (high - low) / 2.
   b. Use countPartitions() to get the number of subarrays needed for mid.
   c. If subarrays > K, mid is too small, set low = mid + 1.
   d. If subarrays <= K, mid is a candidate, try a smaller value: high = mid - 1.
3. Return low, the smallest valid maximum sum.

Time Complexity: O(N * log(sum(A) - max(A) + 1))
- Binary search: log(sum(A) - max(A) + 1) iterations, up to log(10^14).
- countPartitions(): O(N) per iteration.
- Efficient for large inputs due to logarithmic reduction.

Space Complexity: O(1)
- Only uses constant extra space.

Why Optimal?
- Binary search leverages the monotonic property to reduce search space.
- Handles large inputs (N <= 10^5, A[i] <= 10^9) efficiently.
- Simple to implement with robust performance.

Trade-offs:
- Slightly more complex than brute force but far more efficient.
- Requires careful handling of long long for large sums.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Helper function to count the number of subarrays needed for a given maximum sum
int countPartitions(const vector<int>& a, long long maxSum) {
    int partitions = 1; // Start with one subarray
    long long subarraySum = 0; // Current subarray sum

    // Iterate through the array
    for (int val : a) {
        // If adding current element fits within maxSum
        if (subarraySum + val <= maxSum) {
            subarraySum += val;
        } else {
            // Start a new subarray
            partitions++;
            subarraySum = val;
        }
    }
    return partitions;
}

// Brute Force Approach
int largestSubarraySumMinimizedBrute(const vector<int>& a, int k) {
    // Find max element and total sum
    long long maxElement = *max_element(a.begin(), a.end());
    long long totalSum = accumulate(a.begin(), a.end(), 0LL);

    // Check each possible maximum sum
    for (long long maxSum = maxElement; maxSum <= totalSum; ++maxSum) {
        if (countPartitions(a, maxSum) == k) {
            return maxSum;
        }
    }
    // Return max element if no solution (unlikely)
    return maxElement;
}

// Optimal Approach (Binary Search)
int largestSubarraySumMinimizedOptimal(const vector<int>& a, int k) {
    // Handle edge case: K > N is impossible, but not needed since K <= N
    int n = a.size();
    if (k > n) return -1; // Just for robustness

    // Find max element and total sum
    long long maxElement = *max_element(a.begin(), a.end());
    long long totalSum = accumulate(a.begin(), a.end(), 0LL);

    // Binary search
    long long low = maxElement, high = totalSum;
    while (low <= high) {
        long long mid = low + (high - low) / 2; // Avoid overflow
        int partitions = countPartitions(a, mid);
        if (partitions > k) {
            // Need more subarrays, increase maxSum
            low = mid + 1;
        } else {
            // Valid or fewer subarrays, try smaller maxSum
            high = mid - 1;
        }
    }
    return low;
}

int main() {
    // Test case
    vector<int> a = {10, 20, 30, 40};
    int k = 2;

    // Run brute force approach
    int ansBrute = largestSubarraySumMinimizedBrute(a, k);
    cout << "Brute Force Answer: " << ansBrute << "\n";

    // Run optimal approach
    int ansOptimal = largestSubarraySumMinimizedOptimal(a, k);
    cout << "Optimal Answer: " << ansOptimal << "\n";

    return 0;
}

/*
Expected Output for a = {10, 20, 30, 40}, k = 2:
Brute Force Answer: 60
Optimal Answer: 60
*/