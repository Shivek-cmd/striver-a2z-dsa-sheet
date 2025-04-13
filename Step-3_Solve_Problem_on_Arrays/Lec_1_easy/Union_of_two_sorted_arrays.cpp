#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Problem:
    Given two sorted arrays nums1 and nums2, return an array that contains the union of these two arrays.
    The elements in the union must be in ascending order and should be distinct.

    The union of two arrays is an array where all values are distinct and are present in either the first array,
    the second array, or both.

    Examples:

    Input: nums1 = [1,1, 2, 3, 4, 5], nums2 = [2, 3, 4,4,5,6]
    Output: [1, 2, 3, 4, 5, ]

    Input: nums1 = [3, 4, 6, 7, 9, 9], nums2 = [1, 5, 7, 8, 8]
    Output: [1, 3, 4, 5, 6, 7, 8, 9]
*/

/*
    ✅ Approach 1: Brute Force using set
        - Insert all elements of both arrays into a set.
        - This removes duplicates and keeps order sorted.
        - Convert the set to a vector and return it.

        Time Complexity:  O((m + n) log(m + n))
        Space Complexity: O(m + n)

    ✅ Approach 2: Better - Using unordered_set + sort
        - Insert all elements into an unordered_set to remove duplicates.
        - Convert to vector and sort it.

        Time Complexity:  O(m + n + k log k) where k = unique elements
        Space Complexity: O(m + n)

    ✅ Approach 3: Optimal - Two Pointer Approach (for sorted arrays)

    -------------------------------------------------------------
    🔍 Detailed Steps:
    -------------------------------------------------------------
    - Since both arrays are sorted, we can use two pointers (i and j)
      to traverse both arrays simultaneously.

    - Initialize:
        i = 0 (for nums1)
        j = 0 (for nums2)
        result = empty vector to store the intersection

    - Loop while i < nums1.size() and j < nums2.size():

        1. Skip duplicates in nums1:
            if i > 0 and nums1[i] == nums1[i - 1], skip current i to avoid duplicates.

        2. Skip duplicates in nums2:
            if j > 0 and nums2[j] == nums2[j - 1], skip current j to avoid duplicates.

        3. If nums1[i] == nums2[j]:
            - It is a common element
            - Push it into result vector
            - Move both pointers forward: i++, j++

        4. Else if nums1[i] < nums2[j]:
            - Current element in nums1 is smaller, so move i++

        5. Else (nums1[i] > nums2[j]):
            - Current element in nums2 is smaller, so move j++

    - End of loop: result contains all unique common elements in sorted order

    -------------------------------------------------------------
    Time Complexity:  O(m + n)
    Space Complexity: O(1) (ignoring output vector)
*/
vector<int> union_BruteForce(vector<int>& nums1, vector<int>& nums2) {
    set<int> s;
    s.insert(nums1.begin(), nums1.end());
    s.insert(nums2.begin(), nums2.end());

    vector<int> result(s.begin(), s.end());
    return result;
}

vector<int> union_Better(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> us;
    for (int x : nums1) us.insert(x);
    for (int x : nums2) us.insert(x);

    vector<int> result(us.begin(), us.end());
    sort(result.begin(), result.end());
    return result;
}

vector<int> union_Optimal(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0;
    int m = nums1.size(), n = nums2.size();
    vector<int> result;

    while (i < m && j < n) {
        // Skip duplicates in nums1
        if (i > 0 && nums1[i] == nums1[i - 1]) {
            i++;
            continue;
        }
        // Skip duplicates in nums2
        if (j > 0 && nums2[j] == nums2[j - 1]) {
            j++;
            continue;
        }

        if (nums1[i] < nums2[j]) {
            result.push_back(nums1[i++]);
        } else if (nums1[i] > nums2[j]) {
            result.push_back(nums2[j++]);
        } else {
            result.push_back(nums1[i]);
            i++;
            j++;
        }
    }

    while (i < m) {
        if (i == 0 || nums1[i] != nums1[i - 1])
            result.push_back(nums1[i]);
        i++;
    }

    while (j < n) {
        if (j == 0 || nums2[j] != nums2[j - 1])
            result.push_back(nums2[j]);
        j++;
    }

    return result;
}

// -----------------------------
// 🧪 Main function to test all
// -----------------------------
int main() {
    vector<int> nums1 = {1, 2, 3, 4, 5};
    vector<int> nums2 = {1, 2, 7};

    // Brute Force
    vector<int> res1 = union_BruteForce(nums1, nums2);
    cout << "[Brute Force] Union: ";
    for (int val : res1) cout << val << " ";
    cout << endl;

    // Better
    vector<int> res2 = union_Better(nums1, nums2);
    cout << "[Better] Union: ";
    for (int val : res2) cout << val << " ";
    cout << endl;

    // Optimal
    vector<int> res3 = union_Optimal(nums1, nums2);
    cout << "[Optimal] Union: ";
    for (int val : res3) cout << val << " ";
    cout << endl;

    return 0;
}
