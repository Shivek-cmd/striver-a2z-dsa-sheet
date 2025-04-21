#include <bits/stdc++.h>
using namespace std;

/*                  1                    
                  /   \                  
                1       1                
              /   \   /   \              
            1       2       1            
          /   \   /   \   /   \          
        1       3       3       1        
      /   \   /   \   /   \   /   \      
    1       4       6       4       1    
  /   \   /   \   /   \   /   \   /   \  
 1       5       10      10      5       1


/*
Variation 1: Given row number r and column number c. Print the element at position (r, c) in Pascal’s triangle.
    Approaches:
    1. Brute Force Approach (Using Factorials)
    - In this approach, we calculate the factorials of `r`, `c`, and `(r - c)` using the formula:
      C(r, c) = r! / (c! * (r - c)!)
    - Time Complexity: O(r) because we calculate the factorial of `r`, `c`, and `r - c`.
    - Space Complexity: O(1), as only a few variables are used for storing intermediate values.


       2. Better Approach (Using C(r, c) = C(r, r-c))
    - In this approach, we minimize calculations by using the property:
      C(r, c) = C(r, r-c), which means we always choose the smaller of `c` and `r - c` for fewer iterations.
    - Time Complexity: O(c), where `c` is the smaller of `c` and `r - c`.
    - Space Complexity: O(1), as no additional space is required.
*/

// Function to calculate factorial
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Solution for Approach 1: Using the formula C(r, c) = r! / (c! * (r-c)!)
int getPascalElementByFactorial(int r, int c) {
    // Calculate factorial for r, c, and (r-c)
    long long productOfR = factorial(r);
    long long productOfC = factorial(c);
    long long productOfRMinusC = factorial(r - c);

   
    return (int)(productOfR / (productOfC * productOfRMinusC));
}

// Solution for Approach 2: Optimized approach by minimizing calculations
int getPascalElementOptimized(int r, int c) {
    // Minimize calculations by using the property C(r, c) = C(r, r-c)
    if (c > r - c) {
        c = r - c;  
    }

    // Compute C(r, c) using the direct method
    long long ans = 1;
    for (int i = 0; i < c; i++) {
      
        ans = ans * (r - i) / (i + 1);
    }

    return (int)ans;
}

int main() {
    // Sample main function to test the variations

    // Example for Variation 1
    int r = 5, c = 2;
    cout << "Element at position (" << r << ", " << c << ") using factorial method: " 
         << getPascalElementByFactorial(r, c) << endl;
    cout << "Element at position (" << r << ", " << c << ") using optimized method: " 
         << getPascalElementOptimized(r, c) << endl;

    return 0;
}