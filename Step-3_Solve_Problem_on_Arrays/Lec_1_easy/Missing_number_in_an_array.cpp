#include <bits/stdc++.h>
using namespace std;

/*
    🔸 Problem Statement:
    Given an integer N and an array of size N-1 containing N-1 numbers between 1 to N, 
    find the number (between 1 to N) that is not present in the given array.

    Examples:

    Example 1:
    Input: N = 5, array[] = {1, 2, 4, 5}
    Output: 3

    Example 2:
    Input: N = 3, array[] = {1, 3}
    Output: 2
*/

/*
    ✅ All Approaches:

    🔹 Approach 1: Brute Force
        - For each number from 1 to N, check if it exists in the array.
        - If not found, that’s the missing number.

        Time Complexity:  O(N^2)
        Space Complexity: O(1)

    🔹 Approach 2: Better - Using Hashing
        - Use a hash array of size N+1 initialized to 0.
        - Mark the indices of the numbers present.
        - The index with 0 is the missing number.

        Time Complexity:  O(N)
        Space Complexity: O(N)

    🔹 Approach 3: Optimal - Using Sum Formula
        - Use the formula for sum of first N numbers: (N * (N + 1)) / 2
        - Subtract the actual sum of the array from the expected total sum.

        Time Complexity:  O(N)
        Space Complexity: O(1)

    🔹 Approach 4: Optimal - Using XOR
        - XOR all numbers from 1 to N.
        - XOR all elements in the array.
        - XOR of these two results gives the missing number.

        Time Complexity:  O(N)
        Space Complexity: O(1)

    📝 Note:
        - Among the optimal approaches, the XOR approach is slightly better than the summation one
          because the term (N * (N + 1)) / 2 used in the summation method may cause overflow 
          if N is large (e.g., N = 10^5).
        - XOR does not face such overflow issues and is therefore preferred for large inputs.
*/

/*---------------------------------------------------
    ✅ All Solutions
---------------------------------------------------*/

// 🔽 Approach 1: Brute Force
int missingNumber_BruteForce(int N, vector<int>& arr) {
    for (int i = 1; i <= N; i++) {
        bool found = false;
        for (int j = 0; j < N - 1; j++) {
            if (arr[j] == i) {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }
    return -1;
}

// 🔽 Approach 2: Better - Using Hashing
int missingNumber_Hashing(int N, vector<int>& arr) {
    vector<int> hash(N + 1, 0);
    for (int num : arr) {
        hash[num] = 1;
    }
    for (int i = 1; i <= N; i++) {
        if (hash[i] == 0) return i;
    }
    return -1;
}

// 🔽 Approach 3: Optimal - Using Sum Formula
int missingNumber_Sum(int N, vector<int>& arr) {
    int actualSum = (N * (N + 1)) / 2;
    int givenSum = 0;
    for (int num : arr) {
        givenSum += num;
    }
    return actualSum - givenSum;
}

// 🔽 Approach 4: Optimal - Using XOR
int missingNumber_XOR(int N, vector<int>& arr) {
    int xor1 = 0, xor2 = 0;

    for (int i = 1; i <= N; i++) {
        xor1 ^= i;
    }

    for (int num : arr) {
        xor2 ^= num;
    }

    return xor1 ^ xor2;
}

/*---------------------------------------------------
    ✅ Main Function to Test All Approaches
---------------------------------------------------*/
int main() {
    int N = 5;
    vector<int> arr = {1, 2, 4, 5};

    cout << "[Brute Force] Missing Number: " << missingNumber_BruteForce(N, arr) << endl;
    cout << "[Hashing] Missing Number: " << missingNumber_Hashing(N, arr) << endl;
    cout << "[Sum Formula] Missing Number: " << missingNumber_Sum(N, arr) << endl;
    cout << "[XOR] Missing Number: " << missingNumber_XOR(N, arr) << endl;

    return 0;
}
