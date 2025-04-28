#include <bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// Section 1: Problem Statement
/////////////////////////////////////////////////////////////////////////////////////////////

/*
Problem:
Given two numbers N and M, find the Nth root of M.
The Nth root of a number M is defined as a number X when raised to the power N equals M.
If the Nth root is not an integer, return -1.

Examples:

Example 1:
Input: N = 3, M = 27
Output: 3
Explanation: 3^3 = 27

Example 2:
Input: N = 4, M = 69
Output: -1
Explanation: 4th root of 69 is not an integer.

Constraints:
- 1 <= N, M <= 10^9
- Inputs are positive integers.

Edge Cases:
- Very large M
- No integer root exists
*/

/////////////////////////////////////////////////////////////////////////////////////////////
// Section 2: Solution Approaches
/////////////////////////////////////////////////////////////////////////////////////////////

/*
Approach 1: Brute Force (Linear Search)

- Logic:
    Try all numbers from 1 to M.
    For each number x, check if x^n == M.
    If x^n > M, break early (no need to continue).
    
- Steps:
    1. Loop i from 1 to M.
    2. For each i, calculate i^N.
    3. If i^N == M, return i.
    4. If i^N > M, return -1.

- Time Complexity: O(M * logN)
    - logN due to optimized exponentiation.
- Space Complexity: O(1)
- Limitations: Very slow if M is large.

--------------------------------------------------------

Approach 2: Optimal Approach (Binary Search)

- Logic:
    Apply binary search on the answer space [1, M].
    For each mid value, calculate mid^N:
        - If mid^N == M, mid is the answer.
        - If mid^N < M, move to the right half.
        - If mid^N > M, move to the left half.

- Important:
    Use fast exponentiation (Exponentiation by Squaring) to compute mid^N in O(logN) time.
    Stop early if mid^N exceeds M (to avoid overflow).

- Steps:
    1. Set low = 1, high = M.
    2. While low <= high:
        - mid = (low + high) / 2
        - Compute mid^N
            - If mid^N == M, return mid.
            - If mid^N < M, search right half (low = mid + 1).
            - If mid^N > M, search left half (high = mid - 1).
    3. If not found, return -1.

- Time Complexity: O(logM * logN)
- Space Complexity: O(1)
- Advantages: Very efficient even for large M.
*/

/////////////////////////////////////////////////////////////////////////////////////////////
// Section 3: Code Implementation
/////////////////////////////////////////////////////////////////////////////////////////////

/*
 Helper function: Efficiently calculates base^exponent
 using Exponentiation by Squaring in O(log exponent) time.
*/
long long fastPower(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
            if (result > 1e9) return 1e9; // Early exit if result becomes too large
        }
        base *= base;
        if (base > 1e9) base = 1e9; // Prevent overflow
        exponent /= 2;
    }
    return result;
}

/*
 Brute Force Approach: Linear search from 1 to M
*/
int NthRoot_BruteForce(int n, int m) {
    for (int i = 1; i <= m; i++) {
        long long power = fastPower(i, n);
        if (power == m) return i;
        if (power > m) break;
    }
    return -1;
}

/*
 Optimal Approach: Binary Search from 1 to M
*/
int NthRoot_BinarySearch(int n, int m) {
    int low = 1, high = m;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long midPower = fastPower(mid, n);

        if (midPower == m) {
            return mid;
        } else if (midPower < m) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Main Function to Test the Approaches
/////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 3, m = 27;

    cout << "Brute Force Result: " << NthRoot_BruteForce(n, m) << endl;
    cout << "Binary Search Result: " << NthRoot_BinarySearch(n, m) << endl;

    n = 4, m = 69;
    cout << "Brute Force Result: " << NthRoot_BruteForce(n, m) << endl;
    cout << "Binary Search Result: " << NthRoot_BinarySearch(n, m) << endl;

    return 0;
}
