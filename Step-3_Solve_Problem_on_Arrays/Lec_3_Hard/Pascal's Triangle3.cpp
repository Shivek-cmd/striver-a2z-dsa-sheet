// Give me a C++ program with:
// I need a detailed explanation for solving Pascal’s Triangle (Print first `n` rows) in code.
// Please follow these steps in your response, and provide everything in a single code file format (C++).

#include <bits/stdc++.h>
using namespace std;

/* 
-----------------------------------------------------
Approach 1: Brute Force (Using Factorials)
-----------------------------------------------------
    - For each element in row `r`, compute the value using the formula:
          nCr = n! / (r! * (n - r)!)
    - We'll compute factorials separately for each term.
    - This approach is not optimal due to repeated factorial calculations and potential integer overflow.

    - Time Complexity: O(n^2 * r) ≈ O(n^3) where `r` is up to `n` in worst case (factorial per element)
    - Space Complexity: O(1) extra (excluding the result container)

-----------------------------------------------------
Approach 2: Better (Using Precomputed Factorials)
-----------------------------------------------------
    - Precompute all factorials up to `n` and store them in an array.
    - Then, use the formula nCr = fact[n] / (fact[r] * fact[n - r])
    - Reduces the factorial recomputation overhead.

    - Time Complexity: O(n^2) for computing all rows
    - Space Complexity: O(n) for storing factorials

-----------------------------------------------------
Approach 3: Optimal (Using Multiplicative Formula of nCr)
-----------------------------------------------------
    - Use the recurrence relation:
          nCr+1 = nCr * (n - r) / (r + 1)
    - Start each row with `1`, then compute next elements using previous one.
    - This avoids factorials, works in O(n^2), and prevents overflow.

    - Time Complexity: O(n^2)
    - Space Complexity: O(1) extra (excluding result container)

    💡 Thought Process:
    - Pascal’s Triangle is all about computing binomial coefficients.
    - Since we just need values like 1, 3, 3, 1 for each row, we can use the formula iteratively.
    - By keeping previous value and calculating next using a ratio, we avoid recomputing factorials or using recursion.
    - This is both space- and time-efficient.
*/

// --------------------------------------------------
// Code for Approach 1: Brute Force with Factorials
// --------------------------------------------------

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

int computeNCR_Brute(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

vector<vector<int>> pascalTriangleBrute(int n) {
    vector<vector<int>> triangle;
    for (int row = 0; row < n; row++) {
        vector<int> currentRow;
        for (int col = 0; col <= row; col++) {
            currentRow.push_back(computeNCR_Brute(row, col));
        }
        triangle.push_back(currentRow);
    }
    return triangle;
}

// --------------------------------------------------
// Code for Approach 2: Precomputed Factorials
// --------------------------------------------------

vector<long long> precomputeFactorials(int n) {
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    return fact;
}

vector<vector<int>> pascalTrianglePrecomputed(int n) {
    vector<vector<int>> triangle;
    vector<long long> fact = precomputeFactorials(n);

    for (int row = 0; row < n; row++) {
        vector<int> currentRow;
        for (int col = 0; col <= row; col++) {
            currentRow.push_back(fact[row] / (fact[col] * fact[row - col]));
        }
        triangle.push_back(currentRow);
    }
    return triangle;
}

// --------------------------------------------------
// Code for Approach 3: Optimal using Iterative nCr
// --------------------------------------------------

vector<int> generateRowOptimal(int n) {
    vector<int> row;
    long long val = 1;
    for (int c = 0; c <= n; c++) {
        row.push_back(val);
        val = val * (n - c) / (c + 1);  // next nCr
    }
    return row;
}

vector<vector<int>> pascalTriangleOptimal(int n) {
    vector<vector<int>> triangle;
    for (int i = 0; i < n; i++) {
        triangle.push_back(generateRowOptimal(i));
    }
    return triangle;
}

// --------------------------------------------------
// Main Function to Test All Approaches
// --------------------------------------------------

void printTriangle(const vector<vector<int>>& triangle) {
    for (const auto& row : triangle) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 5;

    cout << "Approach 1: Brute Force using Factorials\n";
    vector<vector<int>> triangle1 = pascalTriangleBrute(n);
    printTriangle(triangle1);

    cout << "\nApproach 2: Using Precomputed Factorials\n";
    vector<vector<int>> triangle2 = pascalTrianglePrecomputed(n);
    printTriangle(triangle2);

    cout << "\nApproach 3: Optimal using Iterative nCr\n";
    vector<vector<int>> triangle3 = pascalTriangleOptimal(n);
    printTriangle(triangle3);

    return 0;
}

/*
-----------------------------------------------------
Problem:
Variation 3: Given the number of rows `n`, print the first `n` rows of Pascal’s Triangle.

Example:
Input: n = 5
Output:
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
-----------------------------------------------------
*/
