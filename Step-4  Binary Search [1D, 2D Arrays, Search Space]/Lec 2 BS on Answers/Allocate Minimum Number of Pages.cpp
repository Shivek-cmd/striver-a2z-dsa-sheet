#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Problem: Book Allocation
Given an array 'arr' of integers where arr[i] represents the number of pages in the i-th book,
allocate all books to 'm' students such that:
1. Each student gets at least one book.
2. Each book is allocated to exactly one student.
3. Books are allocated contiguously.
The goal is to minimize the maximum number of pages assigned to any student.
Return -1 if allocation is impossible.

Examples:
1. Input: n = 4, m = 2, arr = {12, 34, 67, 90}
   Output: 113
   Explanation: Allocation: [12, 34, 67 | 90]. Max pages = 12 + 34 + 67 = 113.
2. Input: n = 5, m = 4, arr = {25, 46, 28, 49, 24}
   Output: 71
   Explanation: Allocation: [25, 46 | 28 | 49 | 24]. Max pages = 25 + 46 = 71.

Constraints:
- 1 <= n <= 10^5 (number of books)
- 1 <= m <= n (number of students)
- 1 <= arr[i] <= 10^9 (pages in each book)

Edge Cases:
- m > n: Impossible to allocate (return -1).
- m == n: Each student gets one book (answer = max(arr)).
- n == 1, m == 1: Single book to single student (answer = arr[0]).
- Large arr[i] values: Handle potential overflow with long long.
- Single large book: Max element dominates the answer.
*/

/*
Observations:
1. The answer is the minimum possible maximum pages any student can receive.
2. Books must be allocated contiguously, so we are partitioning the array into m contiguous segments.
3. The minimum possible answer is max(arr), when each student gets one book (m == n).
4. The maximum possible answer is sum(arr), when one student gets all books (m == 1).
5. The answer lies in the range [max(arr), sum(arr)].
6. If m > n, allocation is impossible (not enough books for each student).
7. We can use a helper function to count how many students are needed for a given maximum page limit.
8. Binary search can optimize the search for the minimum maximum pages, as the answer space is monotonic:
   - If a page limit allows allocation to <= m students, a larger limit will also work.
   - If a page limit requires > m students, a smaller limit will also fail.
*/

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================

----------------------------------------
Approach 1: Brute Force
----------------------------------------
Logic:
- Check every possible maximum page limit from max(arr) to sum(arr).
- For each limit, count the number of students needed using a helper function.
- Return the first limit that requires exactly m students.

Algorithm:
1. If m > n, return -1 (impossible allocation).
2. Find max(arr) as the lower bound and sum(arr) as the upper bound.
3. For each possible page limit from max(arr) to sum(arr):
   a. Use countStudents() to calculate the number of students needed.
   b. If students == m, return the current page limit.
4. If no valid limit is found, return max(arr) (though this is unlikely given constraints).

Time Complexity: O(N * (sum(arr) - max(arr) + 1))
- N: Array size, for countStudents() loop.
- sum(arr) - max(arr) + 1: Number of possible page limits.
- Worst case: Large sum(arr) (up to 10^9 * 10^5), making this approach impractical.

Space Complexity: O(1)
- Only uses a constant amount of extra space.

Limitations:
- Inefficient for large inputs due to linear search over a potentially huge range.
- Not suitable for real-time applications or large sum(arr).

----------------------------------------
Approach 2: Optimal (Binary Search)
----------------------------------------
Logic:
- The answer lies in [max(arr), sum(arr)], and the number of students needed decreases
  as the page limit increases (monotonic property).
- Use binary search to find the smallest page limit that allows allocation to exactly m students.
- For each mid-point, check if the number of students needed is <= m.

Algorithm:
1. If m > n, return -1 (impossible allocation).
2. Initialize low = max(arr), high = sum(arr).
3. While low <= high:
   a. Compute mid = (low + high) / 2.
   b. Use countStudents() to get the number of students needed for mid pages.
   c. If students > m, mid is too small, set low = mid + 1.
   d. If students <= m, mid is a candidate, try a smaller value: high = mid - 1.
