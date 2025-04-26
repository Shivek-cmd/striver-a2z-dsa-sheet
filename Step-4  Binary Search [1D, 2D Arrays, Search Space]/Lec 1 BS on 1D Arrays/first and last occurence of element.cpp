#include <bits/stdc++.h>
using namespace std;

/*
==============================================================================
Section 1: Problem Statement
==============================================================================
Given a sorted array of integers (may contain duplicates), find the first and last
occurrences of a target value x. Return the indices of the first and last occurrences.
If the target is not found, return {-1, -1}.

Example Inputs and Outputs:
- Input: arr = [1, 2, 4, 8, 8, 10], x = 8
  Output: {3, 4} (first 8 at index 3, last 8 at index 4)
- Input: arr = [1, 2, 4, 8, 8, 10], x = 5
  Output: {-1, -1} (5 not found)

Constraints:
- 0 <= arr.size() <= 10^4
- -10^4 <= arr[i], x <= 10^4
- Array is sorted in ascending order.
*/

namespace FirstLastOccurrence {

/*
==============================================================================
Section 2: Solution Approaches
==============================================================================
*/

// Approach 1: Naive Linear Search
pair<int, int> findFirstAndLastNaive(const vector<int>& arr, int x) {
    int n = arr.size();
    int first = -1, last = -1;

    // Handle empty array
    if (n == 0) return {-1, -1};

    // Find first occurrence
    for (int i = 0; i < n; ++i) {
        if (arr[i] == x) {
            first = i;
            break;
        }
    }

    // If first not found, target doesn't exist
    if (first == -1) return {-1, -1};

    // Find last occurrence
    for (int i = n - 1; i >= 0; --i) {
        if (arr[i] == x) {
            last = i;
            break;
        }
    }

    return {first, last};
}

// Approach 2: Binary Search
pair<int, int> findFirstAndLastBinary(const vector<int>& arr, int x) {
    int n = arr.size();
    int first = -1, last = -1;

    // Handle empty array
    if (n == 0) return {-1, -1};

    // Binary search for first occurrence
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            first = mid;
            high = mid - 1; // Search left for earlier occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // If target not found
    if (first == -1) return {-1, -1};

    // Binary search for last occurrence
    low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            last = mid;
            low = mid + 1; // Search right for later occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return {first, last};
}


// Test function with C++11 compatibility (no structured bindings)
void testApproachesCpp11(const vector<int>& arr, int x) {
    cout << "Array: [";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
    }
    cout << "], Target: " << x << endl;

    // C++11: Access pair members directly
    pair<int, int> naive_result = findFirstAndLastNaive(arr, x);
    cout << "Naive Approach: {" << naive_result.first << ", " << naive_result.second << "}" << endl;

    pair<int, int> binary_result = findFirstAndLastBinary(arr, x);
    cout << "Binary Search Approach: {" << binary_result.first << ", " << binary_result.second << "}" << endl;
    cout << "----------------------------------------" << endl;
}

} // namespace FirstLastOccurrence

int main() {
    using namespace FirstLastOccurrence;

    // Test cases
    vector<int> arr1 = {1, 2, 4, 8, 8, 10};
    int x1 = 8;
    int x2 = 5;

    cout << "\nTesting :" << endl;
    testApproachesCpp11(arr1, x1);
    testApproachesCpp11(arr1, x2);

    return 0;
}

/*
==============================================================================
Compiler Instructions
==============================================================================
To compile with C++17 (required for structured bindings):
- g++: g++ -std=c++17 file.cpp -o output
- clang++: clang++ -std=c++17 file.cpp -o output
- MSVC: cl /std:c++17 file.cpp

To compile with C++11 (for compatibility):
- g++: g++ -std=c++11 file.cpp -o output
- clang++: clang++ -std=c++11 file.cpp -o output
- MSVC: cl /std:c++11 file.cpp

IDE Configuration:
- Visual Studio: Set C++ Language Standard to "C++17" in Project Properties.
- Code::Blocks: Go to Settings > Compiler > Compiler Flags, enable "-std=c++17".
- Online Compilers (e.g., LeetCode, HackerRank): Ensure C++17 is selected.

==============================================================================
Example Output
==============================================================================
Testing with C++17 Structured Bindings:
Array: [1, 2, 4, 8, 8, 10], Target: 8
Naive Approach: {3, 4}
Binary Search Approach: {3, 4}
----------------------------------------
Array: [1, 2, 4, 8, 8, 10], Target: 5
Naive Approach: {-1, -1}
Binary Search Approach: {-1, -1}
----------------------------------------

Testing with C++11 Compatibility:
Array: [1, 2, 4, 8, 8, 10], Target: 8
Naive Approach: {3, 4}
Binary Search Approach: {3, 4}
----------------------------------------
Array: [1, 2, 4, 8, 8, 10], Target: 5
Naive Approach: {-1, -1}
Binary Search Approach: {-1, -1}
----------------------------------------
*/