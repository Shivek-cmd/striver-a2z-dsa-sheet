#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
PROBLEM STATEMENT:
-----------------------------------------------------

Variety-1 
There’s an array ‘A’ of size ‘N’ with an equal number of positive and negative elements. 
Without altering the relative order of positive and negative elements, you must return an array 
of alternately positive and negative values.

Note: Start the array with positive elements.

Examples:

Example 1:
Input:
arr[] = {1,2,-4,-5}, N = 4
Output:
1 -4 2 -5

Explanation:
Positive elements = 1,2
Negative elements = -4,-5
To maintain relative ordering, 1 must occur before 2, and -4 must occur before -5.

Example 2:
Input:
arr[] = {1,2,-3,-1,-2,-3}, N = 6
Output:
1 -3 2 -1 3 -2

Explanation:
Positive elements = 1,2,3
Negative elements = -3,-1,-2
To maintain relative ordering, 1 must occur before 2, and 2 must occur before 3.
Also, -3 should come before -1, and -1 should come before -2.

-----------------------------------------------------
Approach 1 - Brute Force Approach:
-----------------------------------------------------

- First, separate positive and negative elements into two different arrays, `pos` and `neg`.
- After segregating each of the positive and negative elements, we start placing them alternately back into the array `A`. 
- We begin with a positive number at index 0, so all positive numbers will be placed at even indices, and negatives will be placed at odd indices. The relative order within positive and negative elements should be maintained.
  
Time Complexity: O(N+N/2)
Space Complexity: O(N) (Due to the use of two extra vectors `pos` and `neg`)

-----------------------------------------------------
Approach 2 - Optimized Approach:
-----------------------------------------------------

In this optimal approach, we aim to solve the problem in a single pass.

- We will maintain two pointers: `pos` for the positive elements, which starts at index 0, and `neg` for the negative elements, which starts at index 1.
- We will take an aux array of same size.
- We traverse the array. When we encounter a positive number, we place it at `pos` in aux array and increment `pos` by 2 (for alternating positions).
- When we encounter a negative number, we place it at `neg` in the aux array and increment `neg` by 2.
- We continue until both pointers exceed the array's bounds, indicating that the array has been rearranged alternately.
- we will copy all the aux array elements to original array

ONE INTUITION:- If positive and negative numbers are equal it mean pos,neg pointer can never be greater that size of array.
Time Complexity: O(N) (single pass through the array)
Space Complexity: O(N) 

-----------------------------------------------------
*/

void rearrangeBySignBruteForce(int arr[], int n) {
    vector<int> pos, neg;

    // Separate positive and negative numbers into separate vectors
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            pos.push_back(arr[i]);
        else
            neg.push_back(arr[i]);
    }

    int i = 0;
    int posIndex = 0, negIndex = 0;

    // Place elements alternately, starting with positive
    while (posIndex < pos.size() && negIndex < neg.size()) {
        arr[i++] = pos[posIndex++];
        arr[i++] = neg[negIndex++];
    }

}

void rearrangeBySignOptimized(int arr[], int n) {
    int pos = 0, neg = 1;  // Start with positions for positive and negative numbers
    vector<int> ans(n,0);
    // Rearrange the array by alternating positive and negative elements
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            ans[pos] = arr[i];
            pos += 2;  // Move to the next even index
        } else {
            ans[neg] = arr[i];
            neg += 2;  // Move to the next odd index
        }
    }
    for(int i=0;i<n;i++)
    {
        arr[i]=ans[i];
    }
}

int main() {
    // Test case 1 - Brute Force approach
    int arr1[] = {1, 4, -3, 6, -8, 10};
    int N1 = 6;
    rearrangeBySignBruteForce(arr1, N1);
    cout << "Rearranged array using Brute Force: ";
    for (int i = 0; i < N1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // Test case 2 - Optimized approach
    int arr2[] = {1, 2, -3, -1, -2, -3};
    int N2 = 6;
    rearrangeBySignOptimized(arr2, N2);
    cout << "Rearranged array using Optimized Approach: ";
    for (int i = 0; i < N2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
-----------------------------------------------------
PROBLEM STATEMENT:
-----------------------------------------------------

Variety-2 
There’s an array ‘A’ of size ‘N’ with positive and negative elements (not necessarily equal). Without altering the relative order of positive and negative elements, you must return an array of alternately positive and negative values. The leftover elements should be placed at the very end in the same order as in array A.

Note: Start the array with positive elements.


/**
 * 
 /**
 * Approach:
 * 
 * 1. Initialize two separate vectors, `pos[]` and `neg[]`, to store the positive and negative numbers
 *    from the given input array `arr[]`.
 * 
 * 2. Traverse the input array `arr[]`:
 *    - If the current element is positive, push it into the `pos[]` vector.
 *    - If the current element is negative, push it into the `neg[]` vector.
 * 
 * 3. After separating the positive and negative numbers, we need to rearrange them in the input array.
 * 
 * 4. The process of rearranging will start by alternating between positive and negative elements:
 *    - Place elements alternately from the `pos[]` and `neg[]` vectors, starting with a positive number.
 *    - This is done using a while loop where both `pos[]` and `neg[]` are traversed and placed alternately in the `arr[]` array.
 * 
 * 5. After placing all elements alternately, if there are any leftover elements (either positive or negative),
 *    place them at the end of the array in the order they appear in the `pos[]` or `neg[]` vectors.
 * 
 * 6. Finally, return the rearranged array.
 * 
 * T.C.: O(N)

   S.C.: O(N)
 */

vector<int> RearrangebySign(vector<int>& arr, int n) {
    vector<int> pos, neg;

    // Separate positive and negative numbers into separate vectors
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            pos.push_back(arr[i]);
        else
            neg.push_back(arr[i]);
    }

    int i = 0;
    int posIndex = 0, negIndex = 0;

    // Place elements alternately, starting with positive
    while (posIndex < pos.size() && negIndex < neg.size()) {
        arr[i++] = pos[posIndex++];
        arr[i++] = neg[negIndex++];
    }

    // Place remaining elements from pos[] if any
    while (posIndex < pos.size()) {
        arr[i++] = pos[posIndex++];
    }

    // Place remaining elements from neg[] if any
    while (negIndex < neg.size()) {
        arr[i++] = neg[negIndex++];
    }

    return arr;  // Return the rearranged array
}

 int main() {
    
    // Array Initialisation.
    int n = 6;
    vector<int> A {1,2,-4,-5,3,4};
  
    vector<int> ans = RearrangebySign(A,n);
    
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[i] << " ";
    }
  
    return 0;
  }