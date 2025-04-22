// Problem Statement:
// Given an array of N integers, find unique triplets that add up to give a sum of zero.
// You need to return an array of all the unique triplets [arr[a], arr[b], arr[c]] such that i != j, j != k, k != i, and their sum is equal to zero.
// [arr[1], arr[0], arr[2]] and [arr[0], arr[1], arr[2]] will be considered the same.

// Example 1: 

// Input: nums = [-1,0,1,2,-1,-4]

// Output: [[-1,-1,2],[-1,0,1]]

// Explanation: Out of all possible unique triplets possible, [-1,-1,2] and [-1,0,1] satisfy the condition of summing up to zero with i!=j!=k

// Example 2:

// Input: nums=[-1,0,1,0]
// Output: Output: [[-1,0,1],[-1,1,0]]
// Explanation: Out of all possible unique triplets possible, [-1,0,1] and [-1,1,0] satisfy the condition of summing up to zero with i!=j!=k


/*

-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------
- The steps are as follows:
    - Declare a set to store the unique triplets.
    - Use three nested loops to iterate over the array:
        - The first loop runs from 0 to n-1.
        - The second loop runs from i+1 to n-1.
        - The third loop runs from j+1 to n-1.
    - In each iteration, check if the sum of arr[i] + arr[j] + arr[k] is equal to 0.
    - If the sum is 0, sort the triplet and insert it into the set.
    - Return the list of unique triplets stored in the set.
    - Time complexity: O(n^3) because of three nested loops iterating over all triplets.
    - Space complexity: O(n) for storing the triplets in the set.

-----------------------------------------------------
Approach 2: Better Approach (Using HashSet for Third Element)
-----------------------------------------------------
- The steps are as follows:
    - Declare a set to store unique triplets.
    - Use two loops:
        - The first loop runs from 0 to n-1.
        - The second loop runs from i+1 to n-1.
    - Before the second loop, declare a HashSet to store the array elements between indices i and j.
    - In the second loop, calculate the third element as -(arr[i] + arr[j]).
    - If the third element exists in the HashSet, add the triplet to the set.
    - Insert arr[j] into the HashSet after checking.
    - Return the list of unique triplets stored in the set.
    - Time complexity: O(n^2) because of two nested loops, and each lookup/insert in the HashSet takes O(1) on average.
    - Space complexity: O(n) for storing elements in the HashSet.

-----------------------------------------------------
Approach 3: Optimal Approach (Using Sorting and Two Pointers)
-----------------------------------------------------
- The steps are as follows:
    - Sort the array to make the triplet checking efficient.
    - Use a loop (i) from 0 to n-1. In each iteration, the current value of i is fixed.
    - Skip duplicates of the current element (arr[i] == arr[i-1]).
    - Use two pointers:
        - One (j) starting from i+1.
        - The other (k) from the last index.
    - Move the pointers based on the sum of arr[i], arr[j], and arr[k]:
        - If the sum is greater than 0, move k to the left (k--).
        - If the sum is less than 0, move j to the right (j++).
        - If the sum equals 0, insert the triplet and skip duplicates by adjusting j and k.
    - Return the list of unique triplets.
    - Time complexity: O(n^2) because of the loop and the two-pointer approach, where each pair is processed at most once.
    - Space complexity: O(n) to store the triplets in the result list.
    */

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Brute Force
vector<vector<int>> tripletBruteForce(int n, vector<int>& arr) {
    set<vector<int>> st;

    // Check all possible triplets
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == 0) {
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }

    // Store the set elements in the answer
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Approach 2: Better Approach (Using HashSet for Third Element)
vector<vector<int>> tripletHashSet(int n, vector<int>& arr) {
    vector<vector<int>> result;
    set<vector<int>> s2; // To store unique triplets

    for (int i = 0; i < n - 2; i++) {
        set<int> s1; // Set to track elements we've seen so far
        for (int j = i + 1; j < n; j++) {
            int ele = -(arr[i] + arr[j]); // Find the third element needed to make sum 0
            if (s1.find(ele) != s1.end()) { // If the third element is in s1
                vector<int> ans = {arr[i], arr[j], ele}; // Form the triplet
                sort(ans.begin(), ans.end()); // Sort the triplet to avoid duplicates
                s2.insert(ans); // Insert the sorted triplet into the set
            }
            s1.insert(arr[j]); // Add the current element to s1
        }
    }

    // Convert the set of unique triplets to a vector
    result.assign(s2.begin(), s2.end());
    return result; // Return the result containing all unique triplets
}

// Approach 3: Optimal Approach (Using Sorting and Two Pointers)
vector<vector<int>> tripletOptimal(int n, vector<int>& arr) {
    vector<vector<int>> result;
    sort(arr.begin(), arr.end()); // Sort the array to enable two-pointer technique

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicates for the `i` index
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }

        int j = i + 1; // Start from the next element
        int k = n - 1; // Start from the end of the array

        while (j < k) {
            int sum = arr[i] + arr[j] + arr[k];

            if (sum < 0) {
                j++; // Increase the left pointer to increase the sum
            } else if (sum > 0) {
                k--; // Decrease the right pointer to decrease the sum
            } else {
                // Found a valid triplet
                result.push_back({arr[i], arr[j], arr[k]});

                // Skip duplicates for `j` and `k`
                while (j < k && arr[j] == arr[j + 1]) j++;
                while (j < k && arr[k] == arr[k - 1]) k--;

                // Move both pointers after handling duplicates
                j++;
                k--;
            }
        }
    }

    return result;
}

int main() {
    vector<int> arr = {-1, 0, 1, 2, -1, -4};
    int n = arr.size();

    // Function to print results
    auto printResult = [](const vector<vector<int>>& ans, const string& approach) {
        cout << approach << ":\n";
        if (ans.empty()) {
            cout << "No triplets found.\n";
        } else {
            for (auto it : ans) {
                cout << "[";
                for (auto i : it) {
                    cout << i << " ";
                }
                cout << "] ";
            }
            cout << "\n";
        }
        cout << "\n";
    };

    // Call and print results for Brute Force approach
    vector<vector<int>> ansBrute = tripletBruteForce(n, arr);
    printResult(ansBrute, "Brute Force Approach");

    // Call and print results for HashSet approach
    vector<vector<int>> ansHashSet = tripletHashSet(n, arr);
    printResult(ansHashSet, "HashSet Approach");

    // Call and print results for Optimal approach
    vector<vector<int>> ansOptimal = tripletOptimal(n, arr);
    printResult(ansOptimal, "Optimal (Two-Pointer) Approach");

    return 0;
}