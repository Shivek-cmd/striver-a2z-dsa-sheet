#include <bits/stdc++.h>
using namespace std;
// Section 1: Problem Statement
// Problem: Given an array of N integers (positive and negative), find the maximum product of a subarray.
// A subarray is a contiguous sequence of elements within the array.
// Input: A vector of N integers.
// Output: The maximum product of any subarray.
// Constraints:
// - 1 <= N <= 10^5
// - -10^9 <= nums[i] <= 10^9
// Edge Cases:
// - N = 1: Single element is the subarray.
// - Array with all zeros: Maximum product is 0.
// - Array with negative numbers: Maximum product may involve even number of negatives.
// - Array with zeros: Splits the array into separate subarrays.
// Examples:
// Example 1: nums = [1, 2, 3, 4, 5, 0] -> Result: 120 (subarray: [1,2,3,4,5])
// Example 2: nums = [1, 2, -3, 0, -4, -5] -> Result: 20 (subarray: [-4,-5])

// Section 2: Solution Approaches
/*
Approach 1: Brute Force
Logic:
- Compute the product of every possible subarray by iterating over all start and end indices.
- Track the maximum product found.
Thought Process:
- A subarray is defined by a start index i and end index j (i <= j).
- To find the maximum product, check all possible subarrays and calculate their products.
Steps:
1. Iterate i from 0 to N-1 (start of subarray).
2. Iterate j from i to N-1 (end of subarray).
3. Compute the product of elements from i to j.
4. Update the maximum product if the current product is larger.
5. Return the maximum product.
Time Complexity: O(N^3)
- O(N^2) for iterating over all subarrays (i, j pairs).
- O(N) for computing the product of each subarray.
Space Complexity: O(1)
- Only uses a variable to track the maximum product.
Limitations:
- Highly inefficient for large N (up to 10^5), leading to 10^15 operations.
Trade-offs:
- Simple to implement but impractical for large inputs.

Approach 2: Optimized Brute Force
Logic:
- Reduce the number of iterations by computing the product incrementally for each subarray starting at index i.
- Instead of recomputing the product for each j, multiply the next element.
Thought Process:
- For each start index i, compute the product of subarrays starting at i by multiplying elements one by one.
- This avoids the inner loop for product calculation.
Steps:
1. Iterate i from 0 to N-1 (start of subarray).
2. For each i, iterate j from i to N-1, maintaining a running product.
3. Update the maximum product if the current product is larger.
4. Return the maximum product.
Time Complexity: O(N^2)
- O(N^2) for iterating over all subarrays.
- O(1) for updating the product per iteration.
Space Complexity: O(1)
- Uses a variable for the running product and maximum product.
Limitations:
- Still inefficient for large N, but better than O(N^3).
Trade-offs:
- Faster than brute force but not scalable for N = 10^5.

Approach 3: Prefix and Suffix Products (Optimal)
Logic:
- Use prefix and suffix products to compute the maximum product subarray in a single pass.
- Track the product of elements from the start (prefix) and end (suffix), resetting on zeros.
- The maximum of prefix and suffix products at each step gives the maximum subarray product.
Thought Process:
- Zeros split the array into independent subarrays, as including a zero results in a product of 0.
- For non-zero segments, the maximum product is either a prefix or suffix subarray.
- Negative numbers require considering even/odd counts, handled implicitly by tracking prefix/suffix.
Steps:
1. Initialize prefix and suffix products to 1, and maxProduct to the smallest possible value.
2. Iterate i from 0 to N-1:
   - If prefix is 0, reset to 1 (start new subarray).
   - If suffix is 0, reset to 1 (start new suffix subarray).
   - Update prefix *= nums[i].
   - Update suffix *= nums[N-i-1].
   - Update maxProduct = max(maxProduct, prefix, suffix).
3. Return maxProduct.
Time Complexity: O(N)
- Single pass through the array, with constant-time operations per element.
Space Complexity: O(1)
- Uses only a few variables (prefix, suffix, maxProduct).
Advantages:
- Highly efficient, suitable for large N (up to 10^5).
- Handles zeros, negatives, and all edge cases naturally.
Limitations:
- Slightly more complex to understand due to prefix/suffix logic.
Why Optimal:
- O(N) time is a significant improvement over O(N^2) and O(N^3).
- Minimal space usage and single-pass processing make it ideal.
*/

// Section 3: Code Implementation

// Approach 1: Brute Force
long long maxProductSubarrayBruteForce(const vector<int>& nums) {
    long long maxProduct = LLONG_MIN;
    int n = nums.size();
    // Iterate over all possible subarrays
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Compute product of subarray from i to j
            long long product = 1;
            for (int k = i; k <= j; k++) {
                product *= nums[k];
            }
            maxProduct = max(maxProduct, product);
        }
    }
    return maxProduct;
}

// Approach 2: Optimized Brute Force
long long maxProductSubarrayOptimizedBrute(const vector<int>& nums) {
    long long maxProduct = LLONG_MIN;
    int n = nums.size();
    // Iterate over all start indices
    for (int i = 0; i < n; i++) {
        // Compute running product for subarrays starting at i
        long long product = 1;
        for (int j = i; j < n; j++) {
            product *= nums[j];
            maxProduct = max(maxProduct, product);
        }
    }
    return maxProduct;
}

// Approach 3: Prefix and Suffix Products (Optimal)
long long maxProductSubarrayOptimal(const vector<int>& nums) {
    long long maxProduct = LLONG_MIN;
    long long prefix = 1, suffix = 1;
    int n = nums.size();
    
    // Iterate through array, computing prefix and suffix products
    for (int i = 0; i < n; i++) {
        // Reset prefix if 0 to start new subarray
        if (prefix == 0) prefix = 1;
        // Reset suffix if 0 to start new suffix subarray
        if (suffix == 0) suffix = 1;
        
        // Update prefix and suffix products
        prefix *= nums[i];
        suffix *= nums[n - i - 1];
        
        // Update maxProduct with maximum of prefix and suffix
        maxProduct = max(maxProduct, max(prefix, suffix));
    }
    
    return maxProduct;
}

// Main function to test all approaches
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5, 0},         // 120
        {1, 2, -3, 0, -4, -5}       // 20
    };
    
    for (int i = 0; i < testCases.size(); i++) {
        const auto& nums = testCases[i];
        cout << "Test Case " << i + 1 << ": Array = ";
        for (int x : nums) cout << x << " ";
        cout << endl;
        
        // Brute Force
        long long result1 = maxProductSubarrayBruteForce(nums);
        cout << "Brute Force - Max Product: " << result1 << endl;
        
        // Optimized Brute Force
        long long result2 = maxProductSubarrayOptimizedBrute(nums);
        cout << "Optimized Brute - Max Product: " << result2 << endl;
        
        // Optimal (Prefix and Suffix)
        long long result3 = maxProductSubarrayOptimal(nums);
        cout << "Optimal - Max Product: " << result3 << endl;
        cout << endl;
    }
    
    return 0;
}