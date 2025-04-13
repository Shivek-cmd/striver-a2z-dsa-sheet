#include <bits/stdc++.h>
using namespace std;

/*
    🔸 STL Vector in C++ - Time Complexities

    ✅ Declaration:                        O(1)
    ✅ push_back():                        Amortized O(1)
    ✅ pop_back():                         O(1)
    ✅ size(), empty(), front(), back():   O(1)
    ✅ clear():                            O(N)
    ✅ at(index), v[index]:                O(1)
    ✅ Traversing / Iteration:             O(N)
    ✅ Insert/Delete in middle (insert/erase): O(N) (since elements may shift)
*/

int main() {
    cout << "🌟 STL for DSA - All In One\n\n";

    // ✅ Declaration Examples
    vector<int> v1;               // Empty vector of ints
    vector<int> v2(5);            // Vector of 5 elements, all initialized to 0
    vector<int> v3(5, 10);        // Vector of 5 elements, all initialized to 10
    vector<int> v4 = {1, 2, 3};   // Initializer list

    // ✅ Basic Operations
    vector<int> v;
    v.push_back(10);       // Adds 10 at the end
    v.push_back(20);       // Adds 20 at the end
    v.push_back(30);       // Adds 30 at the end

    cout << "\nSize of vector: " << v.size() << endl; // Returns size
    cout << "Front element: " << v.front() << endl;   // First element
    cout << "Back element: " << v.back() << endl;     // Last element

    v.pop_back();          // Removes last element
    cout << "After pop_back, size: " << v.size() << endl;

    cout << "Is vector empty? " << (v.empty() ? "Yes" : "No") << endl;

    // ✅ Accessing Elements
    cout << "\nAccessing elements:" << endl;
    for (int i = 0; i < v.size(); ++i)
        cout << "v[" << i << "] = " << v[i] << endl;

    cout << "Element at index 0 using at(): " << v.at(0) << endl;

    // ✅ Looping Through a Vector
    cout << "\nUsing traditional for loop:" << endl;
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << "\n\nUsing range-based for loop:" << endl;
    for (int x : v)
        cout << x << " ";

    // ✅ Iterators
    cout << "\n\nUsing iterators:" << endl;
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";

    cout << "\n";

    // ✅ Clear vector
    v.clear();
    cout << "\nAfter clear(), size: " << v.size() << endl;

    return 0;
}
