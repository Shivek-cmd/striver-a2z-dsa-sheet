
// // Rules for Creating Patterns:

// // Outer Loop:
// // Count the number of rows (or lines) you need. This loop handles how many times the pattern repeats vertically.

// // Inner Loop:
// // Control the columns. Focus on the relationship between rows and columns—think about how each column’s value changes based on the current row.

// // Printing Inside Inner Loop:
// // Whatever character or number you need to print should go inside the inner loop. This ensures that the pattern is constructed line by line.

// // Observe Symmetry (Optional):
// // Look for any repeating or mirrored structure in the pattern. Identifying symmetry can simplify your logic and make your code cleaner.



// // // patterns 
// // 1. *****
// //   *****
// //   *****
// //   *****
// #include <iostream>
// using namespace std;

// // void print(int n) {
// //     for (int i = 0; i < n; i++) {
// //         for (int j = 0; j < n; j++) {
// //             cout << "*";
// //         }
// //         cout << endl;
// //     }
// // }

// // int main() {
// //     int n;
// //     cin >> n;
// //     print(n);

// //     return 0;
// // }
// // // patterns 
// // *
// // **
// // ***
// // ****

// // void print1(int n)
// // {
// // for(int i=0;i<n;i++)
// // {
// //     for(int j=0;j<=i;j++)
// //     {
// //         cout << "*";
// //     }
// //     cout<<endl;
// // }
// // }
// // int main() {
// //     int n;
// //     cin >> n;
// //     print1(n);

// //     return 0;
// // }

// // patterns 
// // ****
// // ***
// // **
// // *


// void print2(int n)
// {
// for(int i=0;i<n;i++)
// {
//     for(int j=n;j>=i;j--)
//     {
//         cout << "*";
//     }
//     cout<<endl;
// }
// }
// int main() {
//     int n;
//     cin >> n;
//     print2(n);

//     return 0;
// }