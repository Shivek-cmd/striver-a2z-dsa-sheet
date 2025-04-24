

#include <bits/stdc++.h>
using namespace std;


/*==============================================================================
Section 1: Problem Statement
==============================================================================*/
// Problem: Given a read-only array of N integers in the range [1, N], where each integer
// appears exactly once except for one number A that appears twice and one number B that is
// missing, find the repeating number A and the missing number B.
// Input: A vector of N integers, where each integer is in [1, N].
// Output: A vector of two integers: [A, B], where A is the repeating number and B is the missing number.
// Constraints:
// - 2 <= N <= 10^5
// - 1 <= arr[i] <= N
// - Exactly one number appears twice, and exactly one number is missing.
// Edge Cases:
// - Smallest valid input (N=2, e.g., {1, 1} -> repeating: 1, missing: 2)
// - Large arrays with numbers spread across [1, N]
// Examples:
// Example 1: arr = {3, 1, 2, 5, 3} -> Result: {3, 4} (3 repeats, 4 is missing)
// Example 2: arr = {3, 1, 2, 5, 4, 6, 7, 5} -> Result: {5, 8} (5 repeats, 8 is missing)

// Section 2: Solution Approaches
/*


----------------------------------------
Approach 1: Brute Force
----------------------------------------

Logic:
- For each number i from 1 to N, count its occurrences in the array using linear search.
- If count == 2, i is the repeating number.
- If count == 0, i is the missing number.
Steps:
1. Iterate i from 1 to N.
2. For each i, scan the array to count occurrences.
3. Store the number with count == 2 as repeating and count == 0 as missing.
4. Return [repeating, missing].
Time Complexity: O(N^2)
- Outer loop: O(N), inner loop for counting: O(N).
Space Complexity: O(1)
- Only uses a constant amount of extra space.
Limitations:
- Highly inefficient for large N due to nested loops.
- Not scalable for N up to 10^5.



----------------------------------------
Approach 2: Using Hash Map
----------------------------------------

Logic:
- Use a hash map to store the frequency of each number in the array.
- The number with frequency 2 is the repeating number.
- The number in [1, N] with frequency 0 is the missing number.
Steps:
1. Create a hash map to store frequency of array elements.
2. Iterate through the array to populate the map.
3. Find the number with frequency 2 (repeating).
4. Iterate from 1 to N to find the number with frequency 0 (missing).
5. Return [repeating, missing].
Time Complexity: O(N log N)
- Map operations (insert, find) take O(log N) in C++ (std::map).
- Single pass through array: O(N).
Space Complexity: O(N)
- Map stores at most N key-value pairs.
Limitations:
- Extra space required for the map.
- Slightly slower than optimal due to log N factor in map operations.
Trade-offs:
- Simpler to implement and understand compared to optimal approaches.
- Suitable when space is not a constraint.




----------------------------------------
Approach 3: Using Math (Optimal)
----------------------------------------

Logic:
- Convert the problem into two linear equations using sum and sum of squares.
- Let X = repeating number, Y = missing number.
- Equation 1: Sum of array (S) - Sum of [1, N] (Sn) = X - Y.
- Equation 2: Sum of squares of array (S2) - Sum of squares of [1, N] (S2n) = X^2 - Y^2.
- Solve for X and Y using X + Y = (X^2 - Y^2) / (X - Y) and X - Y.
Steps:
1. Calculate Sn = N*(N+1)/2 and S2n = N*(N+1)*(2N+1)/6.
2. Calculate S (sum of array) and S2 (sum of squares of array).
3. Compute X - Y = S - Sn and X^2 - Y^2 = S2 - S2n.
4. Compute X + Y = (X^2 - Y^2) / (X - Y).
5. Solve for X = ((X+Y) + (X-Y))/2 and Y = X - (X-Y).
6. Return [X, Y].
Time Complexity: O(N)
- Single pass to compute S and S2.
- All other operations are O(1).
Space Complexity: O(1)
- Only uses a few variables.
Advantages:
- Optimal in both time and space.
- No extra data structures required.
Limitations:
- Requires careful handling of large numbers to avoid overflow.
- Slightly more complex to understand compared to hash map approach.
Why Optimal:
- Achieves O(N) time with O(1) extra space, meeting the constraints efficiently.
- Avoids the log N factor of map-based approach and the O(N^2) of brute force.
*/

