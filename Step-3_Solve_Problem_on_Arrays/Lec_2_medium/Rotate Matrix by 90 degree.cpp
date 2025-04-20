#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
Given a matrix, your task is to rotate the matrix 90 degrees clockwise.

Example 1:
Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Explanation: Rotate the matrix simply by 90 degree clockwise and return the matrix.
*/

/*
Approaches:

1. **Brute Force Approach:**
   - This approach uses a dummy matrix to store the rotated result.
   - For each element in the original matrix, place it in the corresponding position in the rotated matrix.
   
   - **Steps**:
     - Create a new matrix of dimensions `cols x rows` (swap rows and columns).
     - For each element at position `(i, j)` in the original matrix, place it in position `(j, rows - 1 - i)` in the new matrix.
     - Copy the new matrix back to the original matrix.

   - **Time Complexity**:
     - O(n^2) where `n` is the number of rows or columns (assuming a square matrix). For non-square matrices, it's O(m * n), where m is the number of rows and n is the number of columns.
   
   - **Space Complexity**:
     - O(m * n) for the dummy matrix.

2. **Optimal Approach (In-place rotation):**
   - This is a more efficient approach that modifies the matrix in-place to save space.
   - We use **two steps**:
     1. **Transpose the matrix**: Convert rows to columns and vice versa.
     2. **Reverse each row**: The reversed rows will form the rotated matrix.

   - **Time Complexity**:
     - O(n^2) where `n` is the number of rows or columns (assuming a square matrix).
   
   - **Space Complexity**:
     - O(1) because we are modifying the matrix in place.

   - **Why this is efficient**:
     - This approach only requires two passes over the matrix, making it space-efficient (since we don't use any extra space) and time-efficient (due to fewer steps).

*/

void rotatebrute(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Create a new matrix to store the rotated result
    vector<vector<int>> rotate(cols, vector<int>(rows, 0));  // Dimensions are flipped for rotation
    
    // Populate the rotated matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotate[j][rows - 1 - i] = matrix[i][j];
        }
    }

    // Copy the rotated matrix back to the original matrix
    matrix = rotate;
}

void rotateOptimal(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Step 1: Transpose the matrix (swap matrix[i][j] with matrix[j][i])
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < i; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row to complete the 90-degree clockwise rotation
    for (int i = 0; i < rows; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    rotatebrute(matrix1);
    cout << "Rotated matrix1 (Brute Force): " << endl;
    printMatrix(matrix1);

    vector<vector<int>> matrix2 = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    rotateOptimal(matrix2);
    cout << "Rotated matrix2 (Optimal): " << endl;
    printMatrix(matrix2);

    return 0;
}
