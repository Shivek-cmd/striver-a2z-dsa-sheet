#include <bits/stdc++.h>
using namespace std;

/*==============================================================================
 Section 1: Problem Statement
 ==============================================================================

 Problem:
     You are given a positive integer n. Your task is to find and return its 
     square root. If ‘n’ is not a perfect square, then return the floor value 
     of 'sqrt(n)'.

     Find the maximum number x such that x*x <= n.

 Examples:
     Input:  n = 36
     Output: 6

     Input:  n = 28
     Output: 5

 Constraints:
     - 1 <= n <= 10^9
     - n is a positive integer.

 Edge Cases:
     - n = 1 (smallest input)
     - n is a perfect square (e.g., 25, 100)
     - n is not a perfect square (e.g., 28, 50)


 ==============================================================================
 Section 2: Solution Approaches
 ==============================================================================



---------------------------------------
 Approach 1: Brute Force (Linear Search)
 ---------------------------------------
 - Start from 1, incrementally square each number until it exceeds n.
 - Keep track of the last number whose square was <= n.

 Time Complexity: O(N)
 Space Complexity: O(1)
 Limitations: Very slow for large n (~10^9)




---------------------------------------
 Approach 2: Better (Using Built-in sqrt())
 -------------------------------------------
 - Use the standard library function sqrt().
 - Take the floor of the result.

 Time Complexity: O(1)
 Space Complexity: O(1)
 Limitations: Depends on library precision.




---------------------------------------
 Approach 3: Optimal (Binary Search)
 ------------------------------------
 Core Idea:
     We are using Binary Search on the range [1, n] instead of an array.
     Even though an array is not given, our *search space* [1, n] is sorted.
     Hence, Binary Search can be applied.

 Goal:
     Find the maximum integer 'x' such that (x * x) <= n.

 ------------------------------------------------------------------------------
 Key Observations:
     - The search space is [1, n], which is sorted in increasing order.
     - As 'mid' increases, 'mid * mid' also increases.
     - If (mid * mid) <= n, we move right to find a potentially bigger valid answer.
     - If (mid * mid) > n, we move left to find a smaller number.

 ------------------------------------------------------------------------------
 Algorithm Steps:

 Step 1: Initialize pointers
     - low = 1
     - high = n

 Step 2: Loop until low <= high
     - Find mid = (low + high) / 2

 Step 3: Check mid * mid
     - If (mid * mid) <= n:
         - mid is a valid candidate.
         - Store mid in 'ans' (optional).
         - Move to the right half: low = mid + 1
     - Else:
         - mid is too big.
         - Move to the left half: high = mid - 1

 Step 4: Loop ends when low > high
     - The 'high' pointer will point to the floor of sqrt(n).
     - We can return 'high' or 'ans'.


 Time Complexity: O(logN)
 Space Complexity: O(1)
 Strength: Fast and efficient for large values of n.



 ==============================================================================
 Section 3: Code Implementation
 ==============================================================================

 Approach 1: Brute Force

 */
int floorSqrtBrute(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (1LL * i * i <= n) {   //Use 1LL to avoid integer overflow
            ans = i;
        } else {
            break;
        }
    }
    return ans;
}

//  Approach 2: Better (Built-in sqrt())
int floorSqrtBetter(int n) {
    return (int)(sqrt(n));
}

//  Approach 3: Optimal (Binary Search)
int floorSqrtOptimal(int n) {
    int low = 1, high = n;
    int ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (1LL * mid * mid <= n) {
            ans = mid;        // mid is a valid candidate
            low = mid + 1;    // search in the right half
        } else {
            high = mid - 1;    //search in the left half
        }
    }
    return ans;
}

int main() {
    int n1 = 36;
    int n2 = 28;
    int n3 = 1;
    int n4 = 100;
    
    cout << "Using Brute Force Approach:" << endl;
    cout << "Square root of " << n1 << " is: " << floorSqrtBrute(n1) << endl;
    cout << "Square root of " << n2 << " is: " << floorSqrtBrute(n2) << endl;
    cout << "Square root of " << n3 << " is: " << floorSqrtBrute(n3) << endl;
    cout << "Square root of " << n4 << " is: " << floorSqrtBrute(n4) << endl;
    
    cout << "\nUsing Better Approach (sqrt function):" << endl;
    cout << "Square root of " << n1 << " is: " << floorSqrtBetter(n1) << endl;
    cout << "Square root of " << n2 << " is: " << floorSqrtBetter(n2) << endl;
    cout << "Square root of " << n3 << " is: " << floorSqrtBetter(n3) << endl;
    cout << "Square root of " << n4 << " is: " << floorSqrtBetter(n4) << endl;
    
    cout << "\nUsing Optimal Approach (Binary Search):" << endl;
    cout << "Square root of " << n1 << " is: " << floorSqrtOptimal(n1) << endl;
    cout << "Square root of " << n2 << " is: " << floorSqrtOptimal(n2) << endl;
    cout << "Square root of " << n3 << " is: " << floorSqrtOptimal(n3) << endl;
    cout << "Square root of " << n4 << " is: " << floorSqrtOptimal(n4) << endl;
    
    return 0;
}
