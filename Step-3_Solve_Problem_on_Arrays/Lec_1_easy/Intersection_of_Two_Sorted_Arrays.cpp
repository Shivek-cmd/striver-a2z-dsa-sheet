#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Problem:
    Given two sorted arrays nums1 and nums2, return an array containing 
    only the elements that are present in **both** arrays. 
    The result should also be in sorted order and contain only distinct elements.

    Example 1:
    Input: nums1 = [1, 2, 2, 3, 4], nums2 = [2, 2, 3, 5]
    Output: [2, 3]

    Example 2:
    Input: nums1 = [1, 1, 1, 2], nums2 = [1, 1, 2, 2]
    Output: [1, 2]
*/

/*
    ✅ All Approaches:

    🔹 Approach 1: Brute Force using unordered_set + set
        - Insert all elements of nums1 into an unordered_set
        - Traverse nums2, and if element is found in the set, insert into a result set
        - Convert the result set into a vector

        Time Complexity:  O(m + n)
        Space Complexity: O(m + n)

    🔹 Approach 2: Better - Binary Search + Set
        - For each unique element in the smaller array, binary search it in the larger array
        - Insert matching elements into a result set

        Time Complexity:  O(min(m, n) * log max(m, n))
        Space Complexity: O(m + n)

    🔹 Approach 3: Optimal - Two Pointer Technique
        - Use two pointers to traverse both sorted arrays
        - If equal, insert into result and skip duplicates
        - If nums1[i] < nums2[j], increment i; else increment j

        Time Complexity:  O(m + n)
        Space Complexity: O(1) [excluding output]
*/

/*---------------------------------------------------
    ✅ All Solutions
---------------------------------------------------*/

// 🔽 Solution 1: Brute Force using set
vector<int> intersection_BruteForce(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s1(nums1.begin(), nums1.end());
    set<int> result;

    for (int x : nums2) {
        if (s1.count(x)) {
            result.insert(x);
        }
    }

    return vector<int>(result.begin(), result.end());
}

// 🔽 Solution 2: Better - Binary Search + Set
vector<int> intersection_Better(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) swap(nums1, nums2);
    
    set<int> result;
    for (int i = 0; i < nums1.size(); ++i) {
        if (i == 0 || nums1[i] != nums1[i - 1]) {
            if (binary_search(nums2.begin(), nums2.end(), nums1[i])) {
                result.insert(nums1[i]);
            }
        }
    }

    return vector<int>(result.begin(), result.end());
}

// 🔽 Solution 3: Optimal - Two Pointer Approach
vector<int> intersection_Optimal(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    int i = 0, j = 0;
    int m = nums1.size(), n = nums2.size();

    while (i < m && j < n) {
        if (i > 0 && nums1[i] == nums1[i - 1]) {
            i++;
            continue;
        }
        if (j > 0 && nums2[j] == nums2[j - 1]) {
            j++;
            continue;
        }

        if (nums1[i] == nums2[j]) {
            result.push_back(nums1[i]);
            i++;
            j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            j++;
        }
    }

    return result;
}

/*---------------------------------------------------
    ✅ Main Function to Test All Approaches
---------------------------------------------------*/
int main() {
    vector<int> nums1 = {1, 2, 2, 3, 4};
    vector<int> nums2 = {2, 2, 3, 5};

    // Test Brute Force
    vector<int> res1 = intersection_BruteForce(nums1, nums2);
    cout << "[Brute Force] Intersection: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    // Test Better
    vector<int> res2 = intersection_Better(nums1, nums2);
    cout << "[Better] Intersection: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    // Test Optimal
    vector<int> res3 = intersection_Optimal(nums1, nums2);
    cout << "[Optimal] Intersection: ";
    for (int x : res3) cout << x << " ";
    cout << endl;

    return 0;
}
