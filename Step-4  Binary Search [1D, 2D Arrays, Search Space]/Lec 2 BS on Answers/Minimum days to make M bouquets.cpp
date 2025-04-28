#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Minimum Days to Make M Bouquets
You are given N roses and an array arr where arr[i] denotes the day the ith rose blooms.
You can pick only adjacent bloomed roses to make a bouquet, requiring exactly k adjacent
bloomed roses per bouquet. Find the minimum number of days to make at least m bouquets.
Return -1 if impossible.

Example 1:
Input: N = 8, arr = {7, 7, 7, 7, 13, 11, 12, 7}, m = 2, k = 3
Output: 12
Explanation: On day 12, roses at indices 0-3 and 5-7 are bloomed, allowing two bouquets.

Example 2:
Input: N = 5, arr = {1, 10, 3, 10, 2}, m = 3, k = 2
Output: -1
Explanation: Not enough adjacent roses to make 3 bouquets.

Constraints:
- 1 <= N <= 10^5 (number of roses)
- 1 <= arr[i] <= 10^9 (blooming day)
- 1 <= m <= 10^6 (number of bouquets)
- 1 <= k <= N (roses per bouquet)

Edge Cases:
- m * k > N: Impossible due to insufficient roses.
- Empty array or invalid inputs (e.g., negative days).
- All roses bloom on the same day.
- No adjacent roses bloom by the required day.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Iterate through all possible days from min(arr) to max(arr).
- For each day, check if it's possible to make m bouquets with k adjacent roses.
- The first day where possible() returns true is the answer.

Algorithm:
1. If m * k > N, return -1 (insufficient roses).
2. Find min and max blooming days in arr.
3. For each day from min to max:
   - Call possible(arr, m, k, day) to check if m bouquets can be made.
   - If true, return the day.
4. If no day works, return -1.

Time Complexity: O((max(arr) - min(arr) + 1) * N)
- Loop over range [min(arr), max(arr)]: O(max(arr) - min(arr)).
- For each day, possible() scans the array: O(N).
Space Complexity: O(1), no extra space.

Limitations:
- Highly inefficient for large ranges of blooming days (e.g., max(arr) = 10^9).
- Redundant checks for many days that are unlikely to be the answer.

----------------------------------------
Approach 2: Optimal (Binary Search)
----------------------------------------
Logic:
- The answer lies in the range [min(arr), max(arr)], which is sorted.
- Use binary search to find the smallest day where possible() returns true.
- For each mid day, check if m bouquets can be made:
  - If true, try a smaller day (left half).
  - If false, try a larger day (right half).

Algorithm:
1. If m * k > N, return -1.
2. Find min and max blooming days in arr.
3. Initialize low = min(arr), high = max(arr).
4. While low <= high:
   - Compute mid = low + (high - low) / 2.
   - If possible(arr, m, k, mid):
     - Answer might be mid or smaller, so high = mid - 1.
   - Else:
     - Need more days, so low = mid + 1.
5. Return low if valid, else -1.

Time Complexity: O(log(max(arr) - min(arr)) * N)
- Binary search reduces range to O(log(max(arr) - min(arr))).
- Each possible() call takes O(N).
Space Complexity: O(1), no extra space.

Why Optimal?
- Binary search drastically reduces the number of days checked from O(max(arr) - min(arr))
  to O(log(max(arr) - min(arr))).
- Efficient for large ranges (e.g., max(arr) = 10^9).
- Maintains simplicity with minimal space.

Trade-offs:
- Slightly more complex to implement than brute force.
- Still requires O(N) per possible() call, but this is unavoidable for checking adjacency.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Helper function to check if m bouquets can be made by day 'day'
bool possible(const vector<int>& arr, int m, int k, int day) {
    int n = arr.size();
    int cnt = 0;      // Count of consecutive bloomed roses
    int noofB = 0;    // Number of bouquets formed

    for (int i = 0; i < n; i++) {
        if (arr[i] <= day) {
            cnt++;    // Rose has bloomed, increment consecutive count
        } else {
            noofB += cnt / k; // Form bouquets from previous consecutive roses
            cnt = 0;          // Reset count for non-bloomed rose
        }
    }
    noofB += cnt / k; // Check final segment of consecutive roses
    return noofB >= m; // Return true if enough bouquets can be made
}

// Approach 1: Brute Force
int minDaysBruteForce(int N, const vector<int>& arr, int m, int k) {
    // Edge case: insufficient roses
    if (m * k > N) return -1;

    // Find min and max blooming days
    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        mini = min(mini, arr[i]);
        maxi = max(maxi, arr[i]);
    }

    // Check each day from min to max
    for (int day = mini; day <= maxi; day++) {
        if (possible(arr, m, k, day)) {
            return day; // First valid day is the answer
        }
    }
    return -1; // No valid day found
}

// Approach 2: Optimal (Binary Search)
int minDaysOptimal(int N, const vector<int>& arr, int m, int k) {
    // Edge case: insufficient roses
    if (m * k > N) return -1;

    // Find min and max blooming days
    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        mini = min(mini, arr[i]);
        maxi = max(maxi, arr[i]);
    }

    // Binary search on the answer range
    int low = mini, high = maxi;
    while (low <= high) {
        int mid = low + (high - low) / 2; // Avoid overflow
        if (possible(arr, m, k, mid)) {
            high = mid - 1; // Try earlier days
        } else {
            low = mid + 1;  // Need more days
        }
    }
    // low is the first day where possible() is true, or invalid
    return (low <= maxi && possible(arr, m, k, low)) ? low : -1;
}

int main() {
    // Test Case 1
    int N1 = 8;
    vector<int> arr1 = {7, 7, 7, 7, 13, 11, 12, 7};
    int m1 = 2, k1 = 3;
    cout << "Test Case 1 (Brute Force): " << minDaysBruteForce(N1, arr1, m1, k1) << endl;
    cout << "Test Case 1 (Optimal): " << minDaysOptimal(N1, arr1, m1, k1) << endl;

    // Test Case 2
    int N2 = 5;
    vector<int> arr2 = {1, 10, 3, 10, 2};
    int m2 = 3, k2 = 2;
    cout << "Test Case 2 (Brute Force): " << minDaysBruteForce(N2, arr2, m2, k2) << endl;
    cout << "Test Case 2 (Optimal): " << minDaysOptimal(N2, arr2, m2, k2) << endl;

    return 0;
}