// Section 3: Code Implementation

// Approach 1: Brute Force
vector<int> findRepeatingAndMissingBruteForce(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(2); // [repeating, missing]
    
    // Iterate through 1 to N
    for (int i = 1; i <= n; i++) {
        int count = 0;
        // Count occurrences of i in array
        for (int j = 0; j < n; j++) {
            if (arr[j] == i) {
                count++;
            }
        }
        // Repeating number has count == 2
        if (count == 2) {
            result[0] = i;
        }
        // Missing number has count == 0
        if (count == 0) {
            result[1] = i;
        }
    }
    
    return result;
}

// Approach 2: Hash Map
vector<int> findRepeatingAndMissingHashMap(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(2); // [repeating, missing]
    map<int, int> mp; // Frequency map
    
    // Count frequencies
    for (int i = 0; i < n; i++) {
        mp[arr[i]]++;
        // Check for repeating number (count > 1)
        if (mp[arr[i]] > 1) {
            result[0] = arr[i];
        }
    }
    
    // Find missing number in [1, N]
    for (int i = 1; i <= n; i++) {
        if (mp.find(i) == mp.end()) {
            result[1] = i;
            break;
        }
    }
    
    return result;
}

// Approach 3: Math (Optimal)
vector<int> findRepeatingAndMissingMath(vector<int>& arr) {
    long long n = arr.size();
    vector<int> result(2); // [repeating, missing]
    
    // Step 1: Calculate expected sum and sum of squares
    long long Sn = (n * (n + 1)) / 2; // Sum of 1 to N
    long long S2n = (n * (n + 1) * (2 * n + 1)) / 6; // Sum of squares of 1 to N
    
    // Step 2: Calculate actual sum and sum of squares
    long long S = 0, S2 = 0;
    for (int i = 0; i < n; i++) {
        S += arr[i];
        S2 += (long long)arr[i] * arr[i];
    }
    
    // Step 3: Form equations
    // X - Y = S - Sn
    long long X_minus_Y = S - Sn;
    // X^2 - Y^2 = S2 - S2n
    long long X2_minus_Y2 = S2 - S2n;
    
    // Step 4: Compute X + Y = (X^2 - Y^2) / (X - Y)
    long long X_plus_Y = X2_minus_Y2 / X_minus_Y;
    
    // Step 5: Solve for X and Y
    long long X = (X_plus_Y + X_minus_Y) / 2; // Repeating number
    long long Y = X - X_minus_Y; // Missing number
    
    result[0] = (int)X;
    result[1] = (int)Y;
    
    return result;
}

// Main function to test the approaches
int main() {
    // Test case 1
    vector<int> arr1 = {3, 1, 2, 5, 3};
    cout << "Test Case 1: arr = {3, 1, 2, 5, 3}\n";
    
    // Brute Force
    vector<int> result1 = findRepeatingAndMissingBruteForce(arr1);
    cout << "Brute Force - Repeating: " << result1[0] << ", Missing: " << result1[1] << endl;
    
    // Hash Map
    vector<int> result2 = findRepeatingAndMissingHashMap(arr1);
    cout << "Hash Map - Repeating: " << result2[0] << ", Missing: " << result2[1] << endl;
    
    // Math (Optimal)
    vector<int> result3 = findRepeatingAndMissingMath(arr1);
    cout << "Math (Optimal) - Repeating: " << result3[0] << ", Missing: " << result3[1] << endl;
    
    // Test case 2
    vector<int> arr2 = {3, 1, 2, 5, 4, 6, 7, 5};
    cout << "\nTest Case 2: arr = {3, 1, 2, 5, 4, 6, 7, 5}\n";
    
    // Brute Force
    result1 = findRepeatingAndMissingBruteForce(arr2);
    cout << "Brute Force - Repeating: " << result1[0] << ", Missing: " << result1[1] << endl;
    
    // Hash Map
    result2 = findRepeatingAndMissingHashMap(arr2);
    cout << "Hash Map - Repeating: " << result2[0] << ", Missing: " << result2[1] << endl;
    
    // Math (Optimal)
    result3 = findRepeatingAndMissingMath(arr2);
    cout << "Math (Optimal) - Repeating: " << result3[0] << ", Missing: " << result3[1] << endl;
    
    return 0;
}