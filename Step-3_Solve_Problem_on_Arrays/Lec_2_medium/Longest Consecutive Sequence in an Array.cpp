/*
Problem: Given an array of ‘N’ integers, find the length of the longest sequence 
which contains the consecutive elements.

Example 1:
Input: [100, 200, 1, 3, 2, 4]
Output: 4
Explanation: The longest consecutive subsequence is 1, 2, 3, and 4.

Example 2:
Input: [3, 8, 5, 7, 6]
Output: 4
Explanation: The longest consecutive subsequence is 5, 6, 7, and 8.
*/

// Approach 1: Brute Force
/*
The brute-force method involves checking for each element if there is a consecutive number greater than the current one. 
For each element, keep increasing the length as long as consecutive elements exist in the array. 
At the end of the iteration, return the maximum length found.

Time Complexity: O(N^2) 
Explanation: For each element, we are searching for the next consecutive element using linear search, which takes O(N).
Space Complexity: O(1) (since we are only using a constant amount of space)
*/

// Approach 2: Better Approach (Sorting)
/*
We can improve this by sorting the array first and then checking for consecutive elements. 
After sorting, if the next element in the array is exactly 1 greater than the current element, we increase the current sequence length.
Skip duplicates because consecutive subsequences cannot contain duplicates.
Return the maximum sequence length at the end.

Time Complexity: O(N log N) for sorting the array and O(N) for a single scan of the sorted array.
Space Complexity: O(1) (if we sort in-place) or O(N) (if we use extra space for sorting).
*/

// Approach 3: Optimal Approach (Using a Hash Set)
/*
To achieve a more efficient solution, we can use a hash set to store all the elements in the array. 
The idea is to find a sequence starting from a number that has no smaller element (i.e., num-1 does not exist).
Once we find the starting element, we can use the hash set to find consecutive elements (num+1, num+2, etc.) in O(1) time.
This approach avoids checking every element and narrows down the search.

Time Complexity: O(N) for inserting all elements into the set and checking the consecutive elements.
Space Complexity: O(N) for the hash set to store all elements.
*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Brute Force Solution
int longestConsecutiveSequenceBruteForce(vector<int>& arr) {
    int max_length = 1;
    for (int i = 0; i < arr.size(); i++) {
        int x = arr[i];
        int curr_length = 1;
        while (find(arr.begin(), arr.end(), x + 1) != arr.end()) {
            x = x + 1;
            curr_length++;
        }
        max_length = max(max_length, curr_length);
    }
    return max_length;
}

// Approach 2: Sorting Solution
int longestConsecutiveSequenceSorting(vector<int>& arr) {
    if (arr.empty()) return 0;

    sort(arr.begin(), arr.end());
    int max_length = 1, curr_length = 1;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] == arr[i - 1] + 1) {
            curr_length++;
        } else if (arr[i] != arr[i - 1]) {
            max_length = max(max_length, curr_length);
            curr_length = 1;
        }
    }
    return max(max_length, curr_length);
}

// Approach 3: Optimal Solution Using Hash Set
int longestConsecutiveSequenceOptimal(vector<int>& arr) {
    if (arr.empty()) return 0;  // Edge case for empty array

    unordered_set<int> numSet(arr.begin(), arr.end());  // Insert all elements into a set
    int max_length = 0;

    for (int num : numSet) {
        // Check if it's the start of a potential sequence
        if (numSet.find(num - 1) == numSet.end()) {  // Ensure this is the first element in the sequence
            int current_num = num;
            int current_length = 1;

            // Look for consecutive numbers starting from num
            while (numSet.find(current_num + 1) != numSet.end()) {
                current_num++;
                current_length++;
            }

            // Update max_length if the current sequence is longer
            max_length = max(max_length, current_length);
        }
    }

    return max_length;
}

int main() {
    vector<int> nums1 = {100, 200, 1, 3, 2, 4};
    vector<int> nums2 = {3, 8, 5, 7, 6};

    // Testing Brute Force approach
    cout << "Brute Force - Length of longest consecutive subsequence in nums1: " << longestConsecutiveSequenceBruteForce(nums1) << endl;
    cout << "Brute Force - Length of longest consecutive subsequence in nums2: " << longestConsecutiveSequenceBruteForce(nums2) << endl;

    // Testing Sorting approach
    cout << "Sorting - Length of longest consecutive subsequence in nums1: " << longestConsecutiveSequenceSorting(nums1) << endl;
    cout << "Sorting - Length of longest consecutive subsequence in nums2: " << longestConsecutiveSequenceSorting(nums2) << endl;

    // Testing Optimal approach
    cout << "Optimal - Length of longest consecutive subsequence in nums1: " << longestConsecutiveSequenceOptimal(nums1) << endl;
    cout << "Optimal - Length of longest consecutive subsequence in nums2: " << longestConsecutiveSequenceOptimal(nums2) << endl;

    return 0;
}
