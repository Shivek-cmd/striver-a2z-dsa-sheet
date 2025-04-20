
/*
Problem Statement:
Given a matrix, if an element in the matrix is 0, 
then you will have to set its entire row and column to 0 
and then return the matrix.

Examples:

Input: 
matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: 
[[1,0,1],[0,0,0],[1,0,1]]

Input: 
matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: 
[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
*/

/*
-----------------------------------------------------
Approach 1 - Brute Force Approach:
-----------------------------------------------------

Steps:

- For each element in the matrix, check if it's 0.
- If we find a 0, iterate through the entire row and column and temporarily mark them with a special value (e.g., -1), since setting them directly to 0 might cause issues during the iteration.
- After scanning the matrix, convert all the -1s back to 0.

Time Complexity:

- Step 1: O(n * m), where n is the number of rows and m is the number of columns.
- Step 2: O(n * m) for each 0 found.
- Step 3: O(n * m) to convert the -1s to 0s.

Overall Time Complexity: O(n * m)

Space Complexity:

- Additional space is used for the matrix itself, so O(1) if we modify the matrix in place (no extra space).

-----------------------------------------------------
Approach 2: Using Extra Space (Marking Rows and Columns)
-----------------------------------------------------

Steps:

- Create two arrays (or vectors) rows and cols to keep track of which rows and columns need to be set to 0. These arrays will have a size of n (rows) and m (columns), respectively.
- Traverse the matrix and whenever a 0 is found, mark the respective row and column as needing to be set to 0 in the rows and cols arrays.
- After the traversal, go through the matrix again, and for each element, set it to 0 if the corresponding row or column is marked.

Time Complexity: O(n * m) because we scan the matrix twice.

Space Complexity: O(n + m) due to the additional space for rows and cols.

-----------------------------------------------------
Approach 3: Optimal Approach (In-place Solution)
-----------------------------------------------------

Steps:
 Instead of using extra space, we can mark the first row and first column to indicate whether that row or column needs to be zeroed.
- Use the first row and first column as markers: If matrix[i][0] is 0, mark the entire column 0, and if matrix[0][j] is 0, mark the entire row 0.
- Finally, iterate through the matrix and update each element according to the markers.
- Edge case: Make sure to handle the first row and first column separately as they are used for marking.

Time Complexity: O(n * m) because we only scan the matrix a few times.

Space Complexity: O(1) because we do not use any additional space except for the matrix itself.
*/

#include <bits/stdc++.h>
using namespace std;

void setZeroes(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // First, mark -1 in rows and columns that need to be set to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                // Mark row and column as needing zeroes
                for (int p = 0; p < rows; p++) {
                    if (matrix[p][j] != 0) matrix[p][j] = -1; // Temporarily mark
                }
                for (int q = 0; q < cols; q++) {
                    if (matrix[i][q] != 0) matrix[i][q] = -1; // Temporarily mark
                }
            }
        }
    }

    // Convert all -1s back to 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == -1) matrix[i][j] = 0;
        }
    }
}

void setZeroesUsingExtraSpace(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<int> rowsToZero(rows, 0);
    vector<int> colsToZero(cols, 0);

    // Step 1: Identify rows and columns that need to be zeroed
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                rowsToZero[i] = 1;
                colsToZero[j] = 1;
            }
        }
    }

    // Step 2: Set rows and columns to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (rowsToZero[i] == 1 || colsToZero[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }
}

void setZeroesOptimal(vector<vector<int>>& matrix) {
    int m = matrix.size();  // Number of rows
    int n = matrix[0].size();  // Number of columns
    int col0 = 1;  // Track whether the first column should be set to zero

    // Step 1: Mark rows and columns that should be zeroed
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                // Mark the first row and first column
                if (j != 0) {
                    matrix[0][j] = 0;  // Mark the column
                } else {
                    col0 = 0;  // Mark the first column
                }
                matrix[i][0] = 0;  // Mark the row
            }
        }
    }

    // Step 2: Set zeros in the rest of the matrix based on first row/column markers
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }

    // Step 3: Handle the first row (if it needs to be zeroed)
    if (matrix[0][0] == 0) {
        for (int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }

    // Step 4: Handle the first column (if it needs to be zeroed)
    if (col0 == 0) {
        for (int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroes(matrix1);
    cout << "Output for matrix1:" << endl;
    printMatrix(matrix1);

    vector<vector<int>> matrix2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    setZeroes(matrix2);
    cout << "Output for matrix2:" << endl;
    printMatrix(matrix2);

    vector<vector<int>> matrix3 = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroesUsingExtraSpace(matrix3);
    cout << "Output for matrix3 (using extra space):" << endl;
    printMatrix(matrix3);

    vector<vector<int>> matrix4 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    setZeroesUsingExtraSpace(matrix4);
    cout << "Output for matrix4 (using extra space):" << endl;
    printMatrix(matrix4);

    vector<vector<int>> matrix5 = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroesOptimal(matrix5);
    cout << "Output for matrix5 (optimal approach):" << endl;
    printMatrix(matrix5);

    vector<vector<int>> matrix6 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    setZeroesOptimal(matrix6);
    cout << "Output for matrix6 (optimal approach):" << endl;
    printMatrix(matrix6);

    return 0;
}
