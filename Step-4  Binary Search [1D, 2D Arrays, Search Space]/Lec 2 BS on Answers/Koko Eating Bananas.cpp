#include <bits/stdc++.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Section 1: Problem Statement
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Problem Statement:
A monkey is given ‘n’ piles of bananas, where the 'ith' pile has ‘a[i]’ bananas. 
An integer ‘h’ is given, denoting the time (in hours) to finish eating all bananas.

Each hour, the monkey chooses a pile and eats ‘k’ bananas.
If the pile has fewer than ‘k’ bananas, the monkey eats all remaining bananas and 
does not eat more in that hour.

Find the minimum number ‘k’ (bananas/hour) such that the monkey finishes all bananas within ‘h’ hours.

Examples:

Example 1:
Input: N = 4, a[] = {7, 15, 6, 3}, h = 8
Output: 5
Explanation: Eating 5 bananas/hr, Koko will take exactly 8 hours.

Example 2:
Input: N = 5, a[] = {25, 12, 8, 14, 19}, h = 5
Output: 25
Explanation: Eating 25 bananas/hr, Koko will finish one pile each hour.

Constraints:
- 1 <= N <= 1e5
- 1 <= a[i] <= 1e9
- 1 <= h <= 1e9

Edge Cases:
- Very large pile values.
- h smaller or larger compared to number of piles.


How Koko Eats the Bananas:

- Koko must finish the pile she picks before moving to another pile.
- In any hour, if bananas left in a pile are less than 'k', Koko eats all bananas and the hour completes.
- Therefore, for each pile, the time taken is ceil(pile size / k).

For example, if array = {3, 6, 7, 11} and h = 8:

- Eating speed = 2 bananas/hour:

1st pile: ceil(3/2) = 2 hrs  
2nd pile: ceil(6/2) = 3 hrs  
3rd pile: ceil(7/2) = 4 hrs  
4th pile: ceil(11/2) = 6 hrs  

Total time = 15 hours ➔ exceeds h.

Observation:
- The minimum possible value of k lies between 1 and the maximum element in the array (max(a[])).
- Because if Koko eats at the rate equal to the largest pile, she can finish each pile within 1 hour.

Thus, **answer search space is [1, max(a[])]**.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
// Section 2: Solution Approaches
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Approach 1: Naive (Brute-force)

Logic:
- Check every possible eating speed from 1 to max(a[]).
- For each speed, calculate total hours needed.
- Return the first speed for which total hours <= h.

Algorithm:
1. Find maximum element in the array, max(a[]).
2. Loop i = 1 to max(a[]):
    - For each i, calculate total hours using:
      hours += ceil(pile / i)
3. If hours <= h, return i.

Time Complexity: O(max(a[]) * N)
Reason: We are running nested loops. The outer loop runs for max(a[]) times in the worst case and the inner loop runs for N times.
Space Complexity: O(1)

Trade-offs:
- Works for small inputs.
- Extremely slow for large inputs (max(a[]) up to 1e9).

-------------------------------------------------------

Approach 2: Optimal (Binary Search)

Logic:
- Answer space [1, max(a[])] is sorted.
- Use binary search to find minimum k satisfying total hours <= h.

Algorithm:
1. Find maximum element in the array, max(a[]).
2. Initialize low = 1, high = max(a[]).
3. While low <= high:
    - mid = (low + high) / 2
    - Calculate total hours at mid speed.
    - If total hours <= h:
        - mid is a valid answer, search smaller (high = mid - 1)
    - Else:
        - Need faster eating speed (low = mid + 1)
4. Return the minimum valid k.

Time Complexity: O(N * log(max(a[])))
Reason: We are applying Binary search for the range [1, max(a[])], and for every value of ‘mid’,
 we are traversing the entire array inside the function named calculateTotalHours().
Space Complexity: O(1)

Advantages:
- Much faster, works for large inputs.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
// Section 3: Code Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to find maximum element in array
int maxElement(const vector<int> &arr) {
    int maxi = INT_MIN;
    for (int val : arr) {
        maxi = max(maxi, val);
    }
    return maxi;
}

// Function to calculate total hours needed at given eating speed
int totalHours(int bananasPerHour, const vector<int> &arr) {
    int totalH = 0;
    for (int val : arr) {
        totalH += ceil((double)val / bananasPerHour);
    }
    return totalH;
}

// Brute-force Approach
int minimumRateToEatBananas(vector<int> &arr, int h) {
    int maxi = maxElement(arr);

    for (int i = 1; i <= maxi; i++) {
        int reqTime = totalHours(i, arr);
        if (reqTime <= h) {
            return i;
        }
    }

    return maxi; // fallback, although answer should be found
}

// Optimal Approach using Binary Search
int minimumRateToEatBananasOptimize(vector<int> &arr, int h) {
    int low = 1, high = maxElement(arr);
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int reqTime = totalHours(mid, arr);

        if (reqTime <= h) {
            ans = mid;       // mid is a possible answer
            high = mid - 1;  // try smaller speed
        } else {
            low = mid + 1;   // need faster speed
        }
    }

    return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Function to Test
////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    vector<int> arr = {7, 15, 6, 3};
    int h = 8;

    cout << "Brute-force Result: Minimum bananas per hour = " << minimumRateToEatBananas(arr, h) << endl;
    cout << "Optimized Result: Minimum bananas per hour = " << minimumRateToEatBananasOptimize(arr, h) << endl;

    arr = {25, 12, 8, 14, 19};
    h = 5;

    cout << "Brute-force Result: Minimum bananas per hour = " << minimumRateToEatBananas(arr, h) << endl;
    cout << "Optimized Result: Minimum bananas per hour = " << minimumRateToEatBananasOptimize(arr, h) << endl;

    return 0;
}