4. Return low, which points to the smallest valid page limit.

Time Complexity: O(N * log(sum(arr) - max(arr) + 1))
- Binary search: log(sum(arr) - max(arr) + 1) iterations.
- countStudents(): O(N) per iteration.
- Much faster than brute force due to logarithmic reduction in search space.

Space Complexity: O(1)
- Only uses a constant amount of extra space.

Why Optimal?
- Binary search reduces the search space from linear to logarithmic.
- Efficiently handles large inputs (n up to 10^5, arr[i] up to 10^9).
- Monotonic property ensures correctness.

Trade-offs:
- Slightly more complex to implement than brute force.
- Still requires O(N) per iteration, but this is unavoidable due to the need to check allocations.

*/

/*
==============================================================================
Section 3: Code Implementation
==============================================================================
*/

// Helper function to count the number of students needed for a given page limit
int countStudents(const vector<int>& arr, long long pages) {
    int students = 1; // Start with one student
    long long pagesStudent = 0; // Pages assigned to current student

    for (int pagesInBook : arr) {
        // Check if current book can be added to current student
        if (pagesStudent + pagesInBook <= pages) {
            pagesStudent += pagesInBook;
        } else {
            // Move to next student and assign current book
            students++;
            pagesStudent = pagesInBook;
        }
    }
    return students;
}

// Brute Force Approach
int findPagesBrute(const vector<int>& arr, int n, int m) {
    // Impossible if more students than books
    if (m > n) return -1;

    // Find minimum and maximum possible page limits
    // Initialize variables for maximum and sum
    long long maxi = INT_MIN; 
    long long sum = 0;       

    // Iterate through the array to find max and sum
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxi) {
            maxi = arr[i];
        }
        sum += arr[i]; 
    }

    // Assign to low and high
    long long low = maxi;  
    long long high = sum; 

    // Check each possible page limit
    for (long long pages = low; pages <= high; pages++) {
        if (countStudents(arr, pages) == m) {
            return pages;
        }
    }
    // Return max(arr) if no solution found (unlikely with valid inputs)
    return low;
}

// Optimal Approach (Binary Search)
int findPagesOptimal(const vector<int>& arr, int n, int m) {
    // Impossible if more students than books
    if (m > n) return -1;

   // Initialize variables for maximum and sum
   long long maxi = INT_MIN; 
   long long sum = 0;       

   // Iterate through the array to find max and sum
   for (int i = 0; i < n; i++) {
       if (arr[i] > maxi) {// Update maximum if current element is larger
       }
       sum += arr[i]; // Add current element to sum
   }

   // Assign to low and high
   long long low = maxi;  // Maximum element
   long long high = sum;  // Sum of all elements

    // Binary search for minimum page limit
    while (low <= high) {
        long long mid = low + (high - low) / 2; // Avoid overflow
        int students = countStudents(arr, mid);
        if (students > m) {
            // Too many students, need more pages
            low = mid + 1;
        } else {
            // Valid or too few students, try fewer pages
            high = mid - 1;
        }
    }
    return low;
}

int main() {
    // Test case from Example 2
    vector<int> arr = {25, 46, 28, 49, 24};
    int n = arr.size(); // Number of books
    int m = 4; // Number of students

    // Run brute force approach
    int ansBrute = findPagesBrute(arr, n, m);
    cout << "Brute Force Answer: " << ansBrute << "\n";

    // Run optimal approach
    int ansOptimal = findPagesOptimal(arr, n, m);
    cout << "Optimal Answer: " << ansOptimal << "\n";

    return 0;
}

/*
Expected Output for arr = {25, 46, 28, 49, 24}, n = 5, m = 4:
Brute Force Answer: 71
Optimal Answer: 71
*/