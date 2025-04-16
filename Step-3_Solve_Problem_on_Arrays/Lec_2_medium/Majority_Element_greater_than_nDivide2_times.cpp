#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
-----------------------------------------------------
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array of N integers, return the element that appears more than ⌊N/2⌋ times (i.e., the majority element).
It is guaranteed that such an element always exists in the array.

-----------------------------------------------------
EXAMPLES:
-----------------------------------------------------
Input:  N = 3, nums[] = {3,2,3}
Output: 3

Input:  N = 7, nums[] = {2,2,1,1,1,2,2}
Output: 2

Input:  N = 10, nums[] = {4,4,2,4,3,4,4,3,2,4}
Output: 4

-----------------------------------------------------
APPROACHES:
-----------------------------------------------------

1️⃣ BRUTE FORCE:
- Loop through each element and count its occurrences using another loop.
- If count > N/2, return the element.

Time Complexity: O(N^2)
Space Complexity: O(1)

2️⃣ BETTER (Using Hash Map):
- Use an unordered_map to count frequencies of each element.
- Return the element with count > N/2.

Time Complexity: O(N)
Space Complexity: O(N)

3️⃣ OPTIMAL (Moore’s Voting Algorithm):

Thought Process:
A majority element appears more than half of the time in the array, so there must be one element 
that is "dominating" the others.
By pairing up the elements, we can eliminate the non-majority elements and still end up with the 
majority element.
- Select a candidate and maintain a count.
- If count drops to zero, change candidate.
- Then verify candidate (if needed, but not necessary in this problem).

Time Complexity: O(N)
Space Complexity: O(1)
*/


// ------------------------------
// 🔁 BRUTE FORCE APPROACH
// ------------------------------
int majorityElementBruteForce(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i])
                count++;
        }
        if (count > n / 2)
            return arr[i];
    }
    return -1; // should never reach here as per problem constraints
}

// ------------------------------
// 🧠 BETTER APPROACH - Hash Map
// ------------------------------
int majorityElementHashMap(const vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, int> freq;

    for (int num : arr)
        freq[num]++;

    for (auto& it : freq) {
        if (it.second > n / 2)
            return it.first;
    }
    return -1;
}

// ------------------------------
// 🚀 OPTIMAL APPROACH - Moore's Voting
// ------------------------------
int majorityElementMoore(const vector<int>& arr) {
    int count = 0;
    int candidate = 0;

    for (int num : arr) {
        if (count == 0) {
            candidate = num;
            count = 1;
        } else if (num == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // No need to verify since the problem guarantees majority exists

    // iF you want to verify simply count the number of occurences of candidate in the whole
    // array and check if it s greater than n/2
    return candidate;
}


// ------------------------------
// 🧪 MAIN FUNCTION TO TEST
// ------------------------------
int main() {
    vector<vector<int>> testCases = {
        {3, 2, 3},
        {2, 2, 1, 1, 1, 2, 2},
        {4, 4, 2, 4, 3, 4, 4, 3, 2, 4}
    };

    for (int i = 0; i < testCases.size(); i++) {
        cout << "Example " << i + 1 << ":\n";
        cout << "Brute Force Result: " << majorityElementBruteForce(testCases[i]) << endl;
        cout << "Hash Map Result   : " << majorityElementHashMap(testCases[i]) << endl;
        cout << "Moore's Voting    : " << majorityElementMoore(testCases[i]) << endl;
        cout << "-----------------------------------\n";
    }

    return 0;
}
