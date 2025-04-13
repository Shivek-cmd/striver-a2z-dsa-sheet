#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Problem Statement:
    Given a non-empty array of integers `arr`, where every element appears exactly twice except for one,
    find and return the element that appears only once.

    Examples:

    Example 1:
    Input:  arr[] = {2, 2, 1}
    Output: 1

    Example 2:
    Input:  arr[] = {4, 1, 2, 1, 2}
    Output: 4
*/

/*
    ✅ All Approaches:

    🔹 Approach 1: Brute Force (Nested Loop)
        - For each element, count how many times it appears using a loop.
        - Return the one that appears only once.

        Time Complexity: O(N²)
        Space Complexity: O(1)

    🔹 Approach 2: Better (Hashing using frequency array)
        - Find the maximum element in the array.
        - Create a frequency array of size (max + 1) and count occurrences.
        - Return the element with frequency 1.

        Time Complexity: O(N + maxVal)
        Space Complexity: O(maxVal)

    🔹 Approach 3: Better (Using Map)
        - Use map<int, int> to store frequency count.
        - Return the key whose value is 1.

        Time Complexity: O(N log N)
        Space Complexity: O(N)

    🔹 Approach 4: Optimal (Using XOR)
        - XOR of a number with itself is 0.
        - XOR of a number with 0 is the number itself.
        - So, XOR all elements. Duplicate elements cancel each other, leaving the unique one.

        Time Complexity: O(N)
        Space Complexity: O(1)
*/

/* ------------------------------------------------------------------
    ✅ All Solutions
-------------------------------------------------------------------*/

// 🔸 Approach 1: Brute Force
int findSingleNumber_BruteForce(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int count = 0;
        for (int j = 0; j < arr.size(); j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) return arr[i];
    }
    return -1;
}

// 🔸 Approach 2: Frequency Array (Hashing with vector)
int findSingleNumber_Hashing(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> freq(maxVal + 1, 0);

    for (int num : arr) {
        freq[num]++;
    }

    for (int i = 0; i < freq.size(); i++) {
        if (freq[i] == 1) return i;
    }

    return -1;
}

// 🔸 Approach 3: Using Map
int findSingleNumber_Map(vector<int>& arr) {
    map<int, int> mp;
    for (int num : arr) {
        mp[num]++;
    }

    for (auto it : mp) {
        if (it.second == 1) return it.first;
    }

    return -1;
}

// 🔸 Approach 4: XOR (Optimal)
int findSingleNumber_XOR(vector<int>& arr) {
    int result = 0;
    for (int num : arr) {
        result ^= num;
    }
    return result;
}

/* ------------------------------------------------------------------
    ✅ Main Function to Test All Approaches
-------------------------------------------------------------------*/
int main() {
    vector<int> arr = {4, 1, 2, 1, 2};

    cout << "[Brute Force] Result: " << findSingleNumber_BruteForce(arr) << endl;
    cout << "[Hashing Array] Result: " << findSingleNumber_Hashing(arr) << endl;
    cout << "[Map] Result: " << findSingleNumber_Map(arr) << endl;
    cout << "[XOR Optimal] Result: " << findSingleNumber_XOR(arr) << endl;

    return 0;
}
