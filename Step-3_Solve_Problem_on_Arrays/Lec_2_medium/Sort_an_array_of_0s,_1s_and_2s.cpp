/*
Problem Statement:
-------------------
Given an array consisting only of 0s, 1s, and 2s, sort the array in-place 
(i.e., without using any in-built sorting functions) such that all 0s come first, 
then all 1s, followed by all 2s.

This is also known as the **Dutch National Flag Problem**.

Input: [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ------------------------ Approaches ------------------------

1. Brute Force (Using Extra Space):
   - Traverse the array 3 times: once to collect 0s, then 1s, then 2s into a temporary array.
   - Copy the temp array back to the original array.

   Time Complexity: O(N)
   Space Complexity: O(N)

2. Better (Counting Sort Idea):
   - Count the number of 0s, 1s, and 2s in one pass.
   - Overwrite the original array using the counts.

   Time Complexity: O(N)
   Space Complexity: O(1)

3. Optimal (Dutch National Flag Algorithm):

 - We can solve this problem in a single pass using the **Dutch National Flag Algorithm**.
    - The idea is to use **three pointers**: `low`, `mid`, and `high` to partition the array into three sections.
      - **[0, low-1]**: Section containing all 0s.
      - **[low, mid-1]**: Section containing all 1s.
      - **[high+1, n-1]**: Section containing all 2s.

      [mid,high]=> unsorted array

        Pointers:
    0        low -1       low         mid-1   mid         high   high+1        n-1
    *    0000000000         111111111111        01210210          2222222222


   - The key observation is that we will adjust the positions of `low`, `mid`, and `high` pointers based on the values of `arr[mid]`:
      - If `arr[mid] == 0`, we swap `arr[low]` and `arr[mid]`, then move both `low` and `mid` forward.
      - If `arr[mid] == 1`, we just move `mid` forward because it's already in the correct section.
      - If `arr[mid] == 2`, we swap `arr[mid]` and `arr[high]`, then move `high` backward.

 
  

   Time Complexity: O(N)
   Space Complexity: O(1)

-------------------------------------------------------------- */


/* ------------------------ Solutions ------------------------ */

// Approach 1: Brute Force (using extra array)
void sortColorsBrute(vector<int>& arr) {
    vector<int> temp;
    for (int num : arr) if (num == 0) temp.push_back(0);
    for (int num : arr) if (num == 1) temp.push_back(1);
    for (int num : arr) if (num == 2) temp.push_back(2);
    for (int i = 0; i < arr.size(); ++i) arr[i] = temp[i];
}

// Approach 2: Better - Count 0s, 1s, 2s
void sortColorsCount(vector<int>& arr) {
    int count0 = 0, count1 = 0, count2 = 0;
    for (int num : arr) {
        if (num == 0) count0++;
        else if (num == 1) count1++;
        else count2++;
    }
    int index = 0;
    while (count0--) arr[index++] = 0;
    while (count1--) arr[index++] = 1;
    while (count2--) arr[index++] = 2;
}

// Approach 3: Optimal - Dutch National Flag Algorithm
void sortColorsOptimal(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else {  // arr[mid] == 2
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

/* ------------------------ Utility Function ------------------------ */

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

/* ------------------------ Main Function ------------------------ */

int main() {
    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    vector<int> nums2 = nums1;
    vector<int> nums3 = nums1;

    cout << "Original: ";
    printArray(nums1);

    sortColorsBrute(nums1);
    cout << "Sorted (Brute Force): ";
    printArray(nums1);

    sortColorsCount(nums2);
    cout << "Sorted (Counting Sort): ";
    printArray(nums2);

    sortColorsOptimal(nums3);
    cout << "Sorted (Dutch National Flag - Optimal): ";
    printArray(nums3);

    return 0;
}
