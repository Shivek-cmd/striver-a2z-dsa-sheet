#include <vector>      // Explicitly include necessary headers
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std; // Kept for simplicity, but consider qualifying std:: in larger programs

/*
    🔸 Problem Statement:
    Given an array of integers `arr[]` and an integer `target`:

    1st Variant: Return "YES" if there exist two numbers such that their sum equals the target. Otherwise, return "NO".
    
    2nd Variant: Return the indices of the two numbers such that their sum equals the target. Otherwise, return [-1, -1].

    Note: You are not allowed to use the same element twice. Example: If the target is equal to 6 and num[1] = 3, then nums[1] + nums[1] = target is not a solution.

    🧪 Examples:

    Example 1:
    Input: N = 5, arr[] = {2, 6, 5, 8, 11}, target = 14
    Output: YES (for 1st variant)
            [1, 3] (for 2nd variant)
    Explanation: arr[1] + arr[3] = 14. So, the answer is “YES” for the first variant and [1, 3] for the second variant.

    Example 2:
    Input: N = 5, arr[] = {2, 6, 5, 8, 11}, target = 15
    Output: NO (for 1st variant)
            [-1, -1] (for 2nd variant)
    Explanation: There are no two numbers whose sum equals the target.
*/

/*
    ✅ All Approaches For Variant 1:

    🔹 **Approach 1**: Brute Force
        - Try all pairs using nested loops.
        - If the sum equals the target, return true for the first variant, and return the indices for the second variant.
        - **Time Complexity**: O(N^2)
        - **Space Complexity**: O(1)

    🔹 **Approach 2**: Better with Hashing
        - Use an unordered set to store the elements we’ve seen so far.
        - For each element, check if the complement (`target - arr[i]`) exists in the set. If it does, return true for the first variant, and return the indices for the second variant.
        - **Time Complexity**: O(N)
        - **Space Complexity**: O(N)

    🔹 **Approach 3**: Optimal (Two-pointer approach for sorted arrays)
        - Sort the array and use two pointers: one at the start and one at the end.
        - Move the pointers inward based on the sum.
        - **Time Complexity**: O(N log N) for sorting + O(N) for the two-pointer traversal.
        - **Space Complexity**: O(1)
*/

/* -------------------------------
    ✅ Approach 1: Brute Force
--------------------------------*/

bool checkPairSum_BruteForce(vector<int>& arr, int target) {
    int n = arr.size();
    if (n < 2) return false; // Check for valid array size
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                return true;
            }
        }
    }
    return false;
}

/* -------------------------------
    ✅ Approach 2: Hashing (Optimized)
--------------------------------*/

bool checkPairSum_Hashing(vector<int>& arr, int target) {
    if (arr.size() < 2) return false; // Check for valid array size
    unordered_set<int> s;
    for (int i = 0; i < arr.size(); i++) {
        if (s.find(target - arr[i]) != s.end()) {
            return true; // Pair exists
        }
        s.insert(arr[i]);
    }
    return false;
}

/* -------------------------------
    ✅ Approach 3: Two-pointer (for sorted arrays)
--------------------------------*/

bool checkPairSum_TwoPointer(vector<int>& arr, int target) {
    if (arr.size() < 2) return false; // Check for valid array size
    vector<int> sortedArr = arr; // Create a copy to avoid modifying original array
    sort(sortedArr.begin(), sortedArr.end()); // Sort the copy
    int left = 0, right = sortedArr.size() - 1;
    while (left < right) {
        int sum = sortedArr[left] + sortedArr[right];
        if (sum == target) {
            return true;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return false;
}

/*
    ✅ All Approaches For Variant 2:

    🔹 **Approach 1**: Brute Force
        - Try all pairs using nested loops.
        - If the sum equals the target, return the indices of the pair.
        - **Time Complexity**: O(N^2)
        - **Space Complexity**: O(1)

    🔹 **Approach 2**: Better with Hashing (most optimal one)
        - Use an unordered map to store the elements we’ve seen so far along with their indices.
        - For each element, check if the complement (`target - arr[i]`) exists in the map. If it does, return the indices of the complement and the current element.
        - **Time Complexity**: O(N)
        - **Space Complexity**: O(N)

    🔹 **Approach 3**: Two-pointer (for sorted arrays)
        - Create a vector of pairs to store each element along with its original index.
        - Sort the vector based on the elements.
        - Use two pointers (one at the start, one at the end) to find a pair summing to the target.
        - Return the original indices of the pair if found, else return [-1, -1].
        - **Time Complexity**: O(N log N) for sorting + O(N) for two-pointer traversal = O(N log N)
        - **Space Complexity**: O(N) for storing the vector of pairs

*/

/* -------------------------------
    ✅ Approach 1: Brute Force
--------------------------------*/

vector<int> findPairIndices_BruteForce(vector<int>& arr, int target) {
    int n = arr.size();
    if (n < 2) return {-1, -1}; // Check for valid array size
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

/* -------------------------------
    ✅ Approach 2: Hashing (Optimized)
--------------------------------*/

vector<int> findPairIndices_Hashing(vector<int>& arr, int target) {
    if (arr.size() < 2) return {-1, -1}; // Check for valid array size
    unordered_map<int, int> seen;
    for (int i = 0; i < arr.size(); i++) {
        int complement = target - arr[i];
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        seen[arr[i]] = i;
    }
    return {-1, -1};
}

/* -------------------------------
    ✅ Approach 3: Two-pointer (for sorted arrays)
--------------------------------*/

vector<int> findPairIndices_TwoPointer(vector<int>& arr, int target) {
    if (arr.size() < 2) return {-1, -1}; // Check for valid array size
    
    vector<pair<int, int>> pairs; // Create a vector of pairs (value, original index)
    for (int i = 0; i < arr.size(); i++) {
        pairs.push_back({arr[i], i});
    }

    // Sort the pairs based on the values (arr[i]) but keep track of original indices
    sort(pairs.begin(), pairs.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    });

    // Use two-pointer technique to find the pair that sums up to the target
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        int sum = pairs[left].first + pairs[right].first;
        if (sum == target) {
            return {pairs[left].second, pairs[right].second};  // Return the original indices
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    return {-1, -1}; // No valid pair found
}

int main() {
    // Sample Input
    vector<int> arr = {2, 6, 5, 8, 11};
    int target = 14;

    // Test Brute Force Approach (First Variant)
    bool result = checkPairSum_BruteForce(arr, target);
    cout << "Brute Force - Variant 1: " << (result ? "YES" : "NO") << endl;

    // Test Hashing Approach (First Variant)
    result = checkPairSum_Hashing(arr, target);
    cout << "Hashing - Variant 1: " << (result ? "YES" : "NO") << endl;

    // Test Two-pointer Approach (First Variant)
    result = checkPairSum_TwoPointer(arr, target);
    cout << "Two-pointer - Variant 1: " << (result ? "YES" : "NO") << endl;

    // Test Brute Force Approach (Second Variant)
    vector<int> indices = findPairIndices_BruteForce(arr, target);
    cout << "Brute Force: [" << indices[0] << ", " << indices[1] << "]" << endl;

    // Test Hashing Approach (Second Variant)
    indices = findPairIndices_Hashing(arr, target);
    cout << "Hashing: [" << indices[0] << ", " << indices[1] << "]" << endl;

    // Test Two-pointer Approach (Second Variant)
    indices = findPairIndices_TwoPointer(arr, target);
    cout << "Two-pointer: [" << indices[0] << ", " << indices[1] << "]" << endl;

    return 0;
}