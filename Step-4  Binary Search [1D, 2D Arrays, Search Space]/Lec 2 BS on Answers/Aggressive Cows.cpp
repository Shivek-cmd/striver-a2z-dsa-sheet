#include <bits/stdc++.h>
using namespace std;

/*

==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Aggressive Cows
You are given an array 'arr' of size 'n' which denotes the position of stalls.
You are also given an integer 'k' which denotes the number of aggressive cows.
The task is to assign stalls to 'k' cows such that the minimum distance between any two
of them is the maximum possible. Find the maximum possible minimum distance.

Examples:
Example 1:
Input: N = 6, k = 4, arr[] = {0,3,4,7,10,9}
Output: 3
Explanation: The maximum possible minimum distance between any two cows will be 3
when 4 cows are placed at positions {0, 3, 7, 10}. Here the distances between cows
are 3, 4, and 3 respectively. We cannot make the minimum distance greater than 3 in
any ways.

Example 2:
Input: N = 5, k = 2, arr[] = {4,2,1,3,6}
Output: 5
Explanation: The maximum possible minimum distance between any two cows will be 5
when 2 cows are placed at positions {1, 6}.

Constraints:
- 2 <= N <= 10^5
- 2 <= k <= N
- 0 <= arr[i] <= 10^9
- All elements in arr[] are unique.

Edge Cases:
- k == 2 (place cows at the minimum and maximum stall positions)
- k == N (each cow gets one stall, minimum distance is the smallest gap)
- Large gaps between stall positions
- k > N (invalid case, cannot place more cows than stalls)

==============================================================================
Section 1: Observation:
==============================================================================

To maximize the minimum distance between any two cows placed in the stalls, we need to strategically assign the cows to the stalls.
Key insights guide our approach:

Why do we need to sort the stalls?
Sorting the stalls by their positions ensures that we can efficiently calculate distances between potential cow placements. 
In a sorted array, the minimum distance between any two cows will always be determined by the smallest gap between their assigned stalls.
 By sorting, we simplify the problem of checking whether a given minimum distance is feasible, as we can place cows in a way that respects
  the order of stalls without needing to consider non-consecutive arrangements explicitly.

Why does the answer lie in the range [1, max(stalls[])-min(stalls[])]?
- Minimum possible distance: The smallest possible distance between any two cows is 1, as this is the smallest gap that could exist between
 two consecutive stalls in the sorted array,
 Any distance less than 1 is not possible since stalls are at distinct positions.
- Maximum possible distance: The largest possible minimum distance occurs when we place the k cows as far apart as possible.
 For k=2, placing cows at the first and last stalls (after sorting) gives the distance max(stalls[])-min(stalls[]), which is the range 
 of the stall positions. For k>2, the minimum distance will be smaller, as we need to fit more cows, but it will never exceed this range.
  Thus, the maximum possible minimum distance is bounded by max(stalls[])-min(stalls[]).

============================================================================================================================
From these observations, the answer (the maximum possible minimum distance) lies in the range [1, max(stalls[])-min(stalls[])].
=============================================================================================================================


To check if a given distance 'dist' is feasible, we can use a function canWePlace(stalls, dist, k):
- Place the first cow at the first stall (stalls[0]).
- Iterate through the sorted stalls, placing a cow at a stall if it is at least 'dist' away from the last placed cow.
- If we can place all k cows, the distance is feasible; otherwise, it is not.

This observation sets up the problem for both linear and binary search approaches to find the largest feasible distance.
*/
struct Solution {
    /*
==============================================================================
    Section 2: Solution Approaches
==============================================================================

    Helper Function: canWePlace(stalls, dist, k)
    - Input: stalls array (sorted), distance to maintain, number of cows (k)
    - Output: True if k cows can be placed with at least 'dist' between them, else false
    - Logic: Place first cow at stalls[0]. Iterate through stalls, placing a cow if the
      distance from the last placed cow is >= dist. Track number of cows placed.
    - Time Complexity: O(N), where N is stalls.size()
    - Space Complexity: O(1)

    --------------------------------------
    Approach 1: Naive (Linear Search)
    --------------------------------------
    Logic:
    - From observation, the answer lies in [1, max(stalls[])-min(stalls[])].
    - Iterate through all possible distances from 1 to max(stalls[])-min(stalls[]).
    - For each distance, check if k cows can be placed using canWePlace().
    - Return the largest distance where canWePlace() returns true.

    Algorithm:
    1. Sort the stalls array.
    2. For dist = 1 to (stalls[n-1] - stalls[0]):
        a. If canWePlace(stalls, dist, k) is false, return (dist-1).
    3. Return (stalls[n-1] - stalls[0]) if all distances are valid.

    Time Complexity: O(NlogN) + O(N * (max(stalls[])-min(stalls[])))
    - Sorting: O(NlogN).
    - Linear search over distances, each calling canWePlace(): O(N * range).
    Space Complexity: O(1)
    Limitations:
    - Inefficient for large ranges (e.g., max(stalls[])-min(stalls[]) = 10^9).
    - Checks many unnecessary distances.

    --------------------------------------
    Approach 2: Optimal (Binary Search)
    --------------------------------------
    Logic:
    - The search space [1, max(stalls[])-min(stalls[])] is sorted, as larger distances
      are harder to achieve.
    - Use binary search to find the largest distance where canWePlace() returns true.
    - For each mid-point distance:
      - If canWePlace(mid) is true, try a larger distance (left half eliminated).
      - Else, try a smaller distance (right half eliminated).
    - Binary search converges to the maximum valid distance.

    Algorithm:
    1. Sort the stalls array.
    2. Initialize low = 1, high = stalls[n-1] - stalls[0].
    3. While low <= high:
        a. Compute mid = low + (high - low) / 2.
        b. If canWePlace(stalls, mid, k) is true:
           - Search right half (low = mid + 1).
        c. Else, search left half (high = mid - 1).
    4. Return high (points to the largest valid distance).

    Time Complexity: O(NlogN) + O(N * log(max(stalls[])-min(stalls[])))
    - Sorting: O(NlogN).
    - Binary search over range, each calling canWePlace(): O(N * log(range)).
    Space Complexity: O(1)
    Why Optimal?
    - Reduces the number of distances checked from linear to logarithmic.
    - Efficient for large ranges of possible distances.

    Trade-offs:
    - Binary search is slightly more complex to implement.
    - Still requires O(N) per check, but far fewer checks overall.
    */

