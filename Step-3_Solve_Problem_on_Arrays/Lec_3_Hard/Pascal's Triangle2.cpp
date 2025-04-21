/* Variation 2: Given the row number n. Print the n-th row of Pascal’s triangle.

-----------------------------------------------------
Approach 1: Brute Force using Factorial Function
-----------------------------------------------------
    - For each column `r` in row `n`, compute the binomial coefficient nCr using factorials:
        nCr = factorial(n) / (factorial(r) * factorial(n - r))
    - This method is simple and directly maps to the mathematical formula.
    - However, factorials can be costly and repeated for each element.

    - Time Complexity: O(n * r) ≈ O(n^2), since we compute factorial r times
    - Space Complexity: O(1), no extra space except variables


-----------------------------------------------------
Approach 2: Optimal Space + Clean Loop
-----------------------------------------------------
    - Similar to Approach 2, but focus on clarity and compact computation.
    - Use long long to avoid overflow and prevent precision issues.
    - Good for competitive programming or interviews.

    - Time Complexity: O(n)
    - Space Complexity: O(1)
/*
*/ 



#include <bits/stdc++.h>
using namespace std;

// Function to calculate factorial
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}


// ----------- Code for Approach 1: Brute Force with Factorials -----------
void printPascalRowBrute(int n) {
    for (int c = 0; c <= n; c++) {
        long long val = factorial(n) / (factorial(c) * factorial(n - c));
        cout << val << " ";
    }
    cout << endl;
}

// ----------- Code for Approach 2: Optimal Compact Version -----------

void printPascalRowOptimal(int n) {
    long long val = 1;
    for (int c = 0; c <= n; c++) {
        if (c == 0)
            cout << "1 ";
        else {
            val = val * (n - c + 1) / c;
            cout << val << " ";
        }
    }
    cout << endl;
}

int main() {
    // Sample main function to test the variations

         int n = 5;
         cout << "Brute Force (Factorial Based): ";
         printPascalRowBrute(n);

         cout << "Optimal (Compact & Efficient): ";
         printPascalRowOptimal(n);


    return 0;

    return 0;
}