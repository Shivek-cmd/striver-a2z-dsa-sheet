#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Problem Statement: Ship Within Days
==============================================================================
You own a shipment company that uses conveyor belts to ship packages from one port 
to another within 'd' days. The package weights are given in an array 'weights'. 
Each day, packages must be loaded in the same order as they appear, without exceeding 
the ship's weight capacity. Find the minimum ship capacity required to ship all 
packages within 'd' days.

Examples:
----------
Input: weights = {5,4,5,2,3,4,5,6}, d = 5
Output: 9

Input: weights = {1,2,3,4,5,6,7,8,9,10}, d = 1
Output: 55

Constraints:
------------
- 1 <= d <= weights.size() <= 10^5
- 1 <= weights[i] <= 500

Edge Cases:
------------
- Single package
- d == weights.size()
- d == 1 (one single day)
- Empty weights array
*/

/*

==============================================================================
Observation:
===============================================================================

Minimum ship capacity: The minimum ship capacity should be the maximum value in the 
given array. Let’s understand using an example. Assume the given weights array is
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} and the ship capacity is 8. Now in the question,
  it is clearly stated that the loaded weights in the ship must not exceed the maximum 
weight capacity of the ship. For this constraint, we can never ship the weights 9 and 10,
if the ship capacity is 8. That is why, in order to ship all the weights, the minimum ship
 capacity should be equal to the maximum of the weights array i.e. max(weights[]).
Maximum capacity: If the ship capacity is equal to the sum of all the weights, we can ship
 all goods within a single day. Any capacity greater than this will yield the same result.

 So, the maximum capacity will be the summation of all the weights i.e. sum(weights[]).
From the observations, it is clear that our answer lies in the range
 [max(weights[]), sum(weights[])].



==============================================================================
    Section 2: Solution Approaches
==============================================================================

    Helper Function: findDays(weights, capacity)
    - Input: weights array, ship capacity
    - Output: Number of days required to ship all packages with given capacity
    - Logic: Iterate through weights, accumulating weights until capacity is exceeded.
      When exceeded, increment day count and reset accumulated weight to current weight.
    - Time Complexity: O(N), where N is weights.size()
    - Space Complexity: O(1)

    --------------------------------------
    Approach 1: Naive (Linear Search)
    --------------------------------------
    Logic:
    - The minimum capacity is max(weights), as no package can exceed the ship's capacity.
    - The maximum capacity is sum(weights), which allows shipping all packages in one day.
    - Iterate through all possible capacities from max(weights) to sum(weights).
    - For each capacity, use findDays() to compute required days.
    - Return the smallest capacity where required days <= d.

    Algorithm:
    1. Compute max(weights) and sum(weights).
    2. For capacity = max(weights) to sum(weights):
        a. Call findDays(weights, capacity).
        b. If findDays() <= d, return capacity.
    3. Return -1 if no solution found.

    Time Complexity: O(N * (sum(weights) - max(weights) + 1))
    - N iterations in findDays(), called for each capacity in range.
    Space Complexity: O(1)
    Limitations:
    - Highly inefficient for large weight sums (e.g., sum(weights) = 10^5 * 500).
    - Performs redundant checks for many capacities.

    --------------------------------------
    Approach 2: Optimal (Binary Search)
    --------------------------------------
    Logic:
    - The search space [max(weights), sum(weights)] is sorted, as higher capacity always 
      reduces the number of days required.
    - Use binary search to find the smallest capacity where findDays(capacity) <= d.
    - For each mid-point capacity:
      - If findDays(mid) <= d, try a smaller capacity (right half eliminated).
      - Else, try a larger capacity (left half eliminated).
    - Binary search narrows down to the minimal valid capacity.

    Algorithm:
    1. Compute max(weights) and sum(weights).
    2. Initialize low = max(weights), high = sum(weights).
    3. While low <= high:
        a. Compute mid = low + (high - low) / 2.
        b. If findDays(weights, mid) <= d:
           - Update answer = mid, search left half (high = mid - 1).
        c. Else, search right half (low = mid + 1).
    4. Return answer.

    Time Complexity: O(N * log(sum(weights) - max(weights) + 1))
    - Binary search reduces range to log(sum(weights) - max(weights)).
    - Each iteration calls findDays(), which is O(N).
    Space Complexity: O(1)
    Why Optimal?
    - Reduces the number of capacities checked from linear to logarithmic.
    - Efficient for large ranges of possible capacities.

    Trade-offs:
    - Binary search is more complex to implement than linear search.
    - Still requires O(N) per check, but far fewer checks overall.
    */







/*
==============================================================================
Helper Class: Solution
==============================================================================
*/
struct Solution {
    // Helper function to find days needed for a given ship capacity
    int findDays(const vector<int>& weights, int capacity) {
        int days = 1;
        int currentLoad = 0;
        
        for (int weight : weights) {
            if (weight > capacity) {
                return INT_MAX; // Impossible to load
            }
            if (currentLoad + weight <= capacity) {
                currentLoad += weight;
            } else {
                days++;
                currentLoad = weight;
            }
        }
        return days;
    }

    // Naive Approach (Linear Search)
    int shipWithinDaysNaive(const vector<int>& weights, int d) {
        if (weights.empty()) return 0;
        if (d < 1) return -1;

        int maxWeight = *max_element(weights.begin(), weights.end());
        int sumWeights = accumulate(weights.begin(), weights.end(), 0);

        for (int capacity = maxWeight; capacity <= sumWeights; capacity++) {
            if (findDays(weights, capacity) <= d) {
                return capacity;
            }
        }
        return -1;
    }

    // Optimal Approach (Binary Search)
    int shipWithinDaysOptimal(const vector<int>& weights, int d) {
        if (weights.empty()) return 0;
        if (d < 1) return -1;

        int maxWeight = *max_element(weights.begin(), weights.end());
        int sumWeights = accumulate(weights.begin(), weights.end(), 0);

        int low = maxWeight, high = sumWeights;
        int result = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int daysNeeded = findDays(weights, mid);

            if (daysNeeded <= d) {
                result = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return result;
    }
};

/*
==============================================================================
Main Function: Driver Code
==============================================================================
*/
int main() {
    Solution sol;

    // Test Case 1
    vector<int> weights1 = {5, 4, 5, 2, 3, 4, 5, 6};
    int d1 = 5;
    cout << "Test Case 1 (Naive): " << sol.shipWithinDaysNaive(weights1, d1) << endl;
    cout << "Test Case 1 (Optimal): " << sol.shipWithinDaysOptimal(weights1, d1) << endl;

    // Test Case 2
    vector<int> weights2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int d2 = 1;
    cout << "Test Case 2 (Naive): " << sol.shipWithinDaysNaive(weights2, d2) << endl;
    cout << "Test Case 2 (Optimal): " << sol.shipWithinDaysOptimal(weights2, d2) << endl;

    // Edge Case: Single Package
    vector<int> weights3 = {10};
    int d3 = 1;
    cout << "Edge Case (Single Package): " << sol.shipWithinDaysOptimal(weights3, d3) << endl;

    // Edge Case: Empty Array
    vector<int> weights4 = {};
    int d4 = 1;
    cout << "Edge Case (Empty Array): " << sol.shipWithinDaysOptimal(weights4, d4) << endl;

    return 0;
}

/*
==============================================================================
Expected Output:
==============================================================================
Test Case 1 (Naive): 9
Test Case 1 (Optimal): 9
Test Case 2 (Naive): 55
Test Case 2 (Optimal): 55
Edge Case (Single Package): 10
Edge Case (Empty Array): 0
==============================================================================
*/
