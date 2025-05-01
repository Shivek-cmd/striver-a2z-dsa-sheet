#include <bits/stdc++.h>
using namespace std;

/* Painter's Partition Problem
Given an array of length N, where the array represents boards and each element
denotes the length of a board. K painters are available to paint these boards,
where each unit of a board takes 1 unit of time to paint. Return the minimum
time to paint all N boards, with the constraint that each painter paints
continuous sections of boards.

Example 1:
Input: N = 4, boards = [5, 5, 5, 5], k = 2
Output: 10
Explanation: Divide boards into two equal partitions (5+5, 5+5). Each painter
takes 10 units of time, so total time is 10.

Example 2:
Input: N = 4, boards = [10, 20, 30, 40], k = 2
Output: 60
Explanation: Assign first three boards (10+20+30=60) to one painter and the
last board (40) to another. Total time is max(60, 40) = 60.

Constraints:
- 1 <= N <= 10^5 (number of boards)
- 1 <= boards[i] <= 10^9 (length of each board)
- 1 <= k <= N (number of painters)
Edge Cases:
- k = 1: One painter paints all boards (sum of all board lengths).
- k = N: Each painter paints one board (max of board lengths).
- Empty boards or invalid k (k > N).
*/

/* 

==============================================================================
Observations:
==============================================================================

1. Problem Nature: Optimization problem to minimize the maximum time taken by any
   painter, with painters working on contiguous board sections.
2. Key Constraint: Painters cannot split a board; each painter's work is a
   contiguous subarray.
3. Solution Range:
   - Minimum time: When k = N, each painter gets one board (max(boards)).
   - Maximum time: When k = 1, one painter paints all boards (sum(boards)).
   - Answer lies in [max(boards), sum(boards)].
4. Decision Problem: For a time T, can we assign boards to k or fewer painters
   such that no painter exceeds T? Suggests binary search.
5. Greedy Allocation: To test time T, greedily assign boards to painters while
   ensuring each painter's sum does not exceed T.
6. Edge Cases:
   - k > N: Invalid input.
   - k = 1: Answer is sum(boards).
   - k = N: Answer is max(boards).
7. Pattern: Similar to "Split Array Largest Sum," suitable for binary search.
These observations guide toward a binary search solution with greedy validation.
*/

/*

==============================================================================
Approach 1: Brute Force
==============================================================================

Logic:
- Check every possible time T from max(boards) to sum(boards).
- For each T, use a helper function to count the number of painters needed.
- The first T where the number of painters is <= k is the answer.
Steps:
1. Compute max(boards) and sum(boards).
2. For T from max(boards) to sum(boards):
   a. If countPainters(boards, T) <= k, return T.
3. Return max(boards) for edge cases.
Time Complexity: O(N * (sum(boards) - max(boards) + 1))
- N iterations in countPainters, repeated for each T.
Space Complexity: O(1) - Constant space.
Limitations:
- Inefficient for large sum(boards) (up to 10^14).
- Linear search over a large range is slow.
*/

/*
==============================================================================
Approach 2: Optimal (Binary Search)
==============================================================================

Logic:
- Use binary search to find the smallest T in [max(boards), sum(boards)] where
  countPainters(boards, T) <= k.
- If countPainters > k, T is too small (search higher).
- If countPainters <= k, T is feasible (try lower to minimize).
Steps:
1. Set low = max(boards), high = sum(boards).
2. Binary search:
   a. Compute mid = (low + high) / 2.
   b. If countPainters(boards, mid) > k, set low = mid + 1.
   c. Else, set high = mid - 1.
3. Return low as the smallest feasible time.
Time Complexity: O(N * log(sum(boards) - max(boards) + 1))
- Binary search takes O(log(sum - max)) iterations.
- Each iteration calls countPainters (O(N)).
Space Complexity: O(1) - Constant space.
Why Optimal:
- Binary search reduces iterations from linear to logarithmic.
- Efficient for large ranges.
Trade-offs:
- Slightly more complex than brute force but far faster.
*/

/* Helper function to count painters needed for a given time limit */
int countPainters(const vector<int>& boards, long long time) {
    int painters = 1; /* Start with one painter */
    long long currentSum = 0; /* Track sum for current painter */
    for (int board : boards) {
        if (board > time) { /* Single board exceeds time, impossible */
            return INT_MAX;
        }
        if (currentSum + board <= time) {
            currentSum += board; /* Add board to current painter */
        } else {
            painters++; /* Start new painter */
            currentSum = board; /* New painter starts with this board */
        }
    }
    return painters;
}

/* Brute Force Implementation */
long long minTimeToPaintBrute(const vector<int>& boards, int k) {
    if (boards.empty() || k < 1 || k > boards.size()) {
        return -1; /* Invalid input */
    }
    long long maxBoard = *max_element(boards.begin(), boards.end());
    long long totalSum = accumulate(boards.begin(), boards.end(), 0LL);
    for (long long time = maxBoard; time <= totalSum; time++) {
        if (countPainters(boards, time) <= k) {
            return time; /* First feasible time */
        }
    }
    return maxBoard; /* Fallback for edge cases */
}

/* Optimal Implementation (Binary Search) */
long long minTimeToPaintOptimal(const vector<int>& boards, int k) {
    if (boards.empty() || k < 1 || k > boards.size()) {
        return -1; /* Invalid input */
    }
    long long low = *max_element(boards.begin(), boards.end());
    long long high = accumulate(boards.begin(), boards.end(), 0LL);
    while (low <= high) {
        long long mid = low + (high - low) / 2; /* Avoid overflow */
        int painters = countPainters(boards, mid);
        if (painters > k) {
            low = mid + 1; /* Need more time */
        } else {
            high = mid - 1; /* Try less time */
        }
    }
    return low; /* Smallest feasible time */
}

/* Main function to test both approaches */
int main() {
    vector<int> boards = {10, 20, 30, 40};
    int k = 2;
    cout << "Brute Force: " << minTimeToPaintBrute(boards, k) << endl;
    cout << "Optimal: " << minTimeToPaintOptimal(boards, k) << endl;
    return 0;
}