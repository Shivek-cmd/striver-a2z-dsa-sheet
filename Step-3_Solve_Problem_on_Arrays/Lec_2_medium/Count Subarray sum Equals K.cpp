// Problem Statement:
// Given an array of integers and an integer k, return the total number of subarrays whose sum equals k.
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example 1:
// Input: N = 4, array[] = {3, 1, 2, 4}, k = 6
// Output: 2
// Explanation: The subarrays that sum up to 6 are [3, 1, 2] and [2, 4].
//
// Example 2:
// Input: N = 3, array[] = {1, 2, 3}, k = 3
// Output: 2
// Explanation: The subarrays that sum up to 3 are [1, 2] and [3].
//
// Approach:
// There are multiple ways to solve this problem, let's analyze them:

// Approach 1: Brute Force (O(N^3))
// - Loop through each possible subarray in a brute force manner, calculating the sum of every subarray.
// - This is inefficient because we calculate the sum of every subarray repeatedly.

// Approach 2: Better Solution (O(N^2))
// - Loop through each subarray, but instead of calculating the sum for each subarray again, 
//   use the previously calculated sum to avoid redundant calculations. This reduces the number of sum calculations.

// Approach 3: Optimal Solution (O(N) with Prefix Sum and Hash Map)
// - Use prefix sum and hash map to store the frequency of prefix sums. 
// - This method allows us to calculate subarrays whose sum equals `k` efficiently in a single pass through the array.

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Approach 1: Brute Force O(N^3)
int bruteForceSubarraysCount(const vector<int>& arr, int k) {
    int n = arr.size();
    int count = 0;
    // Check every possible subarray
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            // Calculate the sum for each subarray
            for (int x = i; x <= j; x++) {
                sum += arr[x];
            }
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}

// Approach 2: Optimized Brute Force O(N^2)
int optimizedBruteForceSubarraysCount(const vector<int>& arr, int k) {
    int n = arr.size();
    int count = 0;
    // Loop through each starting point of the subarray
    for (int i = 0; i < n; i++) {
        int sum = 0;
        // Loop through each subarray starting from index i
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}

// Approach 3: Optimal Solution using Prefix Sum + Hash Map O(N)
int optimalSubarraysCount(const vector<int>& arr, int k) {
    unordered_map<int, int> prefixSumFreq;
    int count = 0, prefixSum = 0;
    // Initialize the map with 0 sum frequency (important for subarrays that directly sum to k)
    prefixSumFreq[0] = 1;

    // Traverse the array and compute prefix sum
    for (int num : arr) {
        prefixSum += num;
        
        // If prefixSum - k exists in the map, we have found a subarray with sum = k
        if (prefixSumFreq.find(prefixSum - k) != prefixSumFreq.end()) {
            count += prefixSumFreq[prefixSum - k];
        }

        // Update the frequency of the current prefixSum
        prefixSumFreq[prefixSum]++;
    }

    return count;
}

int main() {
    vector<int> arr1 = {3, 1, 2, 4};
    int k1 = 6;
    cout << "Brute Force Result: " << bruteForceSubarraysCount(arr1, k1) << endl;
    cout << "Optimized Brute Force Result: " << optimizedBruteForceSubarraysCount(arr1, k1) << endl;
    cout << "Optimal Result: " << optimalSubarraysCount(arr1, k1) << endl;

    vector<int> arr2 = {1, 2, 3};
    int k2 = 3;
    cout << "Brute Force Result: " << bruteForceSubarraysCount(arr2, k2) << endl;
    cout << "Optimized Brute Force Result: " << optimizedBruteForceSubarraysCount(arr2, k2) << endl;
    cout << "Optimal Result: " << optimalSubarraysCount(arr2, k2) << endl;

    return 0;
}

// Time Complexity and Space Complexity Analysis:

// Approach 1 (Brute Force):
// - Time Complexity: O(N^3), where N is the number of elements in the array.
//   We have three nested loops - one for the start index, one for the end index, and one to calculate the sum for each subarray.
// - Space Complexity: O(1) (constant space) as we are only using a few variables for counting.


// Approach 2 (Optimized Brute Force):
// - Time Complexity: O(N^2), where N is the number of elements in the array.
//   We have two nested loops - one for the start index and one for the end index. Instead of calculating the sum repeatedly, 
//   we accumulate the sum as we extend the subarray.
// - Space Complexity: O(1) (constant space) as we are only using a few variables for counting and sum.


// Approach 3 (Optimal using Prefix Sum + Hash Map):
// - Time Complexity: O(N), where N is the number of elements in the array.
//   We only traverse the array once, and each lookup or insertion operation in the hash map takes O(1) time on average.
// - Space Complexity: O(N), where N is the number of unique prefix sums stored in the hash map. In the worst case, this can be O(N).

// Conclusion:
// - Approach 1 is a brute force solution with O(N^3) time complexity, which is inefficient for large arrays.
// - Approach 2 improves on the brute force approach by reducing the time complexity to O(N^2) but still isn't optimal.
// - Approach 3 is the most efficient with O(N) time complexity using a hash map to keep track of prefix sums. This approach is optimal and should be used for large arrays.
