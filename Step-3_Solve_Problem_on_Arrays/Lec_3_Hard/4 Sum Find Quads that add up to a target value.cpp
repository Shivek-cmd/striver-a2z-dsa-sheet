#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Given an array of N integers, your task is to find unique quads that add up to a target value. In short, you need to return an array of all the unique quadruplets [arr[a], arr[b], arr[c], arr[d]] such that their sum is equal to a given target. Note:
- 0 <= a, b, c, d < n
- a, b, c, and d are distinct.
- arr[a] + arr[b] + arr[c] + arr[d] == target

Example 1:
Input Format: arr[] = [1,0,-1,0,-2,2], target = 0
Result: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input Format: arr[] = [4,3,3,4,4,2,1,2,1,1], target = 9
Result: [[1,1,3,4],[1,2,2,4],[1,2,3,3]]
*/

/*
-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------
- Steps:
    - Declare a set to store the unique quadruplets.
    - Use four nested loops to iterate over the array:
        - The first loop runs from 0 to n-1.
        - The second loop runs from i+1 to n-1.
        - The third loop runs from j+1 to n-1.
        - The fourth loop runs from k+1 to n-1.
    - In each iteration, check if the sum of arr[i] + arr[j] + arr[k] + arr[l] is equal to the target.
    - If the sum is equal to the target, sort the quadruplet and insert it into the set to avoid duplicates.
    - Return the list of unique quadruplets stored in the set.
- Time complexity: O(n^4) because of four nested loops iterating over all possible quadruplets.
- Space complexity: O(n) for storing the quadruplets in the set.
    
-----------------------------------------------------
Approach 2: Better Approach (Using HashSet for Fourth Element)
-----------------------------------------------------
- Steps:
    - Declare a set to store unique quadruplets.
    - Use two loops:
        - The first loop runs from 0 to n-1.
        - The second loop runs from i+1 to n-1.
    - Before the second loop, declare a HashSet to store the array elements between indices i and j.
    - In the second loop, calculate the fourth element as `target - (arr[i] + arr[j] + arr[k])`.
    - If the fourth element exists in the HashSet, add the quadruplet to the set.
    - Insert arr[j] into the HashSet after checking.
    - Return the list of unique quadruplets stored in the set.
- Time complexity: O(N3*log(M)), where N = size of the array, M = no. of elements in the set.
- Space complexity: O(n) for storing elements in the HashSet.
    
-----------------------------------------------------
Approach 3: Optimal Approach (Using Sorting and Two Pointers)
-----------------------------------------------------
- Steps:
    - Sort the array to make the quadruplet checking efficient.
    - Use a loop (i) from 0 to n-4. In each iteration, the current value of `i` is fixed.
    - Skip duplicates of the current element (arr[i] == arr[i-1]).
    - Use another loop (j) from `i+1` to n-3. Again, skip duplicates of the current element (arr[j] == arr[j-1]).
    - Use two pointers:
        - One pointer (`k`) starting from `j+1`.
        - The other pointer (`l`) starting from the last index.
    - Move the pointers based on the sum of arr[i], arr[j], arr[k], and arr[l]:
        - If the sum is greater than the target, move `l` to the left (l--).
        - If the sum is less than the target, move `k` to the right (k++).
        - If the sum equals the target, insert the quadruplet and skip duplicates by adjusting both `k` and `l`.
    - Return the list of unique quadruplets.
- Time complexity: O(n^3) because of the loop and the two-pointer approach, where each pair is processed at most once.
- Space complexity: O(n) to store the quadruplets in the result list.
*/



#include <bits/stdc++.h>
using namespace std;

// Approach 1: Brute Force (O(n^4))
vector<vector<int>> fourSumBruteForce(int n, vector<int>& arr, int target) {
    set<vector<int>> st;

    // Check all possible quadruplets
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (arr[i] + arr[j] + arr[k] + arr[l] == target) {
                        vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }

    // Store the set elements in the answer
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Approach 2: Better Approach (Using HashSet for Fourth Element) (O(n^2))
vector<vector<int>> fourSumHashSet(int n, vector<int>& arr, int target) {
    vector<vector<int>> result;
    set<vector<int>> s2; // To store unique quadruplets

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            set<int> s1; // Set to track elements we've seen so far
            for (int k = j + 1; k < n; k++) {
                int ele = target - (arr[i] + arr[j] + arr[k]); // Find the fourth element needed to make sum = target
                if (s1.find(ele) != s1.end()) { // If the fourth element is in s1
                    vector<int> ans = {arr[i], arr[j], arr[k], ele}; // Form the quadruplet
                    sort(ans.begin(), ans.end()); // Sort the quadruplet to avoid duplicates
                    s2.insert(ans); // Insert the sorted quadruplet into the set
                }
                s1.insert(arr[k]); // Add the current element to s1
            }
        }
    }

    // Convert the set of unique quadruplets to a vector
    result.assign(s2.begin(), s2.end());
    return result;
}

// Approach 3: Optimal Approach (Using Sorting and Two Pointers) (O(n^3))
vector<vector<int>> fourSumOptimal(int n, vector<int>& arr, int target) {
    vector<vector<int>> result;
    sort(arr.begin(), arr.end()); // Sort the array to enable two-pointer technique

    for (int i = 0; i < n - 3; i++) {
        // Skip duplicates for the `i` index
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }

        for (int j = i + 1; j < n - 2; j++) {
            // Skip duplicates for the `j` index
            if (j > i + 1 && arr[j] == arr[j - 1]) {
                continue;
            }

            int k = j + 1; // Start from the next element after `j`
            int l = n - 1; // Start from the end of the array

            while (k < l) {
                int sum = arr[i] + arr[j] + arr[k] + arr[l];

                if (sum < target) {
                    k++; // Increase the left pointer to increase the sum
                } else if (sum > target) {
                    l--; // Decrease the right pointer to decrease the sum
                } else {
                    // Found a valid quadruplet
                    result.push_back({arr[i], arr[j], arr[k], arr[l]});

                    // Skip duplicates for `k` and `l`
                    while (k < l && arr[k] == arr[k + 1]) k++;
                    while (k < l && arr[l] == arr[l - 1]) l--;

                    // Move both pointers after handling duplicates
                    k++;
                    l--;
                }
            }
        }
    }

    return result;
}

int main() {
    vector<int> arr = {1, 0, -1, 0, -2, 2};
    int n = arr.size();
    int target = 0;

    // Function to print results
    auto printResult = [](const vector<vector<int>>& ans, const string& approach) {
        cout << approach << ":\n";
        if (ans.empty()) {
            cout << "No quadruplets found.\n";
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
    vector<vector<int>> ansBrute = fourSumBruteForce(n, arr, target);
    printResult(ansBrute, "Brute Force Approach");

    // Call and print results for HashSet approach
    vector<vector<int>> ansHashSet = fourSumHashSet(n, arr, target);
    printResult(ansHashSet, "HashSet Approach");

    // Call and print results for Optimal approach
    vector<vector<int>> ansOptimal = fourSumOptimal(n, arr, target);
    printResult(ansOptimal, "Optimal (Two-Pointer) Approach");

    return 0;
}
