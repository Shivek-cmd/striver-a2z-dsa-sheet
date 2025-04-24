#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Count the number of subarrays in an array of integers where the bitwise XOR
of all elements equals a given value K.
- A subarray is a contiguous segment of the array.
- The array contains non-negative integers (including zero).

Example Inputs and Outputs:
1. Input: A = [4, 2, 2, 6, 4], K = 6
   Output: 4
   Explanation: Subarrays with XOR = 6 are [4,2], [4,2,2,6,4], [2,2,6], [6]
2. Input: A = [5, 6, 7, 8, 9], K = 5
   Output: 1
   Explanation: Subarray with XOR = 5 is [5]
3. Input: A = [1, 2, 3], K = 10
   Output: 0
   Explanation: No subarray has XOR = 10
4. Input: A = [6], K = 6
   Output: 1
   Explanation: Subarray with XOR = 6 is [6]

Constraints:
- 1 <= A.size() <= 10^5
- 0 <= A[i], K <= 10^9

Edge Cases:
- Empty array: Return 0.
- No subarray with XOR = K: Return 0.
- Single element equal to K: Count it as a subarray.
- Large inputs: Ensure efficient computation for arrays up to 10^5 elements.
- K = 0: Count subarrays where all elements XOR to 0.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Iterate over all possible subarrays using two nested loops.
- Compute the XOR of elements in each subarray.
- If the XOR equals K, increment a counter.

Thought Process:
- A subarray is defined by a starting index i and an ending index j.
- For each subarray [i, j], compute the XOR of elements from arr[i] to arr[j].
- If the XOR equals K, it contributes to the count.
- This approach is straightforward but computationally expensive due to checking all subarrays.

Algorithm:
1. Initialize count = 0.
2. For each index i from 0 to n-1:
   - Initialize xor_result = 0.
   - For each index j from i to n-1:
     - Update xor_result ^= arr[j].
     - If xor_result == K, increment count.
3. Return count.

Time Complexity: O(n^2)
- Two nested loops iterate over all possible subarrays: O(n^2).
- XOR operation is O(1) per element.

Space Complexity: O(1)
- Only uses a constant amount of extra space (variables count and xor_result).

Limitations:
- Inefficient for large arrays (up to 10^5 elements) due to quadratic time complexity.
- Does not leverage XOR properties to reduce computations.

Trade-offs:
- Simple to implement and understand but impractical for large inputs.
- No additional space required, unlike the optimal approach.

----------------------------------------
Approach 2: Optimal (Prefix XOR with Hash Map)
----------------------------------------
Logic:
- Use the prefix XOR technique: The XOR of a subarray [i+1, j] equals K if prefix_xor[j] ^ prefix_xor[i] = K.
- This implies prefix_xor[i] = prefix_xor[j] ^ K.
- Store the frequency of prefix XORs in a hash map.
- For each index j:
  - If prefix_xor[j] == K, count the subarray from 0 to j.
  - If prefix_xor[j] ^ K exists in the map, add its frequency to the count (subarrays ending at j).

Thought Process:
- The XOR operation is associative and commutative, and a ^ a = 0.
- If we compute prefix XORs (XOR of all elements up to index i), the XOR of a subarray [i+1, j] is prefix_xor[j] ^ prefix_xor[i].
- To find subarrays with XOR = K, we need prefix_xor[j] ^ prefix_xor[i] = K, or prefix_xor[i] = prefix_xor[j] ^ K.
- Use a hash map to store the frequency of prefix XORs and check for prefix_xor[j] ^ K.
- Initialize the map with {0, 1} to handle subarrays starting at index 0.

Algorithm:
1. Initialize count = 0, prefix_xor = 0, and an unordered_map to store prefix_xor -> frequency.
2. Insert {0, 1} into the map to account for subarrays starting at index 0.
3. Iterate through the array (index i):
   - Update prefix_xor ^= arr[i].
   - If prefix_xor == K, increment count (subarray from 0 to i).
   - Add the frequency of prefix_xor ^ K to count (subarrays ending at i).
   - Increment the frequency of prefix_xor in the map.
4. Return count.

Time Complexity: O(n)
- Single pass through the array: O(n).
- Unordered_map operations (insert, find) are O(1) on average.

Space Complexity: O(n)
- Hash map stores at most n prefix XORs.

Why Optimal:
- Reduces time complexity from O(n^2) to O(n) by using a hash map to track prefix XORs, avoiding the need to compute XOR for each subarray.
- Efficiently handles large inputs (up to 10^5 elements).
- Leverages XOR properties to simplify the problem to a prefix-based solution.

Trade-offs:
- Requires O(n) extra space for the hash map, unlike the brute force approach.
- Assumes hash map operations are O(1) on average, which could degrade in rare cases due to hash collisions.
- Slightly more complex to understand than brute force but far more efficient.

Limitations:
- Potential integer overflow for very large XOR values, mitigated by using long long for prefix_xor.
- Memory usage grows with array size, which may be a concern for very large inputs.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Approach 1: Brute Force
int countSubarraysWithXorKBruteForce(const vector<int>& arr, const int K) {
    int count = 0;
    int n = arr.size();

    // Handle empty array
    if (n == 0) return 0;

    // Iterate over all possible subarrays
    for (int i = 0; i < n; i++) {
        int xor_result = 0; // Initialize XOR for current subarray
        for (int j = i; j < n; j++) {
            xor_result ^= arr[j]; // Compute XOR of subarray [i, j]
            if (xor_result == K) {
                count++; // Increment count if XOR equals K
            }
        }
    }

    return count;
}

// Approach 2: Optimal (Prefix XOR with Hash Map)
int countSubarraysWithXorKOptimal(const vector<int>& arr, const int K) {
    int xr = 0;
    map<int,int> mp;
    mp[xr]++; /// {0,1}
    int cnt = 0;
    for(int i = 0; i < arr.size(); i++) {
        xr = xr ^ arr[i];
        int x = xr ^ K;
        cnt += mp[x];
        mp[xr]++;
    }
    return cnt;
}

// Main function to test the implementations
int main() {
    // Test cases
    vector<pair<vector<int>, int>> test_cases = {
        {{4, 2, 2, 6, 4}, 6},           // Expected: 4
        {{5, 6, 7, 8, 9}, 5},           // Expected: 1
        {{1, 2, 3}, 10},                // Expected: 0
        {{}, 5},                        // Expected: 0
        {{6}, 6},                       // Expected: 1
        {{1, 1, 1}, 1},                 // Expected: 3
        {{0, 0, 0}, 0}                  // Expected: 6
    };

    for (int i = 0; i < test_cases.size(); i++) {
        cout << "Test case " << i + 1 << ": arr = [";
        for (int x : test_cases[i].first) cout << x << " ";
        cout << "], K = " << test_cases[i].second << "\n";

        // Test Brute Force Approach
        int result_brute = countSubarraysWithXorKBruteForce(test_cases[i].first, test_cases[i].second);
        cout << "Brute Force Result: " << result_brute << "\n";

        // Test Optimal Approach
        int result_optimal = countSubarraysWithXorKOptimal(test_cases[i].first, test_cases[i].second);
        cout << "Optimal Result: " << result_optimal << "\n\n";
    }

    return 0;
}