    // Helper function to check if k cows can be placed with at least dist between them
    bool canWePlace(vector<int>& stalls, int dist, int k) {
        int n = stalls.size();
        int cntCows = 1; // Place first cow at stalls[0]
        int last = stalls[0]; // Position of last placed cow

        for (int i = 1; i < n; i++) {
            if (stalls[i] - last >= dist) {
                cntCows++; // Place next cow
                last = stalls[i]; // Update last position
            }
            if (cntCows >= k) {
                return true; // All k cows placed
            }
        }
        return false; // Could not place k cows
    }

    /*
    ==============================================================================
    Section 3: Code Implementation
    ==============================================================================
    */

    // Approach 1: Naive (Linear Search)
    int aggressiveCowsNaive(vector<int>& stalls, int k) {
        int n = stalls.size();
        if (k > n) return -1; // Edge case: more cows than stalls

        // Sort stalls
        vector<int> sortedStalls = stalls; // Copy to avoid modifying input
        sort(sortedStalls.begin(), sortedStalls.end());

        int limit = sortedStalls[n - 1] - sortedStalls[0];
        for (int dist = 1; dist <= limit; dist++) {
            if (!canWePlace(sortedStalls, dist, k)) {
                return dist - 1; // Largest distance where placement was possible
            }
        }
        return limit; // All distances up to limit are valid
    }

    // Approach 2: Optimal (Binary Search)
    int aggressiveCowsOptimal(vector<int>& stalls, int k) {
        int n = stalls.size();
        if (k > n) return -1; // Edge case: more cows than stalls

        // Sort stalls
        vector<int> sortedStalls = stalls; // Copy to avoid modifying input
        sort(sortedStalls.begin(), sortedStalls.end());

        int low = 1; // Minimum possible distance
        int high = sortedStalls[n - 1] - sortedStalls[0]; // Maximum possible distance
        int result = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Avoid overflow
            if (canWePlace(sortedStalls, mid, k)) {
                result = mid; // Valid distance, try larger
                low = mid + 1;
            } else {
                high = mid - 1; // Try smaller distance
            }
        }
        return result; // Largest valid distance
    }
};

/*
Main function to test the solution
*/
int main() {
    Solution sol;

    // Test Case 1
    vector<int> stalls1 = {0, 3, 4, 7, 10, 9};
    int k1 = 4;
    cout << "Test Case 1 (Naive): " << sol.aggressiveCowsNaive(stalls1, k1) << endl;
    cout << "Test Case 1 (Optimal): " << sol.aggressiveCowsOptimal(stalls1, k1) << endl;

    // Test Case 2
    vector<int> stalls2 = {4, 2, 1, 3, 6};
    int k2 = 2;
    cout << "Test Case 2 (Naive): " << sol.aggressiveCowsNaive(stalls2, k2) << endl;
    cout << "Test Case 2 (Optimal): " << sol.aggressiveCowsOptimal(stalls2, k2) << endl;

    // Edge Case: k == N
    vector<int> stalls3 = {1, 2, 3, 4};
    int k3 = 4;
    cout << "Edge Case (k == N): " << sol.aggressiveCowsOptimal(stalls3, k3) << endl;

    // Edge Case: k > N
    vector<int> stalls4 = {1, 2, 3};
    int k4 = 5;
    cout << "Edge Case (k > N): " << sol.aggressiveCowsOptimal(stalls4, k4) << endl;

    return 0;
}

/*
Expected Output:
Test Case 1 (Naive): 3
Test Case 1 (Optimal): 3
Test Case 2 (Naive): 5
Test Case 2 (Optimal): 5
Edge Case (k == N): 1
Edge Case (k > N): -1
*/