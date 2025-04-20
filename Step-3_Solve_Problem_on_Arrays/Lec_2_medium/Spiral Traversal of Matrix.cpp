#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
PROBLEM STATEMENT:
-----------------------------------------------------
Given a Matrix, print the given matrix in spiral order.

Examples:

Example 1:
Input: Matrix[][] = { { 1, 2, 3, 4 },
                      { 5, 6, 7, 8 },
                      { 9, 10, 11, 12 },
                      { 13, 14, 15, 16 } }

Output: 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10.

Example 2:
Input: Matrix[][] = { { 1, 2, 3 },
                      { 4, 5, 6 },
                      { 7, 8, 9 } }

Output: 1, 2, 3, 6, 9, 8, 7, 4, 5.
Explanation: The output of matrix in spiral form.

-----------------------------------------------------
Approaches to solve the problem:


1. **Optimal Approach (O(n²))**:
   - We can maintain the boundaries of the current subarray (top, bottom, left, right) and keep adjusting them as we print the elements.
   - This approach will visit each element once and make sure we print them in the correct spiral order.
   - Time Complexity: O(n²), Space Complexity: O(1)
   - This is the most efficient and commonly used solution.

-----------------------------------------------------
*/


// Optimal Approach (O(n²))
void printSpiralOrder_Optimal(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    int top = 0, left = 0, right = m - 1, bottom = n - 1;
    
    while (top <= bottom && left <= right) {
        // Print the top row from left to right
        for (int i = left; i <= right; i++) {
            cout << matrix[top][i] << " ";
        }
        top++;
        
        // Print the rightmost column from top to bottom
        for (int i = top; i <= bottom; i++) {
            cout << matrix[i][right] << " ";
        }
        right--;
        
        // Print the bottom row from right to left
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                cout << matrix[bottom][i] << " ";
            }
            bottom--;
        }
        
        // Print the leftmost column from bottom to top
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                cout << matrix[i][left] << " ";
            }
            left++;
        }
    }
}

// Sample main function to test all approaches
int main() {
    vector<vector<int>> matrix1 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    
    // Brute Force Approach


    // Optimal Approach
    cout << "Optimal Approach: ";
    printSpiralOrder_Optimal(matrix1);
    cout << "\n";
    
    vector<vector<int>> matrix2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    
    // Testing with another simple case
 

    cout << "Optimal Approach: ";
    printSpiralOrder_Optimal(matrix2);
    cout << "\n";

    return 0;
}
