#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Merge Overlapping Intervals
Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping 
intervals and return an array of non-overlapping intervals that cover all intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap, so merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] overlap, so merge them into [1,5].

Constraints:
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= start_i <= end_i <= 10^4

Edge Cases:
- Empty input array
- Single interval
- Non-overlapping intervals
- Intervals with same start or end points
- Fully overlapping intervals
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Sort intervals by start time to group overlapping intervals together.
- For each interval, check all subsequent intervals for overlap.
- If an overlap is found, merge by updating the end time to the maximum of the two ends.
- Skip merged intervals to avoid duplicate processing.
- Store non-overlapping intervals in the result.

Steps:
1. Sort intervals by start time.
2. Iterate through each interval i:
   a. If result is empty or current interval doesn't overlap with last merged interval, 
      add it to result.
   b. For each subsequent interval j:
      - If j's start <= end of interval i, merge by updating end to max(end_i, end_j).
      - Mark j as processed to skip it later.
3. Return result.

Time Complexity: O(N*logN) + O(N^2)
- Sorting: O(N*logN).
- Nested loops: In worst case, for each interval, we check all subsequent intervals, 
  leading to O(N^2).
Space Complexity: O(N) for the result array.

Limitations:
- Inefficient for large inputs due to nested loops.
- Redundant checks for intervals that are already merged.

----------------------------------------
Approach 2: Optimal (Single Pass)
----------------------------------------
Logic:
- Sort intervals by start time to ensure overlapping intervals are adjacent.
- Use a single loop to process intervals, maintaining a result array.
- For each interval, either merge it with the last interval in result (if overlapping) 
  or append it (if non-overlapping).
- Merging involves updating the end time of the last interval to the maximum of the two ends.

Steps:
1. Sort intervals by start time.
2. Initialize an empty result array.
3. For each interval:
   a. If result is empty or current interval's start > last interval's end, append it.
   b. Else, update last interval's end to max(current end, last end).
4. Return result.

Time Complexity: O(N*logN) + O(N)
- Sorting: O(N*logN).
- Single loop: O(N) for iterating through intervals.
Space Complexity: O(N) for the result array.

Why Optimal?
- Eliminates nested loops by leveraging sorted order, ensuring each interval is processed 
  exactly once.
- Merging is done in-place in the result array, reducing redundant checks.
- Simpler logic with fewer operations.

Trade-offs:
- Requires sorting, which is unavoidable for correctness.
- Space complexity remains O(N) due to output requirements.
*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Function for Brute Force Approach
vector<vector<int>> mergeOverlappingIntervalsBrute(vector<vector<int>>& intervals) {
    // Handle empty input
    if (intervals.empty()) return {};
    
    int n = intervals.size();
    vector<vector<int>> result;
    vector<bool> processed(n, false); // Track merged intervals
    
    // Sort intervals by start time
    sort(intervals.begin(), intervals.end());
    
    // Process each interval
    for (int i = 0; i < n; i++) {
        if (processed[i]) continue; // Skip if already merged
        
        // Start with current interval
        int start = intervals[i][0];
        int end = intervals[i][1];
        
        // Check subsequent intervals for overlap
        for (int j = i + 1; j < n; j++) {
            if (processed[j]) continue;
            
            // If current interval's start <= end, merge
            if (intervals[j][0] <= end) {
                end = max(end, intervals[j][1]);
                processed[j] = true; // Mark as merged
            } else {
                break; // No more overlaps possible
            }
        }
        
        // Add merged interval to result
        result.push_back({start, end});
    }
    
    return result;
}

// Function for Optimal Approach
vector<vector<int>> mergeOverlappingIntervalsOptimal(vector<vector<int>>& intervals) {
    // Handle empty input
    if (intervals.empty()) return {};
    
    int n = intervals.size();
    vector<vector<int>> result;
    
    // Sort intervals by start time
    sort(intervals.begin(), intervals.end());
    
    // Process each interval
    for (int i = 0; i < n; i++) {
        // If result is empty or no overlap with last interval, append
        if (result.empty() || intervals[i][0] > result.back()[1]) {
            result.push_back(intervals[i]);
        } else {
            // Merge by updating end of last interval
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        }
    }
    
    return result;
}

// Main function to test both implementations
int main() {
    // Test case 1
    vector<vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Test Case 1 (Brute Force):\n";
    vector<vector<int>> ans1_brute = mergeOverlappingIntervalsBrute(intervals1);
    for (const auto& interval : ans1_brute) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << "\n";
    
    cout << "Test Case 1 (Optimal):\n";
    vector<vector<int>> ans1_optimal = mergeOverlappingIntervalsOptimal(intervals1);
    for (const auto& interval : ans1_optimal) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << "\n\n";
    
    // Test case 2
    vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
    cout << "Test Case 2 (Brute Force):\n";
    vector<vector<int>> ans2_brute = mergeOverlappingIntervalsBrute(intervals2);
    for (const auto& interval : ans2_brute) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << "\n";
    
    cout << "Test Case 2 (Optimal):\n";
    vector<vector<int>> ans2_optimal = mergeOverlappingIntervalsOptimal(intervals2);
    for (const auto& interval : ans2_optimal) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << "\n\n";
    
    // Edge case: Empty input
    vector<vector<int>> intervals3 = {};
    cout << "Edge Case: Empty Input (Optimal):\n";
    vector<vector<int>> ans3 = mergeOverlappingIntervalsOptimal(intervals3);
    if (ans3.empty()) cout << "[]\n";
    
    return 0;
}

/*
Output:
Test Case 1 (Brute Force):
[1, 6] [8, 10] [15, 18]
Test Case 1 (Optimal):
[1, 6] [8, 10] [15, 18]

Test Case 2 (Brute Force):
[1, 5]
Test Case 2 (Optimal):
[1, 5]

Edge Case: Empty Input (Optimal):
[]
*/