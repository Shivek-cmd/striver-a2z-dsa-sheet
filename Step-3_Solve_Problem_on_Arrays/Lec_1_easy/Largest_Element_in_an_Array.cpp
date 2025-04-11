#include <bits/stdc++.h>
using namespace std;

// ✅ Complete this function to return the largest element in the array
int findLargestElement(vector<int> &arr) {
    // Your code here 👇
    int maxElement = INT_MIN;
    for(int i=0;i<arr.size();i++)
    {
        if(maxElement<arr[i])
        {
            maxElement=arr[i];
        }
    }
    return maxElement;

    
}
 
int main() {
    vector<int> arr = {3, 8, 1, 99, 12, 7};

    int largest = findLargestElement(arr);
    cout << "The largest element is: " << largest << endl;

    return 0;
}
